#pragma once
#include <unordered_map>    /** for unordered_map<>         */
#include <thread>           /** for std::thread             */
#include <memory>           /** for std::shared_ptr<>       */
#include <iostream>         /** for std::istream            */
#include <functional>       /** for function<>              */
#include <map>              /** for map<>                   */
#include <vector>           /** for vector<>                */
#include <boost/asio.hpp>   /** for boost::asio<>           */
#include <regex>            /** for std::regex std::smatch  */
#include <string>           /** for std::stoull             */

namespace csx {

// 需要定义一个结构体Request，用于解析请求。如请求方法、请求路径、HTTP版本等信息
struct Request {
    // 请求方法：POST,GET; 请求路径； HTTP版本
    std::string method, path, http_version;

    // 对content使用智能指针进行引用计数
    std::shared_ptr<std::istream> content;

    // hash容器，k-v字典
    std::unordered_map<std::string, std::string> header;

    // 用正则表达式处理路径搭配
    std::smatch path_match;
};

// 定义服务器资源类型
typedef std::map<std::string, std::unordered_map<std::string,
                            std::function<void(std::ostream&, Request&)>>> resource_type;

// socket_type为HTTP或者HTTPS
template<typename socket_type>
class ServerBase {
public:
    // 构造函数
    ServerBase(unsigned short port, size_t num_threads = 1);

    // 启动服务器
    void            start();
protected:
    // 需要不同类型的服务器实现这个方法
    virtual void    accept() {}

    // 处理请求和应答
    void            process_request_and_response(std::shared_ptr<socket_type> socket) const;

    // --解析请求
    Request         parse_request(std::istream&) const;

    // --应答
    void            respond(std::shared_ptr<socket_type> socket, std::shared_ptr<Request> request) const;

public:
    // 用于服务器访问资源处理方式
    resource_type resource;

    // 用于保存默认资源的处理方式
    resource_type default_resource;
protected:
    // 用于内部实现对所有资源的处理
    std::vector<resource_type::iterator> all_resource;

    // 定义Boost Asio需要的参数
    boost::asio::io_service         m_io_service;
    boost::asio::ip::tcp::endpoint  endpoint;
    boost::asio::ip::tcp::acceptor  acceptor;

private:
    size_t num_threads;
    std::vector<std::thread> threads;
};

template<typename socket_type>
class Server : public ServerBase<socket_type> { };
}







// 构造函数
template<typename socket_type>
csx::ServerBase<socket_type>::ServerBase(unsigned short port, size_t num_thread)
    : endpoint(boost::asio::ip::tcp::v4(), port),
      acceptor(m_io_service, endpoint),
      num_threads(num_threads)
{

}

// 启动服务器
template<typename socket_type>
void csx::ServerBase<socket_type>::start() {
    // 默认资源应该放在vector的末尾，用作默认应答 ：
    // 默认的请求会在找不到匹配请求路径时，进行访问。因此添加在最后
    for (resource_type::iterator iter = resource.begin(); iter != resource.end(); ++iter) {
        all_resource.push_back(iter);
    }
    for (auto iter = default_resource.begin(); iter != default_resource.end(); ++iter) {
        all_resource.push_back(iter);
    }

    // 调用socket的链接方式：还需要子类来实现accept()的逻辑
    accept();

    // 如果num_threads > 1, 那么执行m_io_service.run()
    // 将运行（num_threads - 1个）线程成为线程池
    for (size_t c = 0; c != threads.size(); c++) {
        threads.emplace_back([this]{
            m_io_service.run();
        });
    }
    // 主线程
    m_io_service.run();

    // 等待其他线程：如果有的话，就等待这些线程结束
    for (std::thread& t : threads) {
        t.join();
    }
}

// 处理请求和应答
template<typename socket_type>
void csx::ServerBase<socket_type>::process_request_and_response(std::shared_ptr<socket_type> socket) const {
    // 为async_read_until() 创建新的读缓存
    // shared_ptr用于传递临时对象给lambda（匿名）函数
    // auto会被自动推导为 std::shared_ptr<boost::asio::streambuf>
    auto read_buffer = std::make_shared<boost::asio::streambuf>();
    /**
     * async_read_until异步读取系列, 这个函数的原理是, 给定一个streambuf, 和一个分隔符,asio碰到分隔符时返回;
     * 你可以从streambuf中读取需要的数据。但是在 async_read_until 操作成功后,  streambuf 在界定符之外可能包含一些额外的的数据
     * reference link : http://www.cppblog.com/sunicdavy/archive/2012/12/03/195921.html
     */
    boost::asio::async_read_until(*socket, *read_buffer, "\r\n\r\n",
                    [this, socket, read_buffer](const boost::system::error_code& ec, size_t bytes_transferred){
        if (!ec) {
            // 所以较好的做法是直接从流中提取并解析当前 read_buffer 左边的报头,再拼接async_read_until后面的内容
            size_t total = read_buffer->size();

            // 转换到istream : 之后streambuf缓冲区清空
            std::istream stream(read_buffer.get());

            // auto 被自动推导为 std::make_shared<Request>
            auto request = std::make_shared<Request>();

            // 接下来是将流中的请求信息进行解析，然后保存在request对象中
            *request = parse_request(stream);

            // async_read_until()读取的额外的内容
            size_t num_additional_bytes = total - bytes_transferred;

            // 如果满足，同样读取
            if (request->header.count("Content-Length") > 0) {
                boost::asio::async_read(*socket, *read_buffer,
                boost::asio::transfer_exactly(std::stoull(request->header["Content-Length"]) - num_additional_bytes),
                [this, socket, read_buffer, request](const boost::system::error_code& ec, size_t bytes_transferred){
                    if (!ec) {
                        // 将指针作为istream对象存储在read_buffer中
                        request->content = std::make_shared<std::istream>(read_buffer.get());
                        respond(socket, request);
                    }
                });
            }else {
                respond(socket, request);
            }
        }
    });
}

// --解析请求
template<typename socket_type>
csx::Request csx::ServerBase<socket_type>::parse_request(std::istream& stream) const {
    Request request;
    // 使用正则表达式对请求报头进行解析，通过下面的正则表达式
    // 可以解析出请求方法(GET/POST)、请求路径以及 HTTP 版本
    std::regex e("^([^ ]*) ([^ ]*) HTTP/([^ ]*)$");
    std::smatch sub_match;
    // 从流中的第一行中，解析出请求方法、路径和HTTP版本
    std::string line;
    std::getline(stream, line);
    // line得到第一行之后，把最后的换行符号'CRLF'去掉。
    line.pop_back();
    if (std::regex_match(line, sub_match, e)) {
        request.method          = sub_match[1];
        request.path            = sub_match[2];
        request.http_version    = sub_match[3];

        // 继续解析头部的其他信息
        bool matched;
        e = "^([^:]*): ?(.*)$";
        do {
            // 继续去流中的下一行内容
            getline(stream, line);
            //去除CTRL这个符号（不熟悉的同学，参考https://github.com/tycao/tycao.github.io/blob/master/HTTP_Protocol.md了解HTTP的结构）
            line.pop_back();
            matched = std::regex_match(line, sub_match, e);
            if (matched) {
                request.header[sub_match[1]] = sub_match[2];
            }

        } while (matched == true);
    }
    return request;
}

template<typename socket_type>
void csx::ServerBase<socket_type>::respond(std::shared_ptr<socket_type> socket, std::shared_ptr<Request> request) const {
    // 对请求路径和方法进行匹配查找，并生成响应
    for (auto res_it : all_resource) {
            std::regex e(res_it->first);
            std::smatch sm_res;
            if (std::regex_match(request->path, sm_res, e)) {
                if (res_it->second.count(request->method) > 0) {
                    request->path_match = std::move(sm_res);

                    // auto会被推导为std::shared_ptr<boost::asio::streambuf>
                    auto write_buffer = std::make_shared<boost::asio::streambuf>();
                    std::ostream response(write_buffer.get());  // 定义一个std::pstream类型的response变量
                    res_it->second[request->method](response, *request);

                    // 在lambda中捕获write_buffer，使其不会在async_write完成前被销毁
                    boost::asio::async_write(*socket, *write_buffer,
                         [this, socket, request, write_buffer](const boost::system::error_code& ec, size_t bytes_transferred){
                        // HTTP 长连接（HTTP/1.1），递归调用
                        if (!ec && std::stof(request->http_version) > 1.05) {
                            process_request_and_response(socket);
                        }
                    });
                    return;
                }
            }
    }
}

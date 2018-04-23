#pragma once

#include "server_base.h"

namespace csx {

typedef boost::asio::ip::tcp::socket HTTP;
template<>
class Server<HTTP> : public ServerBase<HTTP> {
public:
    Server(unsigned short port, size_t num_threads = 1)
        : ServerBase<HTTP>::ServerBase(port, num_threads) {}
private:
    // 实现accept方法
    void accept() {
        // 为当前链接创建一个新的socket
        // shared_ptr用于传递一个临时变量给匿名函数
        // socket 会被推导为std::shared_ptr<HTTP>类型
        auto socket = std::make_shared<HTTP>(m_io_service);

        acceptor.async_accept(*socket, [this, socket](const boost::system::error_code& ec){
            // 立即启动并接受一个连接
            accept();

            //
            if (!ec) {
                process_request_and_response(socket);
            }
        });
    }
};
}

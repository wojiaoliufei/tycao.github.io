实现自己的web服务器
=======
众所周知，当我们上网时，使用搜索引擎访问页面时，发生了很多事情（但是我们并不知情）。例如：在浏览器地址栏键入URL `www.baidu.com`，按下回车之后会经历以下流程：<br />
* 浏览器向 DNS 服务器请求解析该 URL 中的域名所对应的 IP 地址;
* 解析出 IP 地址后，根据该 IP 地址和默认端口 80，和服务器建立TCP连接;
* 浏览器通过GET方法，发出读取文件(URL 中域名后面部分对应的文件)的HTTP 请求，该请求报文作为 TCP 三次握手的第三个报文的数据发送给服务器;
* 服务器对浏览器请求作出响应，并把对应的 html 文本发送给浏览器;
* 释放 TCP连接; （TCP四次挥手）
* 浏览器将根据html格式解析该 html 文本并显示内容; 

### 由上述可知，浏览器帮我们做了很多事情。包括请求DNS解析域名成ip地址，然后浏览器默认端口是80，简历tcp连接后，发送给web服务器请求资源。这里的web服务器通常就是Nginx或者Apache.

现在我们自己实现一个轻量型的web服务器。我们把自己的实现的web服务器运行在Linux下。然后访问该Linux服务器。就会得到来自服务器响应给我们的资源信息。<br />
!["web_server"](https://github.com/tycao/tycao.github.io/blob/master/src/web_server.png "web_server")<br /><br />
!["web_server2"](https://github.com/tycao/tycao.github.io/blob/master/src/web_server2.png "web_server2")<br /><br />
!["web_server3"](https://github.com/tycao/tycao.github.io/blob/master/src/web_server3.png "web_server3")<br /><br />


### Linux下执行以下命令时：
```shell
./b2 --with-filesystem --with-system --with-log --with-date_time --with-regex --with-thread --with-atomic --with-locale --with-program_options --build-dir="/home/zogy/boostbuild" --stagedir="/home/zogy/boostlib/stage/lib" link=static runtime-link=shared threading=multi
```
### 大部分的gcc编译器版本都不支持`--with-log`的编译。一直报错。我只好一个个去编译，等到编译到`--with-log`时才发现原来是这货的问题。把上述命令，**去掉--with-log**在各个gcc编译器版本下都能编译通过。如：`gcc 4.8.5 , gcc 7.3.0`等等。

### 另外，这个web服务程序，需要用到正则表达式，但是gcc4.8.5对正则表达式支持的不是很好，会报错。因此需要gcc4.9或者更高版本。

********
### 项目地址：
[C++实现轻量型Web服务框架--HTTP](https://github.com/tycao/tycao.github.io/tree/master/HTTP)<br />
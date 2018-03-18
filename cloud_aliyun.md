在阿里云上搭建自己的shadowsocks
======
* 环境：
	* CentOS 7.4, 64bit， 美国西部（硅谷）， shadowsocks<br />
	![centos_version](https://github.com/tycao/tycao.github.io/blob/master/cloud_aliyun_src/centos_version.png "centos_version")<br />
* 首先，需要买一台阿里云服务器，我买的是**美国西部硅谷的CentOS 7.4版本**。 具体如何买阿里云服务器，[请参考我的上一篇博客](https://github.com/tycao/tycao.github.io/blob/master/deploy_ShadowsSocks_in_Aliyun.md)<br />
* 购买好云服务器之后，运行以下命令，安装 `python-pip` 和 `shadowsocks`:<br />
```shell
yum install python-pip
pip install shadowsocks
```
* 上述命令完成后，安装以下命令：<br />
```shell
touch /etc/shadowsocks.json
chmod 777 /etc/shadowsocks.json
vi /etc/shadowsocks.json
```

* 在 `/etc/shadowsocks.json` 里添加以下内容:<br />
###（多人）只使用单个端口上网的情况：
```shell
{
    "server":"0.0.0.0",
    "server_port":443,
    "local_address":"127.0.0.1",
    "local_port":1080,
    "password":"12345",
    "timeout":300,
    "method":"aes-256-cfb",
    "fast_open":false,
    "workers":5
}
```
!["shadows_json"](https://github.com/tycao/tycao.github.io/blob/master/cloud_aliyun_src/shadowsocks_json.png "shadows_json")<br />
###（多人）各自使用自己的端口上网的情况：
```shell
{
	"server":"0.0.0.0",
	"local_address": "127.0.0.1",
	"local_port":1080,
	"port_password":{
		"8381":"pass1",
		"8382":"pass2",
		"8383":"pass3",
		"8384":"pass4"
	},
	"timeout":60,
	"method":"aes-256-cfb",
	"fast_open":false,
	"workers":1
}
```
!["port"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/port2.png "port")<br />

:warning: <br /> 
1. 注意修改 `"password":"12345"` 为自己的密码
2. workers 表示启动的进程数量 
3. 单个端口上网的情况：需要去`阿里云控制台`为该**阿里云服务器开通443端口**. :point_right: `"server_port":443`  
4. 多个端口上网的情况：需要去`阿里云控制台`为该**阿里云服务器开通8381/8384端口**.
!["port"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/port.png "port")<br />

* 启动shadowsocks服务:<br />
```shell
shadowsocks启动: ssserver -c /etc/shadowsocks.json -d start 
shadowsocks重启: ssserver -c /etc/shadowsocks.json -d restart 
shadowsocks关闭: ssserver -c /etc/shadowsocks.json -d stop
```
## 使用本机Shdowsocks客户端, 连接阿里云服务器上网：<br />
****
[shadowsocks android 版本](https://github.com/shadowsocks/shadowsocks-android/releases)<br />
[shadowsocks windows 版本](https://github.com/shadowsocks/shadowsocks-windows/releases)<br />
shadowsocks iPhone, iPad版本,可以去App store里搜索 ： **firstwingy**


****
参考链接：
[x] [使用阿里云ECS CentOS 搭建Shadowscoks](http://blog.csdn.net/zh237560547/article/details/75318697)<br />
[x] [阿里云centos 7下搭建shadowsocks](https://segmentfault.com/a/1190000010639190)<br />
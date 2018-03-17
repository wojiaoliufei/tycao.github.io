在阿里云上搭建自己的shadowsocks
======
* 环境：
	* CentOS 7.4, 64bit， 美国西部（硅谷）， shadowsocks<br />
	![centos_version](https://github.com/tycao/tycao.github.io/blob/master/cloud_aliyun_src/centos_version.png "centos_version")<br />
* 首先，需要买一台阿里云服务器，我买的是美国西部硅谷的CentOS 7.4
* 购买好云服务器之后，运行以下命令，安装 `python-pip` 和 `shadowsocks`:<br />
```shell
yum install python-pip
pip install shadowsocks
```
* 上述命令完成后，安装以下命令：<br />
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

:warning: <br /> 
* 注意修改 password 为自己的密码
* workers 表示启动的进程数量 

* 启动shadowsocks服务:<br />
```shell
shadowsocks启动: ssserver -c /etc/shadowsocks.json -d start 
shadowsocks重启: ssserver -c /etc/shadowsocks.json -d restart 
shadowsocks关闭: ssserver -c /etc/shadowsocks.json -d stop
```

****
使用本机Shdowsocks客户端, 连接阿里云服务器上网：
[shadowsocks android 版本](https://github.com/shadowsocks/shadowsocks-android/releases)<br />
[shadowsocks windows 版本](https://github.com/shadowsocks/shadowsocks-windows/releases)<br />
shadowsocks iPhone, iPad版本,可以去App store里搜索 ： firstwingy
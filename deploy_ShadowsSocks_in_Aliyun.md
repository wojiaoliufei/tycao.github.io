本节讲述如何在阿里云服务器上搭建ss代理：
----------
## 首先，我在阿里云官网买了一台Centos7版本的云服务器（美国东部 硅谷）。
![aliyun_US2](https://github.com/tycao/tycao.github.io/blob/master/src/aliyun_US2.png "aliyun_US2")

至于如何购买，请移步这里：[如何购买阿里云服务器](http://how2j.cn/k/deploy2linux/deploy2linux-breif/1591.html?tid=107)<br />

##  其次，使用Putty或者SecureCRT远程登录云服务器。 [Putty下载地址：putty 64bit](https://pan.baidu.com/s/1pMQ3u1H)   [SecureCRT下载地址：](https://pan.baidu.com/s/1oAp7QMe)
![putty](https://github.com/tycao/tycao.github.io/blob/master/src/putty.png "putty")
![putty2](https://github.com/tycao/tycao.github.io/blob/master/src/putty2.png "putty2")

## 安装Shadowsocks
* 在Putty上复制如下命令：
	* wget --no-check-certificate https://raw.githubusercontent.com/teddysun/shadowsocks_install/master/shadowsocks.sh
	* chmod +x shadowsocks.sh
	* ./shadowsocks.sh 2>&1 | tee shadowsocks.log

上面3行命令依次运行后，等待命令完成....期间不要动，这些命令是给云服务器安装Shadowsocks服务的。中间会提示你输入你的SS SERVER的密码和端口。建议你输入一个自己的密码和端口(端口范围1-65536，推荐10000以上),如果不输入,系统会启用默认密码（default passowrd: teddysun.com）端口（defaut port:8989）。然后按任意键继续。。。
![pwd_port](https://github.com/tycao/tycao.github.io/blob/master/src/5.png "pwd_port")

稍等一会跑完命令后会出来你的SS客户端的信息,记得记下来：
![aliyun_US](https://github.com/tycao/tycao.github.io/blob/master/src/aliyun_US.png "aliyun_US")

若看到以上提示后就表明阿里云服务器上SS（ShadowSocks服务）已经安装成功，并且已经设置了开机启动，云服务器重启后不用手工启动SS。



# 锐速加速 安装方法

1.复制下面代码到putty里面按回车

wget -N --no-check-certificate https://raw.githubusercontent.com/91yun/serverspeeder/master/serverspeeder-all.sh && bash serverspeeder-all.sh

2.复制下面代码到putty里面也按回车

vi /serverspeeder/etc/config

3.重启加速服务完成优化

service serverSpeeder restart


## 最后，在本地Windows下，安装Shadowsocks客户端，地址如下：
* 非官网：
	* [SS windows客户端下载：非官网](http://www.veryhuo.com/down/html/87755.html)<br />
* 官网：
	* https://github.com/shadowsocks/shadowsocks-windows/releases
* 国内镜像请移步这里：
	* [Shadowsocks国内下载地址：](https://pan.baidu.com/s/1pNl2ein)<br />

安装好之后，输入上述的密码，端口号，云服务器ip
![ss](https://github.com/tycao/tycao.github.io/blob/master/src/shadowsocks.png "ss")


# ~快乐学习 ~快乐编程
* 参考文档：
	* [教你如何自己搭建vps，10M宽带用ss看youtube 1080p无压力！！](http://www.oneplusbbs.com/thread-3068029-1-4.html)<br />
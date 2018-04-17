centos7升级自带的php5.4版本到php5.6 
===========
#### 参考： https://blog.csdn.net/qq_34829953/article/details/78078790


*********
CentOS7 下完全删除mysql，然后重新安装
==================
#### 参考： https://blog.csdn.net/black_1988/article/details/54897235

```shell
yum remove mysql mysql-server mysql-libs compat-mysql51
rm -rf /var/lib/mysql
rm /etc/my.cnf
```
查看是否还有mysql软件：
```shell
rpm -qa|grep mysql
```
有的话继续删除即可。 <br />
接下来，参考本博客其他文章（重新）安装mysql-community版本

*********
傻瓜式搭建私人网络硬盘——owncloud安装指南
=========
#### 参考： 
* https://www.cnblogs.com/nihaorz/p/7170509.html
* http://www.vpsdaquan.cn/vpsdajianowncloud.html

```shell
rpm -import https://download.owncloud.org/download/repositories/stable/CentOS_7/repodata/repomd.xml.key
wget http://download.owncloud.org/download/repositories/stable/CentOS_7/ce:stable.repo -O /etc/yum.repos.d/ce:stable.repo
yum clean expire-cache
yum install owncloud
```
中途会让你选择yes和no，全部yes<br />
完成后重启apache：<br />
```shell
# CentOS6及其以下：
service httpd start

# CentOS7 及其以下：
systemctl start httpd
```



******
******

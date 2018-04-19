centos7升级自带的php5.4版本到php5.6 
===========
#### 参考： https://blog.csdn.net/qq_34829953/article/details/78078790
##### history命令历史：
```shell
    8  yum provides php   #自带的只有5.4版本
    9   rpm -Uvh https://mirror.webtatic.com/yum/el7/epel-release.rpm         #更新源
   10   rpm -Uvh https://mirror.webtatic.com/yum/el7/webtatic-release.rpm
   11  yum remove php-common -y     #移除系统自带的php-common
   12  yum install -y php56w php56w-opcache php56w-xml php56w-mcrypt php56w-gd php56w-devel php56w-mysql php56w-intl php56w-mbstring         #安装依赖包
   13  php -v                    #版本变为5.6
   14  yum provides php-fpm      #因为我是准备搭建lnmp，所以安装php-fpm，这里会提示多个安装源，选择5.6版本的安装就可以了
   15  yum install php56w-fpm-5.6.31-1.w7.x86_64 -y
```

*********
CentOS7 下完全删除mysql，然后重新安装
==================
#### 参考：
* https://blog.csdn.net/black_1988/article/details/54897235
* https://www.cnblogs.com/kerrycode/p/4364465.html

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

centos7升级自带的php5.4版本到php5.6 
===========
#### https://blog.csdn.net/qq_34829953/article/details/78078790


*********
CentOS7 下完全删除mysql，然后重新安装
==================
#### https://blog.csdn.net/black_1988/article/details/54897235

```shell
yum remove mysql mysql-server mysql-libs compat-mysql51
rm -rf /var/lib/mysql
rm /etc/my.cnf
```
查看是否还有mysql软件：
```shell
rpm -qa|grep mysql
```
有的话继续删除即可。 
接下来，参考本博客其他文章（重新）安装mysql-community版本

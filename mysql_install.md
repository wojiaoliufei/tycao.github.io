Linux下安装MySQL
=======
### 背景：虽然安装 `mysql` 是大家都很熟悉的技能。但是此篇教程对于刚刚学习Linux的同学，还是有些用处的。:blush:
### 时间：2018-04-14 21:00 周六

!["lufei"](https://github.com/tycao/tycao.github.io/blob/master/src/lufei.jpg "lufei")<br /><br />
********


# Ubuntu下安装MySQL:
#### 环境：UBuntu 16.04 32bit
```shell
root@ubuntu:/mnt/hgfs/share/flamingoserver# uname -a
Linux ubuntu 4.4.0-34-generic #53-Ubuntu SMP Wed Jul 27 16:06:28 UTC 2016 i686 i686 i686 GNU/Linux
```
* 使用`sudo apt-get install mysql-server mysql-client` 命令安装 `mysql客户端` 和 `服务器端`
```shell
root@ubuntu:/mnt/hgfs/share# sudo apt-get install mysql-server mysql-client
Reading package lists... Done
Building dependency tree       
Reading state information... Done
The following packages were automatically installed and are no longer required:
  libwxbase3.0-0v5 libwxgtk3.0-0v5
Use 'sudo apt autoremove' to remove them.
The following additional packages will be installed:
  libaio1 libevent-core-2.0-5 libhtml-template-perl mysql-client-5.7 mysql-client-core-5.7 mysql-server-5.7
  mysql-server-core-5.7
Suggested packages:
  libipc-sharedcache-perl mailx tinyca
The following NEW packages will be installed:
  libaio1 libevent-core-2.0-5 libhtml-template-perl mysql-client mysql-client-5.7 mysql-client-core-5.7
  mysql-server mysql-server-5.7 mysql-server-core-5.7
0 upgraded, 9 newly installed, 0 to remove and 576 not upgraded.
Need to get 19.0 MB of archives.
After this operation, 157 MB of additional disk space will be used.
Do you want to continue? [Y/n] y
Get:1 http://us.archive.ubuntu.com/ubuntu xenial/main i386 libaio1 i386 0.3.110-2 [6,646 B]
Get:2 http://us.archive.ubuntu.com/ubuntu xenial-updates/main i386 mysql-client-core-5.7 i386 5.7.21-0ubuntu0.16.04.1 [6,432 kB]
7% [2 mysql-client-core-5.7 1,233 kB/6,432 kB 19%]                                          1,436 B/s 3h 25min 44s

9% [2 mysql-client-core-5.7 1,543 kB/6,432 kB 24%]                                                                                 


Get:3 http://us.archive.ubuntu.com/ubuntu xenial-updates/main i386 mysql-client-5.7 i386 5.7.21-0ubuntu0.16.04.1 [1,732 kB]        
Get:4 http://us.archive.ubuntu.com/ubuntu xenial-updates/main i386 mysql-server-core-5.7 i386 5.7.21-0ubuntu0.16.04.1 [7,841 kB]   
Get:5 http://us.archive.ubuntu.com/ubuntu xenial-updates/main i386 libevent-core-2.0-5 i386 2.0.21-stable-2ubuntu0.16.04.1 [75.7 kB]
Get:6 http://us.archive.ubuntu.com/ubuntu xenial-updates/main i386 mysql-server-5.7 i386 5.7.21-0ubuntu0.16.04.1 [2,799 kB]        
Get:7 http://us.archive.ubuntu.com/ubuntu xenial/main i386 libhtml-template-perl all 2.95-2 [60.4 kB]                              
Get:8 http://us.archive.ubuntu.com/ubuntu xenial-updates/main i386 mysql-client all 5.7.21-0ubuntu0.16.04.1 [10.1 kB]              
Get:9 http://us.archive.ubuntu.com/ubuntu xenial-updates/main i386 mysql-server all 5.7.21-0ubuntu0.16.04.1 [10.2 kB]              
Fetched 19.0 MB in 5min 29s (57.5 kB/s)                                                                                            
Preconfiguring packages ...
Selecting previously unselected package libaio1:i386.
(Reading database ... 202358 files and directories currently installed.)
Preparing to unpack .../libaio1_0.3.110-2_i386.deb ...
Unpacking libaio1:i386 (0.3.110-2) ...
Selecting previously unselected package mysql-client-core-5.7.
Preparing to unpack .../mysql-client-core-5.7_5.7.21-0ubuntu0.16.04.1_i386.deb ...
Unpacking mysql-client-core-5.7 (5.7.21-0ubuntu0.16.04.1) ...
Selecting previously unselected package mysql-client-5.7.
Preparing to unpack .../mysql-client-5.7_5.7.21-0ubuntu0.16.04.1_i386.deb ...
Unpacking mysql-client-5.7 (5.7.21-0ubuntu0.16.04.1) ...
Selecting previously unselected package mysql-server-core-5.7.
Preparing to unpack .../mysql-server-core-5.7_5.7.21-0ubuntu0.16.04.1_i386.deb ...
Unpacking mysql-server-core-5.7 (5.7.21-0ubuntu0.16.04.1) ...
Selecting previously unselected package libevent-core-2.0-5:i386.
Preparing to unpack .../libevent-core-2.0-5_2.0.21-stable-2ubuntu0.16.04.1_i386.deb ...
Unpacking libevent-core-2.0-5:i386 (2.0.21-stable-2ubuntu0.16.04.1) ...
Selecting previously unselected package mysql-server-5.7.
Preparing to unpack .../mysql-server-5.7_5.7.21-0ubuntu0.16.04.1_i386.deb ...
Unpacking mysql-server-5.7 (5.7.21-0ubuntu0.16.04.1) ...
Selecting previously unselected package libhtml-template-perl.
Preparing to unpack .../libhtml-template-perl_2.95-2_all.deb ...
Unpacking libhtml-template-perl (2.95-2) ...
Selecting previously unselected package mysql-client.
Preparing to unpack .../mysql-client_5.7.21-0ubuntu0.16.04.1_all.deb ...
Unpacking mysql-client (5.7.21-0ubuntu0.16.04.1) ...
Selecting previously unselected package mysql-server.
Preparing to unpack .../mysql-server_5.7.21-0ubuntu0.16.04.1_all.deb ...
Unpacking mysql-server (5.7.21-0ubuntu0.16.04.1) ...
Processing triggers for libc-bin (2.23-0ubuntu3) ...
Processing triggers for man-db (2.7.5-1) ...
Processing triggers for ureadahead (0.100.0-19) ...
Processing triggers for systemd (229-4ubuntu4) ...
Setting up libaio1:i386 (0.3.110-2) ...
Setting up mysql-client-core-5.7 (5.7.21-0ubuntu0.16.04.1) ...
Setting up mysql-client-5.7 (5.7.21-0ubuntu0.16.04.1) ...
Setting up mysql-server-core-5.7 (5.7.21-0ubuntu0.16.04.1) ...
Setting up libevent-core-2.0-5:i386 (2.0.21-stable-2ubuntu0.16.04.1) ...
Setting up mysql-server-5.7 (5.7.21-0ubuntu0.16.04.1) ...
update-alternatives: using /etc/mysql/mysql.cnf to provide /etc/mysql/my.cnf (my.cnf) in auto mode
Renaming removed key_buffer and myisam-recover options (if present)
Setting up libhtml-template-perl (2.95-2) ...
Setting up mysql-client (5.7.21-0ubuntu0.16.04.1) ...
Setting up mysql-server (5.7.21-0ubuntu0.16.04.1) ...
Processing triggers for libc-bin (2.23-0ubuntu3) ...
Processing triggers for ureadahead (0.100.0-19) ...
Processing triggers for systemd (229-4ubuntu4) ...
root@ubuntu:/mnt/hgfs/share# 
root@ubuntu:/mnt/hgfs/share# 
root@ubuntu:/mnt/hgfs/share# 
root@ubuntu:/mnt/hgfs/share# 
root@ubuntu:/mnt/hgfs/share# 
root@ubuntu:/mnt/hgfs/share# mysql -v
ERROR 1045 (28000): Access denied for user 'root'@'localhost' (using password: NO)
root@ubuntu:/mnt/hgfs/share# mysql -V
mysql  Ver 14.14 Distrib 5.7.21, for Linux (i686) using  EditLine wrapper
```

* 使用`mysql -V`命令，显示`mysql的版本`：
```shell
mysql -V
```
* 查看mysql的运行状态：
```shell
service mysql status
```
!["mysql_status"](https://github.com/tycao/tycao.github.io/blob/master/src/mysql_status.png "mysql_status")<br /><br />

* 登录mysql服务器：
```shell
mysql -u root -p
```
会跳出`Enter Password:`的界面：输入mysql的登录密码，按回车键。
然后就会成功进入到mysql的操作界面。

* 创建MySQL数据库和用户：
```shell
mysql> create database snailblog;
```
* 创建用户（用户名为`man_user`， 密码为`test1234`），并使用snailblog数据库：<br />
```shell
mysql> grant all on snailblog.* to 'man_user'@'localhost' identified by 'test1234';
mysql> flush privileges;			# 使命令立刻生效
```
!["create_db"](https://github.com/tycao/tycao.github.io/blob/master/src/create_db.png "create_db")<br /><br />

* 使用新用户登录：<br />
```shell
mysql -u man_user -ptest1234
```
:warning: 注意！<br />
* _**`-u`和用户名之间可以加空格，也可以不加空格**_  
* _-p和登录密码之间必须**不能**有空格_
!["man_user"](https://github.com/tycao/tycao.github.io/blob/master/src/man_user.png "man_user")<br /><br />

* 创建表：<br />
```shell
mysql> CREATE TABLE IF NOT EXISTS `user` (id INT, name VARCHAR(20), email VARCHAR(20));
```
!["create_tb"](https://github.com/tycao/tycao.github.io/blob/master/src/create_tb.png "create_tb")<br /><br />

* 插入记录：<br />
```shell
mysql> INSERT INTO user (id,name,email) VALUES(1,"bar","bar@gmail.com");
mysql> INSERT INTO user (id,name,email) VALUES(2,"foo","foo@163.com");
mysql> INSERT INTO user (id,name,email) VALUES(3,"cat","cat@gmail.com");
```
* 简单查询：<br />
```shell
mysql> SELECT * FROM user;
```
!["insert"](https://github.com/tycao/tycao.github.io/blob/master/src/insert.png "insert")<br /><br />

* 退出MySQL命令行：<br />
```shell
quit 或者 exit
```
* 停止MySQL数据库服务：<br />
```shell
sudo systemctl stop mysql.service
# 或者
service mysql stop
```
!["stop_mysql_service"](https://github.com/tycao/tycao.github.io/blob/master/src/stop_mysql_service.png "stop_mysql_service")<br /><br />


* 查看MySQL运行状态：<br />
```shell
sudo systemctl status mysql.service 
# 或者
service mysql status
```
!["query_mysql_status"](https://github.com/tycao/tycao.github.io/blob/master/src/query_mysql_status.png "query_mysql_status")<br /><br />

* 启动MySQL数据库服务：<br />
```shell
sudo systemctl start mysql.service
# 或者
service mysql start
```

* 重启MySQL数据库服务：<br />
```shell
sudo systemctl restart mysql.service
# 或者
service mysql restart
```
!["start_mysql_service"](https://github.com/tycao/tycao.github.io/blob/master/src/start_mysql_service.png "start_mysql_service")<br /><br />

* 修改mysql用户的登录密码：<br />
#### 在mysql系统外，使用mysqladmin：<br />
`mysqladmin -u 用户名 -p password "密码"`
```shell
$ mysqladmin -uroot -p password "test1234"
```
!["change_pwd"](https://github.com/tycao/tycao.github.io/blob/master/src/change_pwd.png "change_pwd")<br /><br />

* MySQL的配置文件：<br />
```shell
sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf
```
!["config_file"](https://github.com/tycao/tycao.github.io/blob/master/src/config_file.png "config_file")<br /><br />


* [x] 参考链接：<br />
[UBuntu下安装MySQL](https://blog.csdn.net/vXueYing/article/details/52330180)<br />

!["lufei"](https://github.com/tycao/tycao.github.io/blob/master/src/lufei.jpg "lufei")<br /><br />


***********



# CentOS下安装mysql:
#### 环境：CentOS 7.4 64bit

**history命令：**
```shell
  328  mkdir /temp
  329  cd /temp/
  332  wget http://repo.mysql.com/mysql-community-release-el7-5.noarch.rpm
  333  ll
  334  rpm -ivh mysql-community-release-el7-5.noarch.rpm
  335  yum install mysql-server	# 此处在有网络的情况下，会自动下载mysql-client mysql-devlib mysql-commom等依赖包
  336  systemctl status mysql
  337  systemctl start mysql
  338  systemctl status mysql
  340  mysql -V
  341  mysql -uroot -p				# Mysql的root初始值没有密码
  342  mysqladmin -uroot -p password "1"	# 修改mysql的root登录密码为'1'
  343  mysql -uroot -p1
  344  mysql -ucaosx -p1
```
!["centos_mysql"](https://github.com/tycao/tycao.github.io/blob/master/src/centos_mysql.png "centos_mysql")<br /><br />

* 下载：<br />
yum上mysql的资源有问题，所以不能仅仅之用yum。在使用yum之前还需要用其他命令获取mysql社区版：<br />
```shell
mkdir /temp									# 若/temp存在，则直接忽略这一步
cd /temp
wget http://repo.mysql.com/mysql-community-release-el7-5.noarch.rpm
rpm -ivh mysql-community-release-el7-5.noarch.rpm
```
* 通过yum进行安装:<br />
接着就可以通过yum安装了：<br />
```shell
yum install mysql mysql-server mysql-devel -y
```

* 以上只是安装，执行如下命令才能启动mysql服务器：<br />
```shell
systemctl start mysql.service				# CentOS 6的启动服务的命令是：service mysql start
```

* 验证：<br />
安装后会自动启动，启动后会占用3306端口。 使用如下命令查看3306端口是否启动，如果启动了则表示mysql处于运行状态。
```shell
netstat -anp|grep 3306
```
* 创建密码并登录：
通过Yum安装的mysql的管理员账户是没有密码的，这里通过命令设置其密码为 admin ，尽量使用这个密码哦，后续部署j2ee应用的时候会用到这个密码哦。
注： Warning信息并非提示设置失败，而是告诉大家密码露出来了，当心背后有人~
```shell
mysqladmin -u root -p password admin		# -p 这个参数一定不能忘记！！！
```
!["mysql_change_pwd"](https://github.com/tycao/tycao.github.io/blob/master/src/mysql_change_pwd.png "mysql_change_pwd")<br /><br />

* 登录验证：
```shell
mysql -u root -padmin
```



*****

* [x] 参考链接：
[CentOS下如何安装MySQL](http://how2j.cn/k/deploy2linux/deploy2linux-install/1608.html)<br />

!["lufei2"](https://github.com/tycao/tycao.github.io/blob/master/src/lufei2.jpg "lufei2")<br /><br />



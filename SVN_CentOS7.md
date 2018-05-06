CentOS7下搭建SVN服务器（此方法同样适用于UBuntu）
===============
### 参考文档：
[CentOS Linux搭建SVN Server配置详解](http://www.ha97.com/4467.html)<br />
************
**时间：** 2018-05-06 14:00 <br />
**背景：** 很早之前就想创建自己的SVN仓库了。由于平时工作中用的就是SVN，业余时间自己用的是Git来进行代码管理，但是Github上private项目代码管理是收费的！因此一些不适合公开的代码就需要自己搭建SVN服务器了。<br />
**SVN简介和工作原理：** <br />
* subversion（简称svn）是近几年崛起的版本管理软件，是cvs的接班人，目前绝大多数公司和开源软件都使用svn作为代码版本管理软件。Subversion支持linux和windows，但较多安装在linux下。<br />
* svn服务器有两种运行方式：`独立服务器和借助于apache。`  即`svn://或http://` <br />
* svn客户端tortoisesvn ，国内镜像请看这里 :point_right: [SVN for Windows安装包](https://pan.baidu.com/s/112VzU5CC9jF8TgRUUbhrmA]    密码：ysn3  <br />
* svn的基本工作原理： 在一台服务器上建立一个源代码库，库里可以存放许多不同项目的源程序。有源代码库管理员统一管理这些源程序。每个用户在使用源代码库之前，首先要把源代码库里的项目文件下载到本地，然后开发人员可以在本地修改，然后用svn命令进行提交，由源代码库统一管理修改。<br />
* subversion目录说明：
	* dav目录：是提供apache与mod_dav_svn使用的目录，让他们存储内部数据
	* db目录：就是所有版本控制的数据存放文件
	* hooks目录：放置hook脚本文件的目录
	* locks目录：用来放置subversion见艰苦锁定数据的目录，用来追踪存取文件库的客户端
	* format文件：是一个文本文件，里面只放了一个整数。表示当前文件库配置的版本号
	* conf目录：是这个仓库的配置文件（仓库的用户访问账号、权限等）
!["svn_01"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_01.png "svn_01")<br /><br />

************
**接下来详细讲解安装步骤：** <br />
#### 环境： CentOS7 64bit
### 购买一台云服务器：
这里不再赘述，请参考这里 :point_right: [如何购买云服务器](http://how2j.cn/k/deploy2linux/deploy2linux-breif/1591.html?tid=107)<br />

### 安装必须的软件包：
**yum install subversion mysql-server httpd mod_dav_svn mod_perl sendmail wget gcc-c++ make unzip perl\* ntsysv vim-enhanced**
* 说明：
	* subversion (SVN服务器)
	* mysql-server (用于codestriker)
	* httpd mod_dav_svn mod_perl (用于支持WEB方式管理SVN服务器)
	* sendmail (用于配置用户提交代码后发邮件提醒)
	* wget gcc-c++ make unzip perl* (必备软件包)
	* ntsysv vim-enhanced (可选)
* 安装subversion 
```shell
# 查看subversion安装包
yum search subversion

# 安装subversion
yum install subversion
```
!["svn_02"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_02.png "svn_02")<br /><br />

* 查看subversion版本
```shell
svnserve --version
```
!["svn_03"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_03.png "svn_03")<br /><br />

* 安装mysql <br />
yum上mysql的资源有问题，所以不能仅仅之用yum。在使用yum之前还需要用其他命令获取mysql社区版<br />
```shell
# 根目录下创建/temp临时文件夹
mkdir /temp

# 进入到目录下
cd /temp

# 安装mysql 社区版本的安装包
wget http://repo.mysql.com/mysql-community-release-el7-7.noarch.rpm

# 解压
rpm -ivh mysql-community-release-el7-7.noarch.rpm 

# 通过yum 安装
yum install mysql mysql-server mysql-devel -y

# 启动: 以上只是安装，执行如下命令才能启动mysql服务器：
systemctl start mysql.service

# 验证：安装后会自动启动，启动后会占用3306端口。 使用如下命令查看3306端口是否启动，如果启动了则表示mysql处于运行状态。
netstat -anp|grep 3306

# 无密码：通过Yum安装的mysql的管理员账户是没有密码的，这里通过命令设置其密码为 admin
## 注： Warning信息并非提示设置失败，而是告诉大家密码露出来了，当心背后有人~
mysqladmin -u root -p password "admin"

# 使用新密码admin登录mysql服务器
mysql -uroot -padmin
```
注意修改mysql登录密码这一步骤，[原文里](http://how2j.cn/k/deploy2linux/deploy2linux-password/1609.html) 没有 `-p` 这个选项，是错误的。必须要加上`-p`,然后跳出需要你填写旧密码进行验证。<br />
!["svn_04"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_04.png "svn_04")<br /><br />

* 安装Apache
```shell
yum install httpd
```
* 安装mod_dav_svn
```shell
# 查找 mod_dav_svn安装包
yum search mod_dav_svn

# 安装mod_dav_svn
yum install mod_dav_svn
```
!["svn_05"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_05.png "svn_05")<br /><br />


* 安装mod_perl
```shell
# 查找mod_perl安装包
yum search mod_perl

# 安装mod_perl
yum install mod_perl
```
!["svn_06"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_06.png "svn_06")<br /><br />

* 安装 sendmail
```shell
# 查找sendmail 安装包
yum search sendmail 

# 安装sendmail
yum install sendmail 
```
!["svn_07"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_07.png "svn_07")<br /><br />

* 安装wget
```shell
yum install wget 
``` 

* 安装gcc-c++
```shell
yum install gcc-c++
```

* 安装make
```shell
yum search make
yum install make.x86_64
```
!["svn_08"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_08.png "svn_08")<br /><br />


* 安装unzip
```shell
yum install unzip
```

* 安装perl*
```shell
yum install perl*
```

* 安装ntsysv
* 安装 vim-enhanced


### 基本的SVN服务器配置
* 新建一个目录用于存储SVN所有文件
```shell
mkdir /home/svn
```

* 新建一个版本仓库
```shell
svnadmin create /home/svn/project
```

* 初始化版本仓库中的目录
```shell
# 创建临时目录 project
mkdir project project/server project/client project/test

# 初始化SVN目录
svn import project/ file:///home/svn/project -m “初始化SVN目录”

# 删除临时建立的目录
rm -rf project
```

* 添加用户
```shell
vim /home/svn/project/conf/passwd
```
**要添加SVN用户非常简单，只需在 `/home/svn/project/conf/passwd` 文件添加一个形如 `username=password` 的条目就可以了。为了测试，我添加了如下内容:** <br />
```shell
[users]
# harry = harryssecret
# sally = sallyssecret

# 新添加的内容 @2018-05-06
pm = pm_pw

# 能够访问project:/server目录的用户：server_group, server1, server2, server3
server_group = server_pw
server1 = server_pw
server2 = server_pw
server3 = server_pw

# 能够访问project:/client目录的用户：client_group, client1, client2, client3
client_group = client_pw
client1 = client_pw
client2 = client_pw
client3 = client_pw

# 能够访问project:/test目录的用户：test_group, test1, test2, test3
test_group = test_pw
test1 = test_pw
test2 = test_pw
test3 = test_pw
```
!["svn_09"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_09.png "svn_09")<br /><br />


* 修改用户访问策略
```shell
vim /home/svn/project/conf/authz
```

**`/home/svn/project/conf/authz` 记录用户的访问策略，添加以下内容:** <br />

```shell
[group]
# newly added @2018-05-06

# 将定义在/home/svn/project/conf/passwd文件里的用户，分成不同的组，以便访问不同的目录
project_p = pm
project_s = server1, server2, server3, server_group
project_c = client1,client2,client3, client_group
project_t = test1,test1,test1, test_group

# 能够访问project:/（根目录）的用户所在的组
[project:/]
@project_p = rw
* =

# 能够访问project:/server的用户所在的组
[project:/server]
@project_p = rw
@project_s = rw
* =

# 能够访问project:/client的用户所在的组
[project:/client]
@project_p = rw
@project_c = rw
* =

# 能够访问project:/test的用户所在的组
[project:/test]
@project_p = rw
@project_s = rw
@project_c = rw
@project_t = rw
* =



[project:/doc]
@project_p = rw
@project_s = rw
@project_c = rw
@project_t = rw
*=
```
!["svn_10"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_10.png "svn_10")<br /><br />

* 说明：
	* 以上信息表示：
		* 只有`project_p`用户组有`根目录`的读写权;
		* 只有`project_p和project_s用户组`有`project:/server`目录的读写权
		* 只有`project_p和project_c用户组`有`project:/client`目录的读写权
		* `project_p, project_s, project_c, project_t用户组`都有`project:/test`目录的读写权
		* `project_p, project_s, project_c, project_t用户组`都有`project:/doc`目录的读写权
	* `r`表示对该目录有读权限，`w`表示对该目录有写权限，`rw`表示对该目录有读写权限。
	* `最后一行的 _* =_ 表示，除了上面设置了权限的用户组之外，其他任何人都被禁止访问本目录。这个很重要，一定要加上！`
* 修改svnserve.conf文件,让用户和策略配置升效
```shell
vim /home/svn/project/conf/svnserve.conf
```
添加以下内容：<br />
```shell
[general]
anon-access = none
auth-access = write
password-db = /home/svn/project/conf/passwd
authz-db = /home/svn/project/conf/authz
```
!["svn_11"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_11.png "svn_11")<br /><br />


* 启动服务器
```shell
svnserve -d -r /home/svn
```
**注意：如果修改了svn配置，需要重启svn服务，步骤如下：** <br />
```shell
ps -aux|grep svnserve
kill -9 ID号
svnserve -d -r /home/svn
```
接下来， 还要重新启动Apache服务器
```shell
systemctl restart httpd
```

* 测试服务器
```shell
# 不是在本机器测试的话，将localhost修改成相应的ip地址
svn co svn://localhost/project
```
!["svn_12"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_12.png "svn_12")<br /><br />

**若是第一次运行 `svn co svn://localhost/project`的话，需要输入 svn所在服务器的 `root` 密码：** <br />
```shell
# svn co svn://192.168.60.10/project
Authentication realm: <svn://192.168.60.10:3690> 92731041-2dae-4c23-97fd-9e1ed7f0d18d
Password for 'root':
Authentication realm: <svn://192.168.60.10:3690> 92731041-2dae-4c23-97fd-9e1ed7f0d18d
Username: server_group
Password for 'server_group':
svn: Authorization failed ( server_group没用根目录的访问权 )
```
输入 `root密码`之后，紧接着输入了 `svn用户密码`，以上信息说明了：svn用户 `server_group` 没有 `project:/`根目录的访问权限。我们重新输入其他的svn用户再试试看效果：<br />
```shell
# svn co svn://192.168.60.10/project
Authentication realm: <svn://192.168.60.10:3690> 92731041-2dae-4c23-97fd-9e1ed7f0d18d
Password for ‘root’:
Authentication realm: <svn://192.168.60.10:3690> 92731041-2dae-4c23-97fd-9e1ed7f0d18d
Username: pm
Password for ‘pm’:
A    project/test
A    project/server
A    project/client
Checked out revision 1.  ( 测试提取成功 )
```
以上信息说明 svn用户 `pm` 具有根目录的访问权限，和我们上面在配置文件里配置的信息完全一致！`server_group`只对`projecft:/server       project:/test        project:/doc目录` 有读写权限。而对`project:/`根目录没有读写权限！ <br />

```shell
# cd project/server
# vim main.c
# svn add main.c
# svn commit main.c -m “测试一下我的C程序,看什么看,不行啊??”
Adding         main.c
Transmitting file data .
Committed revision 2.  ( 测试提交成功 )
```
再次测试：<br />
```shell
# 进入/project目录下
cd /project

# 新建doc文件夹
mkdir doc

# 添加到svn服务器上
svn add doc

# commit
svn commit doc -m "添加doc文件夹~~"
```

### 配置SVN服务器的HTTP支持
* 转换SVN服务器的密码 <br />
**由于SVN服务器的密码是明文的，HTTP服务器不与支持，所以需要转换成HTTP支持的格式。我写了一个Perl脚本完成这个工作。 脚本内容如下:**  <br />
```shell
cd /home/svn/project/conf/
vim PtoWP.pl
```
添加以下内容：<br />
```perl
#!/usr/bin/perl
use warnings;
use strict;

#open the svn passwd file
open (FILE, "passwd") or die ("Cannot open the passwd file!!!\n");

#clear the apache passwd file
open (OUT_FILE, ">webpasswd") or die ("Cannot open the webpasswd file!!!\n");
close (OUT_FILE);

#begin
foreach (<FILE>) {
	if($_ =~ m/^[^#].*=/) {
		$_ =~ s/=//;
		`htpasswd -b webpasswd $_`;
	}
}
```
!["svn_14"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_14.png "svn_14")<br /><br />

*  设置 `PtoWP.pl` 执行权限
```shell
chmod a+x PtoWP.pl
```


* 运行perl脚本 `PtoWP.pl`
```shell
./PtoWP.pl
```
!["svn_13"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_13.png "svn_13")<br /><br />


* 修改httpd.conf，添加关于SVN服务器的内容 <br />
```shell
vim /etc/httpd/conf/httpd.conf
```
添加以下内容：<br />
```shell
<Location /project>
DAV svn
SVNPath /home/svn/project/
AuthType Basic
AuthName "svn for project"
AuthUserFile /home/svn/project/conf/webpasswd
AuthzSVNAccessFile /home/svn/project/conf/authz
Satisfy all
Require valid-user
</Location>
```
!["svn_15"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_15.png "svn_15")<br /><br />

* 修改svn目录的属主为apache帐号 <br />
**注意：原文少了这一步，会出权限问题!!!** <br />
```shell
chown -R apache.apache /home/svn/project/
```


* 重启Web服务器：
```shell
# 查看apache服务的运行状态
systemctl status httpd

# 重启apache服务
systemctl restart httpd
```
!["svn_16"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_16.png "svn_16")<br /><br />

* 用浏览器访问 `http://localhost/project/server/` 测试 <br />
**若不是在本机测试，则需要把 `localhost` 修改成相应正确的 `公网ip地址`**
!["svn_17"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_17.png "svn_17")<br /><br />
!["svn_18"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_18.png "svn_18")<br /><br />
!["svn_19"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_19.png "svn_19")<br /><br />


******************
Windows下安装svn客户端tortoisesvn ：<br />
!["svn_20"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_20.png "svn_20")<br /><br />
!["svn_21"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_21.png "svn_21")<br /><br />


* 去svn服务器上操作：
```shell
[root@iZt4n12effj3d79928coatZ project]# cd /project
[root@iZt4n12effj3d79928coatZ project]# ll doc/
total 16
-rw-r--r-- 1 root root 14734 May  6 16:40 SVN_CentOS7.md
[root@iZt4n12effj3d79928coatZ project]# svn update
Updating '.':
A    doc/Linux下搭建SVN服务器.txt
Updated to revision 10.
[root@iZt4n12effj3d79928coatZ project]# ll doc/
total 16
-rw-r--r-- 1 root root     0 May  6 16:49 Linux下搭建SVN服务器.txt
-rw-r--r-- 1 root root 14734 May  6 16:40 SVN_CentOS7.md
[root@iZt4n12effj3d79928coatZ project]#
```
!["svn_22"](https://github.com/tycao/tycao.github.io/blob/master/src/svn_22.png "svn_22")<br /><br />

Windows下安装SQL Server 2014，并且打开1433端口
==========================
**背景：** 最近工作里需要计算收益数据，CentOS7环境下，需要从另一台服务器的SQL Server数据库里取出数据。自己就在家先测试一下。虚拟机是Ubuntu 16.04, SQL Server安装在Windows物理机下。
然后在UBuntu下一直 `telnet 192.168.1.102 1433` 一直失败！ **（192.168.1.102是Windows内网IP地址）** 然后又在Windows下cmd命令行中运行 `netstat -a` ， 也一直没有出现1433端口！ 我就火了，怎么回事。然后一直找问题原因。

**********
* [x] 参考连接 ： 
[SQL server 2014 1433端口开启解决方案](https://blog.csdn.net/qq_33412610/article/details/74858100)<br />

### 步骤：
* 配置服务端的tcp/ip协议：
**在SQL Server网络配置中选择 `CAOSX` （安装过程中，设置的SQL Server数据引擎服务器名称）的协议，选择TCP/IP，右键单击，选择属性**<br />
!["sql_server_01"](https://github.com/tycao/tycao.github.io/blob/master/src/sql_server_01.png "sql_server_01")<br /><br />

* 选择IP地址选项卡：
**把 `IP1` 和 `IP2` 中 `TCP端口` 为 `1433`** <br />
**`已启用` 改为 `是`** <br />
!["sql_server_02"](https://github.com/tycao/tycao.github.io/blob/master/src/sql_server_02.png "sql_server_02")<br /><br /><br />

* 配置客户端的tcp/ip协议：
!["sql_server_03"](https://github.com/tycao/tycao.github.io/blob/master/src/sql_server_03.png "sql_server_03")<br /><br /><br />

* 重新启动 `SQL Server` 服务
!["sql_server_04"](https://github.com/tycao/tycao.github.io/blob/master/src/sql_server_04.png "sql_server_04")<br /><br /><br />

* 在物理机本地检测 `1433端口是否已经开启` :
**运行命令： `netstat -a`** <br />
!["sql_server_05"](https://github.com/tycao/tycao.github.io/blob/master/src/sql_server_05.png "sql_server_05")<br /><br /><br />

* 在虚拟机运行以下命令，检测 `是否能够连接物理机的1433端口：` <br />
!["sql_server_06"](https://github.com/tycao/tycao.github.io/blob/master/src/sql_server_06.png "sql_server_06")<br /><br /><br />


*************************
继 [上篇博客教程：CentOS7下安装FreeTDS远程访问Windows下的SQl Server](https://github.com/tycao/tycao.github.io/blob/master/FreeTDS_ON_CentOS7.md) ，现在FreeTDS和SQL Server都已经安装好了。万事俱备，欧文嗯可以通过Linux远程访问（增删改查）Windows下的SQL Server了！！！<br />
!["sql_server_07"](https://github.com/tycao/tycao.github.io/blob/master/src/sql_server_07.png "sql_server_07")<br /><br /><br />
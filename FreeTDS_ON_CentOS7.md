CentOS7下安装FreeTDS远程访问Windows下的SQl Server
==============
* 安装FreeTDs
```shell
# 获取最新版本的freetds的gz安装包 ： 目前最新的安装包是v0.91 
wget http://ibiblio.org/pub/Linux/ALPHA/freetds/stable/freetds-stable.tgz
```
* FreeTDS的安装、配置
```shell
# 解压
tar -zxvf freetds-stable.tgz

# 运行./configure
./configure --prefix=/usr/local/freetds \(指定FreeTDS安装路径)
			--with-tdsver=8.0 --enable-msdblib （设置TDS版本，支持SQL Server 2014）

# 完整版本	
./configure --prefix=/usr/local/freetds --with-tdsver=8.0 --enable-msdblib

# make编译
make

# make 安装
make install
```

* 将freetds的库文件所在路径配置到LD_LIBRARY_PATH参数中
```shell
vim ~/.bashrc
```
添加如下代码：<br />
```shell
PATH=${PATH}:/usr/local/freetds/bin
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/freetds/lib
export PATH
export LD_LIBRARY_PATH
```
然后运行`source ~/.bashrc` 就可以使其立刻生效。<br />
这么作的目的是为了避免加载FreeTds库文件加载不上的情况。 解决了每次运行程序时报错：`failed loading shared library` <br />
这样，就把freetds添加到系统环境变量里面了。

* `/usr/local/freetds/etc/freetds.conf` 的配置新的节点（很重要）
**此步骤用来测试命令行可以远程连接**
```shell
vim /usr/local/freetds/etc/freetds.conf
```
在末尾添加如下内容：<br />
```shell
[TestFreeTDS]
host = 10.187.1.1	# 填写属于自己的正确的ip地址
port = 1433
timeout = 600
connect timeout = 600
tds version = 8.0
text size = 20971560
```
!["freetds_conf"](https://github.com/tycao/tycao.github.io/blob/master/src/freetds_conf.PNG "freetds_conf")<br />
然后终端运行如下命令测试远程连接windows SQL Server:<br />
**tsql -S TestFreeTDS -U username -P passwd** <br />
!["tsql_S"](https://github.com/tycao/tycao.github.io/blob/master/src/tsql_S.PNG "tsql_S")<br />


* `/usr/local/freetds/etc/freetds.conf` 的配置 `[global]` 节点：
	* 注释掉 `[global]`下的 `; tds version = 4.2`
	* 添加新的如下两行内容
		* tds version = 8.0
		* port = 1433
	* 注视掉 `; dump file = /tmp/freetds.log`
	* 重新添加一行 `dump file = /tmp/freetds.log` ： 可以通过`/tmp/freetds.log`查看运行freetds时的状态

运行如下命令，测试远程连接Windwos Server：<br />
```shell
tsql -H 10.187.1.1 -U sa -p 1433 -P password
```
!["tsql_H"](https://github.com/tycao/tycao.github.io/blob/master/src/tsql_S.PNG "tsql_H")<br />

**************
### 参考链接：
[Linux下使用C/C++访问数据库——SQL Server篇](https://blog.csdn.net/xingxu0207/article/details/75027542)<br />

在Linux下升级GCC版本
===========
## 时间：2018-04-14 21:00
编译gcc `make -j 8` 花了整整一夜！（4个小时）
### 参考链接：<br />
[stackoverflow : CentOS下如何升级gcc版本](https://stackoverflow.com/questions/36327805/how-to-install-gcc-5-3-with-yum-on-centos-7-2)<br />
## 在UBuntu 16.04上升级gcc（最好使用root权限执行下列命令）：
* 安装 add-apt-repository 工具

	`sudo apt-get install software-properties-common`

* 增加源

	`sudo add-apt-repository ppa:ubuntu-toolchain-r/test`

* 更新源

	`sudo apt-get update`

* 更新安装

	`sudo apt-get upgrade`

* 安装 gcc/g++ 4.9

	`sudo apt-get install gcc-4.9 g++-4.9`

* 更新链接

	`sudo updatedb`
	`sudo ldconfig`

	sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 48 \
	 --slave /usr/bin/g++ g++ /usr/bin/g++-4.8 \
	 --slave /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-4.8 \
	 --slave /usr/bin/gcc-nm gcc-nm /usr/bin/gcc-nm-4.8 \
	 --slave /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-4.8<br />
	sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 49 \
	 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9 \
	 --slave /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-4.9 \
	 --slave /usr/bin/gcc-nm gcc-nm /usr/bin/gcc-nm-4.9 \
	 --slave /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-4.9
* 参考链接里的截图：<br />
!["gcc_upgrade"](https://github.com/tycao/tycao.github.io/blob/master/src/gcc_upgrade.png "gcc_upgrade")<br /><br /><br />

!["lufei"](https://github.com/tycao/tycao.github.io/blob/master/src/lufei.jpg "lufei")<br /><br />
****************
### UBuntu16.04 升级到gcc-7版本：<br />

#### Installing gcc 7.3 (gcc 7.3.0) - released 01/25/2018:

#### download file: https://ftp.gnu.org/gnu/gcc/gcc-7.3.0/gcc-7.3.0.tar.gz  <br /><br />
`wget https://ftp.gnu.org/gnu/gcc/gcc-7.3.0/gcc-7.3.0.tar.gz`
#### 下载gcc的安装包之后，先解压：
`tar -zxvf gcc-7.3.0/gcc-7.3.0.tar.gz`
#### 解压好gcc包之后，开始安装gcc之前，需要安装一些依赖（required libraries）:
* 首先，检查当前UBubtu安装源是否有这些依赖包：`gmp, mpfr, mpc`<br />
`apt-cache search gmp` <br />
!["gmp_dev"](https://github.com/tycao/tycao.github.io/blob/master/src/gmp_dev.png "gmp_dev")<br /><br />
于是： `apt install libgmp-dev`， 第一个依赖安装好了<br />
`apt-cache search mpfr` <br />
!["mpfr_dev"](https://github.com/tycao/tycao.github.io/blob/master/src/mpfr_dev.png "mpfr_dev")<br /><br />
于是： `apt install libmpfr-dev`， 第二个依赖安装好了<br />
`apt-cache search mpc` <br />
!["mpc_dev"](https://github.com/tycao/tycao.github.io/blob/master/src/mpc.png "mpc_dev")<br /><br />
于是： `apt install libmpc-dev`， 第三个依赖安装好了<br />
#### 如上述，依赖安装好了之后，接下来，安装gcc：<br />
```shell
./configure --with-system-zlib --disable-multilib --enable-languages=c,c++
make -j 8		#### this step took me roughly 4 hours and 6G in dick to finnish!!! ###
make install
```
#### 上述步骤完成之后，先关闭当前终端。再开一个新的终端。然后输入命令 `gcc -v` 查看gcc版本。<br />
!["gcc_v"](https://github.com/tycao/tycao.github.io/blob/master/src/gcc_v.png "gcc_v")<br /><br />
#### 参考链接里的截图：<br />
!["apt_cache"](https://github.com/tycao/tycao.github.io/blob/master/src/apt_cache.png "apt_cache")<br /><br />
参考文档：[apt-cache search gmp | apt-cache search mpfr | apt-cache search mpc](https://askubuntu.com/questions/832597/e-unable-to-locate-package-php5-gmp)<br /><br />

#### 关于查找一个package:
* UBubtu上的命令是： 
```shell
apt-cache search gmp
apt-cache search mpfr
apt-cache search mpc
```

* 在CentOS下的命令：
```shell
yum search gem
yum search mpfr
yum search mpc
```
	

* [x] 参考链接：<br />
[UBubtu16.04升级gcc版本](https://blog.csdn.net/Watson2016/article/details/52415429)<br />
!["lufei"](https://github.com/tycao/tycao.github.io/blob/master/src/lufei.jpg "lufei")<br /><br />
*****

## 在CentOS下升级gcc
### 第一种方法：<br />
* 升级到gcc-7.2版本：<br />
Often people want the most recent version of gcc, and devtoolset is being kept up-to-date, so maybe you want devtoolset-N where N={4,5,6,7...}, check yum for the latest available on your system). Updated the cmds below for N=7.
<br /><br />
There is a package for gcc-7.2.1 for devtoolset-7 as an example. First you need to enable the [Software Collections](https://www.softwarecollections.org/en/scls/rhscl/devtoolset-4/), then it's available in devtoolset-7:
```shell
sudo yum install centos-release-scl
sudo yum install devtoolset-7-gcc*
scl enable devtoolset-7 bash
which gcc
gcc --version
```

### 第二种方法：<br />
#### 下载gcc-7.2安装包：<br />
安装 gcc 7.3 ( [gcc 7.3.0](https://ftp.gnu.org/gnu/gcc/gcc-7.3.0/) ) - released 01/25/2018:<br />
下载文件： https://ftp.gnu.org/gnu/gcc/gcc-7.3.0/gcc-7.3.0.tar.gz
```shell
wget https://ftp.gnu.org/gnu/gcc/gcc-7.3.0/gcc-7.3.0.tar.gz
tar -zxvf gcc-7.3.0.tar.gz
```
编译 、 安装：<br />
```shell
# 首先安装依赖库:
yum install libmpc-devel mpfr-devel gmp-devel

# 进入到gcc目录下
cd gcc-7.3.0
# 在gcc目录下执行一下命令：
./configure --with-system-zlib --disable-multilib --enable-languages=c,c++

# 编译
make -j 8

# 安装
make install
```
<br /><br /><br />
* [x] 参考链接：<br />
[StackOverflow ：How to Install gcc 5.3 with yum on CentOS 7.2](https://stackoverflow.com/questions/36327805/how-to-install-gcc-5-3-with-yum-on-centos-7-2)<br />
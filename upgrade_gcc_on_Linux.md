在Linux下升级GCC版本
===========
* 在UBuntu 16.04上升级gcc:
	* 安装 add-apt-repository 工具
```shell
sudo apt-get install software-properties-common
```
	* 增加源
```shell
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
```
	* 更新源
```shell
sudo apt-get update
```
	* 更新安装
```shell
sudo apt-get upgrade
```
	* 安装 gcc/g++ 4.9
```shell
sudo apt-get install gcc-4.9 g++-4.9
```
	* 更新链接
```shell
sudo updatedb
sudo ldconfig

sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 48 \
 --slave /usr/bin/g++ g++ /usr/bin/g++-4.8 \
 --slave /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-4.8 \
 --slave /usr/bin/gcc-nm gcc-nm /usr/bin/gcc-nm-4.8 \
 --slave /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-4.8
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 49 \
 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9 \
 --slave /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-4.9 \
 --slave /usr/bin/gcc-nm gcc-nm /usr/bin/gcc-nm-4.9 \
 --slave /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-4.9
```
<br /><br />
* [x] 参考链接：<br />
[](https://blog.csdn.net/Watson2016/article/details/52415429)<br />
!["lufei"](https://github.com/tycao/tycao.github.io/blob/master/src/lufei.jpg "lufei")<br /><br />
*****

* 在CentOS下升级gcc
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

<br /><br /><br />
* [x] 参考链接：<br />
[How to Install gcc 5.3 with yum on CentOS 7.2](https://stackoverflow.com/questions/36327805/how-to-install-gcc-5-3-with-yum-on-centos-7-2)<br />
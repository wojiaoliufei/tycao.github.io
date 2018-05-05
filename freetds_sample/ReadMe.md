UBuntu上安装FreeTDS，C++程序远程访问Windows SQL Server
===============
FreeTDS的安装过程和CentOS7完全一致。<br />
项目代码在本文件的同级目录下。This sample works fine on both UBuntu16.04 and CentOS7. Feel Free to make it as you like. <br />

***************
但是Makefile的内容与CentOS7下有些与不同。
### UBuntu上必须把`-lsybdb`放在编译命令的最后，才能通过编译。否则就会报错：`undefined reference to 'dbinit' ....` <br />
```shell
g++ -std=c++11 -I/usr/local/freetds/include/ -L/usr/local/freetds/lib/ manager.cpp test.cpp -o test -lsybdb

```
### 但是CentOS7下就可以把`-lsybdb` 放在编译命令的前面编译。不会报错
```shell
g++ -std=c++11 -I/usr/local/freetds/include/ -L/usr/local/freetds/lib/ -lsybdb manager.cpp test.cpp -o test
```
!["ubuntu_samba_05.png"](https://github.com/tycao/tycao.github.io/blob/master/src/ubuntu_samba_05.png "ubuntu_samba_05.png")<br /><br />

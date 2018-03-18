在Linux下安装、编译protocol buffer
=======
## 环境： UBuntu 16.04 , 64bit
* 拷贝protobuf tar包到UBuntu下：
	* 在UBuntu16.04上安装ftp服务器：
	```shell
	sudo apt-get install vsftpd
	```
	!["vsftpd"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/vsftpd.png "vsftpd")<br />
	!["vsftpd2"]( "vsftpd2")<br />
	* 查看vsftpd服务：
	```shell
	service vsftpd status	#查看vsftpd服务状态
	service vsftpd start	#开启vsftpd服务
	service vsftpd restart	#重启vsftp服务
	```
	!["vsftpd2"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/vsftpd2.png "vsftpd2")<br />
	* 安装vsftpd的详细情况，请参考这篇教程 :point_right: [部署vsftpd到linux](http://how2j.cn/k/deploy2linux/deploy2linux-intro/1599.html)<br />
* 解压protobuf tar安装包：
```shell
sudo tar -zxvf protobuf-cpp-3.5.1.tar.gz
cd protobuf-3.5.1/
sudo ./configure
sudo make	#这一步需要等待一些时间编译
sudo make install
```

* 上述步骤完成后，运行 `protoc --version` 报错:
!["vsftpd"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/protoc_version.png "vsftpd")<br />
解决方法是，运行以下命令：
```shell
sudo chmod 777 /etc/ld.so.conf
sudo echo "/usr/local/lib">>/etc/ld.so.conf  
sudo echo "/usr/lib">>/etc/ld.so.conf    
sudo ldconfig

# 再把/etc/ld.so.conf 的权限修改回来
sudo chmod 544 /etc/ld.so.conf 
```
再次运行 `protoc --version`, 结果成功了！<br />
!["protoc_version2"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/protoc_version2.png "protoc_version2")<br />


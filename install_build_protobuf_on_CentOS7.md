在Linux下安装、编译protocol buffer
=======
## 环境： UBuntu 16.04 , 64bit
* 拷贝protobuf tar包到UBuntu下：
	* 在UBuntu16.04上安装ftp服务器：
	```shell
	sudo apt-get install vsftpd
	```
	!["vsftpd"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/vsftpd.png "vsftpd")<br />
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

<br /><br /><br />
参考文档: [Google protobuf in Linux](https://stackoverflow.com/questions/2456664/google-protobuf-in-linux)<br />
!["stackoverflow"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/stackoverflow.png "stackoverflow")<br />

****
## 接下来，我们写一个小demo来测试以下protobuf的使用情况：
### 首先，写一个 `lm.person.proto` 文件:
一个比较好的习惯是认真对待 proto 文件的文件名。比如将命名规则定于如下：`packageName.MessageName.proto` <br />
##### lm.person.proto文件：
```shell
syntax = "proto3";
package lm; 
message Person 
{ 
   string name = 1;  // proto3里，所有字段全是optional
   stringemail = 2;  // 邮箱 
   int32 age = 3;  //年龄
}
```
### 编译 `lm.person.proto` 文件:
```shell
protoc -I=./ --cpp_out=./ ./lm.person.proto
```
!["build_proto"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/build_proto.png "build_proto")<br />

### 编写 writer.cpp 和 Reader.cpp
**writer.cpp**内容如下：<br />
```shell
#include <iostream>
#include <fstream>
#include "lm.helloworld.pb.h"

using namespace std;
 
int main(void) 
{ 
	lm::Person msg1; 
	msg1.set_name("tycao"); 
	msg1.set_age(25);
	msg1.set_email("616881845@qq.com");
	 
	// Write the Person's info to disk. 
	ofstream output("./log"); 
		 
	if (!msg1.SerializeToOstream(&output)) { 
	  cerr << "Failed to write msg." << endl; 
	  return -1; 
	} 
	return 0; 
}
```


****
## 环境： CentOS 7.4, 64bit
* 解压protobuf 安装包
```shell
tar -zxvf protobuf-cpp-3.2.0.tar.gz
yum install glibc-headers
yum install gcc-c++
pwd
cd /home/wwwroot/ftptest/
ll
cd protobuf-3.2.0/
./configure
make
make install
ldconfig
protoc --version


find / -name "test.proto"
protoc --version
pwd
ll
vi test.proto
ll
chmod 777 test.proto
ll
mv test.proto lm.Person.proto
ll
protoc -I=./ --cpp_out=./ ./lm.Person.proto
vi lm.Person.proto
protoc -I=./ --cpp_out=./ ./lm.Person.proto
vi lm.Person.proto
protoc -I=./ --cpp_out=./ ./lm.Person.proto
ll
vi Writer.cpp
touch log
chmod 777 log
ll
chmod 775 Writer.cpp
ll
vi Writer.cpp
g++ -std=c++11 Writer.cpp -o ./Writer
vi Writer.cpp
g++ -std=c++11 Writer.cpp -o ./Writer
vi Writer.cpp
ll
vi Writer.cpp
g++ -std=c++11 Writer.cpp -o ./Writer -pthread
g++ lm.Person.pb.cc Writer.cpp -o ./Writer `pkg-config --cflags --libs pr otobuf` -lpthread
ll
g++ lm.Person.pb.cc Writer.cpp -o ./Writer  -lpthread
g++ lm.Person.pb.cc Writer.cpp -o ./Writer `pkg-config --cflags --libs pr otobuf` -lpthread
g++ lm.Person.pb.cc Writer.cpp -o ./Writer
g++ ./lm.Person.pb.cc ./Writer.cpp -o ./write -lpthread -lprotocol
g++ ./lm.Person.pb.cc ./Writer.cpp -o ./write -lpthread -lprotobuf
ll
./write
ldconfig
./write
cd /usr/local/lib
ll
vi /etc/ld.so.conf
/sbin/ldconfig -v
cd -
./write
cat log
vi log
g++ ./lm.Person.pb.cc ./Writer.cpp -o ./write -lpthread -lprotocol
g++ ./lm.Person.pb.cc ./Writer.cpp -o ./write -lpthread -lprotobuf
protoc -I=./ --cpp_out=./ ./lm.Person.proto
ll
cd /home/wwwroot/ftptest/
vi Writer.cpp
vi Reader.cpp
chmod 775 Reader.cpp
g++ ./lm.Person.pb.cc ./Reader.cpp -o ./reader -lpthread -lprotobuf
./reader


```









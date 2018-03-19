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
**read.cpp**内容如下:<br />
```shell
#include <iostream>
#include <fstream>
#include "test.pb.h"

using namespace std;

// get Person's info from disk
void ListMsg(const csx::Person & msg)
{
        cout << msg.name() << endl;
        cout << msg.age() << endl;
        cout << msg.email() << endl;
}

int main(int argc, char* argv[])
{
        csx::Person msg1;
        {
                fstream input("./log", ios::in | ios::binary);
                if (!msg1.ParseFromIstream(&input)) {
                  cerr << "Failed to parse address book." << endl;
                  return -1;
                }
        }
        ListMsg(msg1);
}

```
### 编译`write.cpp` 和 `read.cpp`:
```shell
g++ ./test.pb.cc ./write.cpp -o write -lpthread -lprotobuf
g++ ./test.pb.cc ./read.cpp -o read -lpthread -lprotobuf
```

****
### Ubuntu16.04上貌似只能编译过proto2,proto3在g++编译时会报错.所以我又重新下载了protocol buffer 2-6-1:
```shell
wget https://github.com/google/protobuf/releases/download/v2.6.1/protobuf-2.6.1.tar.gz
```
!["protobuf_2_6_1"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/protobuf_2_6_1.png "protobuf_2_6_1")<br />

### test.proto的内容修改为proto2的语法：
```shell
syntax = "proto2";
package csx;

message Person {
    optional string  name  = 1;
    optional int32   age   = 2;
    optional string  email = 3;
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

### 首先，运行以下命令：
```shell
yum install glibc-headers
yum install gcc-c++
```
### 然后进入 `protobuf-3.5.1/` 目录
```shell
cd protobuf-3.5.1/
```

### 进入`protobuf-3.5.1/` 目录之后，运行以下命令：
```shell
./configure
make		# 编译protocol buffer, 需要等待一段时间
make check
make install
ldconfig
```

### 测试protocol buffer是否安装成功：
```shell
protoc --version
```
!["protoc_version3"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/protoc_version3.png "protoc_version3")<br />


### 接下来，写一个小的测试程序,来验证protocol buffer的使用情况：
```shell
touch test.proto
chmod 777 test.proto
vi test.proto
```

在test.proto里填写以下内容：
```shell
syntax = "proto3";
package csx;

message Person {
    string  name  = 1;
	int32   age   = 2;
	string  email = 3;
}
```

接下来，运行以下程序生成`test.pb.cc` 和 `test.pb.h`：
```shell
protoc -I=./ --cpp_out=./ ./test.proto
```
!["test_proto"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/test_proto.png "test_proto")<br />

### 编写`write.cpp`:
```shell
touch write.cpp
chmod 777 write.cpp
vi write.cpp
```
在 `write.cpp` 里填写以下内容：
```shell
#include <iostream>
#include <fstream>
#include "test.pb.h"

using namespace std;

int main(void)
{
        csx::Person msg1;
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

#### 编译 `write.cpp`:
```shell
g++ ./test.pb.cc ./write.cpp -o ./write -lpthread -lprotobuf
```
上述编译命令，会生成write可执行文件。我们运行此write文件：
```shell
./write
```
发现报错了：报错信息是 `./write: error while loading shared libraries: libprotobuf.so.15: cannot open shared object file: No such file or directory`, 即`无法找到静态库libprotobuf.so.15`<br />
!["write"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/write.png "write")<br />

**解决方法是**：<br />
```shell
vi /etc/ld.so.conf
```
在/etc/ld.so.conf里添加如下内容：
```shell
/usr/local/lib
/usr/lib
```
然后运行 `ldconfig`。

Alternatively, 或者是运行如何命令：
```shell
echo "/usr/local/lib">>/etc/ld.so.conf
echo "/usr/lib">>/etc/ld.so.conf
idconfig
```

### 接下来再次运行./write是，就成功了！


### 编写`read.cpp`:
```shell
touch read.cpp
chmod 777 read.cpp
vi read.cpp
```
`read.cpp`的内容填写如下：
```shell
#include <iostream>
#include <fstream>
#include "test.pb.h"

using namespace std;

// get Person's info from disk
void ListMsg(const csx::Person & msg)
{
        cout << msg.name() << endl;
        cout << msg.age() << endl;
        cout << msg.email() << endl;
}

  
int main(int argc, char* argv[]) 
{ 
	csx::Person msg1; 
	{ 
		fstream input("./log", ios::in | ios::binary); 
		if (!msg1.ParseFromIstream(&input)) { 
		  cerr << "Failed to parse address book." << endl; 
		  return -1; 
		}
	}
	ListMsg(msg1); 
}
```

接下来，编译`read.cpp`文件：
```shell
g++ ./test.pb.cc ./read.cpp -o read -lpthread -lprotobuf
```
上述命令生成read可执行文件。 运行`./read`得到如下信息：<br />
!["result"](https://github.com/tycao/tycao.github.io/blob/master/install_and_build_protobuf_in_Linux/result.png "result")<br />



















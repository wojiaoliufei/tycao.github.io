Protocol Buffer : 一种轻便高效的结构化数据存储格式,可以用于结构化数据串行化，或者说序列化。
======
### Protocol Buffer （简称pb）它很适合做数据存储或 RPC 数据交换格式。可用于通讯协议、数据存储等领域的语言无关、平台无关、可扩展的序列化结构数据格式。   官网请戳这里→[Protocol Buffer Github官网](https://github.com/google/protobuf)<br />
#### 因为最近在做量化交易系统，因为数据传输效率快，因此选用Google 内部使用的数据传输协议格式（现已开源）protocol buffer。
#### 好了，废话不多说！接下来，讲解以下如何下载安装编译protocol buffer,以及如何使用它进行数据传输。

* 开发环境 :
	* windows 7，64bit
* 开发工具：
	* [cmake图形化工具](https://pan.baidu.com/s/1ggmOZar)<br /> 【链接：https://pan.baidu.com/s/1ggmOZar 密码：tswr】
	* Visual Studio 2013 ultimate版本

* 下载：
	* 去 [Github官网下载](https://github.com/google/protobuf/releases) 最新版本的protocol buffer源码。
	!["download_01"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/download_01.png "download_01")
	!["download_02"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/download_02.png "download_02")
	* 下载好之后，解压文件到指定目录下：
	!["unzip"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/unzip.png "unzip")
* 编译：
	* 使用cmake工具编译源代码：
	!["build_cmake"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/build_cmake.png "build_cmake")
	在 **_where the source is_**  一栏填写 **_C:/Users/Administrator/Downloads/protobuf-cpp-3.5.1/protobuf-3.5.1/cmake_** （protocol buffer的具体目录视自己的而定）
	* 选择本地的VS版本（不要搞错，很重要！）。我的是Win64 visual studio 12 2013:
	!["select"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/select.png "select")
	* 编译完成如下：
	!["build_done"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/build_done.png "build_done")
	* 看一下编译后，生成的文件：
	!["solution"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/solution.png "solution")
* 安装：
	* 点击打开解决方案：
	!["project_tree"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/project_tree.png "project_tree")
	* 右键点击libprotocolbuf.lib，点击生成：
	!["libprotocolbuf"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/libprotocolbuf.png "libprotocolbuf")
	* 如上一步操作一致，右键点击protoc，点击生成
	* 注意这是visual studio 2013默认在x64平台下的Debug情况下操作的。所以之后创建新的工程，引用protocol buffer 库时，必须也是x64下的Debug:
	!["debug"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/debug.png "debug")
	* 看一下生成了什么新的文件：多出来Debug目录，该目录下多出来几个库文件：libprotocolbufd.lib是我们待会需要用到的（注意：release下生成的时libprotocolbuf.lib）。
	!["debug_result"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/debug_result.png "debug_result")
	* 在该目录下新建一个以.proto为后缀的文件：DEMO.proto
	!["DEMO"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/demo.png "DEMO")
	DEMO.proto的内容如下：
		```cpp	
				syntax = "proto3";
				package tycao;
				message Person
				{
					string name=1;	// 姓名
					int32 age=2;	// 年龄
					string email=3;	// 邮箱地址
				}
		```		
	* 打开cmd命令行窗口，进入该目录下，运行如下命令：
		**_protoc.exe --cpp_out=./ DEMO.proto_**
	!["cmd"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/cmd.png "cmd")
	* 运行了上述命令后，会生成两个新文件：DEMO.pb.cc  DEMO.pb.h
	!["ret"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/ret.png "ret")
* 创建新项目，引用上述得到的protocol buffer 文件：DEMO.pb.cc  DEMO.pb.h
	!["run_success"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/run_success.png "run_success")
	* 配置项目：右键点击项目名称，点击属性：
		* 属性→VC++目录→包含目录：
	!["001"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/001.png "001")
		* 属性→链接器→常规→附加库目录：
	!["002"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/002.png "002")
		* 属性→链接器→输入→附加依赖项：
	!["003"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/003.png "003")
	* 程序运行结果：
	!["project_ret"](https://github.com/tycao/tycao.github.io/blob/master/protobuf_src/project_ret.png "project_ret")
	
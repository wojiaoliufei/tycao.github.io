本章讲述如何提升MySQL插入操作的速度
=======
### 大家都知道，MySQL是免费开源的关系型数据库。因为开源，所以很多国内大厂都在使用MySQL数据库，进行存储数据
* 开发环境：
	* Windows 7, 64bit
	* Visual Studio 2013
	* MySQl 版本：
	![mysql_version](https://github.com/tycao/tycao.github.io/blob/master/src/mysql_version.png "mysql_version")
	* gcc 版本：
![gcc_version](https://github.com/tycao/tycao.github.io/blob/master/src/gcc_version.png "gcc_version")

	

	
* 项目步骤：
	* 创建一个空项目：
	* 将 *C:\wamp64\bin\mysql\mysql5.7.19\include* 路径添加到项目的包含目录中。（根据具体路径而定）
	![mysql_include](https://github.com/tycao/tycao.github.io/blob/master/src/MySQL_include.png "mysql_include")
	* 将 *C:\wamp64\bin\mysql\mysql5.7.19\lib* 路径添加到项目的库目录中。（根据具体路径而定）
	![mysql_lib](https://github.com/tycao/tycao.github.io/blob/master/src/MySQL_lib.png "mysql_lib")
	* 添加libmysql.lib至附加依赖项中
	![mysql_lib2](https://github.com/tycao/tycao.github.io/blob/master/src/MySQL_lib2.png "mysql_lib2")
	* （ *以上两步* 也可以在程序代码的开始处加上 _#pragma comment(lib,"C:\\wamp64\\bin\\mysql\\mysql5.7.19\\lib\\libmysql.lib")_ 来导入libmysql.lib）
	![mysql_lib3](https://github.com/tycao/tycao.github.io/blob/master/src/MySQL_lib3.png "mysq_lib3")
	* 如果使用的mysql是64位的，还需要将项目的解决方案平台由win32改成x64
	![32bit_to_64bit](https://github.com/tycao/tycao.github.io/blob/master/src/32bit_to_64bit.png "32bit_to_64bit")
	* 将 *C:\wamp64\bin\mysql\mysql5.7.19\lib* （根据具体路径）下的libmysql.dll复制到项目中去，和.cpp，.h文件位于同一路径下。
	![mysql_dll](https://github.com/tycao/tycao.github.io/blob/master/src/mysql_dll.png "mysql_dll")
	
至此，相关配置全部完成！

### 接下来，我们开始讲解如何用C++去优化MySQL插入的速度
#### 项目只创建了一个main.cpp文件，项目结构如下：
![project](https://github.com/tycao/tycao.github.io/blob/master/src/project.png "project")
#### 先放出代码如下：
```cpp
#include <iostream>
#include <winsock2.h>
#include <string>
#include <ctime>

#include "mysql.h"

// 若配置了库目录，则可以忽略下面这一行代码
//#pragma comment(lib, "C:\\wamp64\\bin\\mysql\\mysql5.7.19\\lib\\libmysql.lib")

using namespace std;

int main()
{
	MYSQL mysql;
	mysql_init(&mysql); // 初始化

	MYSQL *ConnStatus = mysql_real_connect(&mysql, "localhost", "root", "", "sky", 3306, 0, 0);
	if (ConnStatus == nullptr)
	{
		// 连接失败
		int i = mysql_errno(&mysql);
		string strError = mysql_error(&mysql);
		cout << "Error info: " << strError << endl;

		return 0;
	}

	cout << "Mysql Connected..." << endl;

	string strsql;
	MYSQL_RES *result = nullptr; // 数据结果集

	// 插入操作
	strsql = "insert into t1 set name = 'sky'";

	clock_t t1 = clock();

	mysql_query(&mysql, "START TRANSACTION"); // 开启事务， 如果没有开启事务，那么效率会变得非常低下！

	for (int i = 0; i<10000; i++)
	{
		mysql_query(&mysql, strsql.c_str());
	}

	mysql_query(&mysql, "COMMIT");   // 提交事务
	//mysql_commit(&mysql);
	clock_t t2 = clock();
	cout << "insert end\n" 
		<< "Cost time : " << (t2 - t1) / 1000.
		<< endl;

	//释放结果集 关闭数据库
	mysql_free_result(result);
	mysql_close(&mysql);
	mysql_library_end();

	return 0;
}
```
### 程序运行结果如下：
![output](https://github.com/tycao/tycao.github.io/blob/master/src/mysql_cost_time.png "output")

最后，发现MySQL的插入速度很慢，10000条插入数据，平均下来用了1.56s，但是SQLite 是 10w条插入数据/s。下次把SQLite的测试demo也发出来。以供自己以后查看，当然也是给大家参考。


## 最后，附上本次工程的源码：
[测试MySQL插入操作性能的源码](https://github.com/tycao/opencvgit/tree/master/MySQL)<br />

快乐学习~快乐编程~
------------
## C++代码操作MySQL数据库插入操作的优化过程：
* 参考文档：
	* [C++代码操作MySQL数据库总结](https://www.cnblogs.com/joeblackzqq/p/4332945.html)
	* [C++操作mysql大量数据插入效率低下的解决方法](http://www.codeweblog.com/c-%E6%93%8D%E4%BD%9Cmysql%E5%A4%A7%E9%87%8F%E6%95%B0%E6%8D%AE%E6%8F%92%E5%85%A5%E6%95%88%E7%8E%87%E4%BD%8E%E4%B8%8B%E7%9A%84%E8%A7%A3%E5%86%B3%E6%96%B9%E6%B3%95/)

	
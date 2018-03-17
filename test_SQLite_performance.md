SQLite性能测试以及优化策略（使用SQlite源码）
-----------
* 开发环境
	* Windows 7, 64bit
	* Visual studio 2013
	* SQLite3源码

### 去SQLite官网下载最新版本的SQLite源码：	=> [SQLite官网](http://www.sqlite.org)<br />
![portal_site](https://github.com/tycao/tycao.github.io/blob/master/sqlite_src/download.png "portal_site")

### 下载好之后，解压之后的源代码：
![unzip](https://github.com/tycao/tycao.github.io/blob/master/sqlite_src/source_code.png "unzip")

### 新建一个空项目：
![project](https://github.com/tycao/tycao.github.io/blob/master/sqlite_src/empty_project.png "project")

### 创建入口实现文件（main.cpp）:


### 将sqlite3.c 和 sqlite3.h文件拷贝到工程目录下：
![copy_sqlite3_to_project](https://github.com/tycao/tycao.github.io/blob/master/sqlite_src/copy_sqlite3.png "copy_sqlite3_to_project")


### 项目只有三个文件：main.cpp, sqlite3.h, sqlite3.c
![tree](https://github.com/tycao/tycao.github.io/blob/master/sqlite_src/tree.png "tree")

### 先把完整的工程代码贴上来：
```cpp
#include <iostream>  
#include <string>  
#include <sstream>  
#include <time.h>  
#include "sqlite3.h"  

const int nCount = 500000 * 2;

int main(int argc, char** argv)
{
	sqlite3* db;
	sqlite3_open("testdb.db", &db);
	sqlite3_exec(db, "PRAGMA synchronous = OFF; ", 0, 0, 0);
	sqlite3_exec(db, "drop table if exists t1", 0, 0, 0);
	sqlite3_exec(db, "create table t1(id integer,x integer,y integer ,weight real)", 0, 0, 0);
	clock_t t1 = clock();

	sqlite3_exec(db, "begin;", 0, 0, 0);
	sqlite3_stmt *stmt;
	const char* sql = "insert into t1 values(?,?,?,?)";
	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, 0);

	for (int i = 0; i<nCount; ++i)
	{
		// std::stringstream ssm;  
		// ssm<<"insert into t1 values("<<i<<","<<i*2<<","<<i/2<<","<<i*i<<")";  
		// sqlite3_exec(db,ssm.str().c_str(),0,0,0);  
		sqlite3_reset(stmt);
		sqlite3_bind_int(stmt, 1, i);
		sqlite3_bind_int(stmt, 2, i * 2);
		sqlite3_bind_int(stmt, 3, i / 2);
		sqlite3_bind_double(stmt, 4, i*i);
		sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	sqlite3_exec(db, "commit;", 0, 0, 0);
	clock_t t2 = clock();

	sqlite3_close(db);

	std::cout << "cost tima: " << (t2 - t1) / 1000. << "s" << std::endl;

	return 0;
}
```
上面的代码是通过极速优化后的代码，能够极速提升SQlite的数据插入效率 ： 包括 开启事务等

### Release情况下运行程序后的结果是：
![tree](https://github.com/tycao/tycao.github.io/blob/master/sqlite_src/result.png "tree")

### 下面是debug情况下的运行结果：
![debug](https://github.com/tycao/tycao.github.io/blob/master/sqlite_src/debug.png "debug")

### 可以看到，Release情况下，我们测试插入nCount = 1000000次时，才用了0.7秒多（release下）！！！比MySQL快多了！


~快乐学习 快乐编程~
------
参考文档： [提升SQLite数据插入效率低、速度慢的方法](http://blog.csdn.net/majiakun1/article/details/46607163)<br />



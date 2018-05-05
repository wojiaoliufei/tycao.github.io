#include "manager.h"
#include <iostream>

int main() {
	SybaseManager obj("192.168.1.107:1433", "sa", "1", "hft", 1433);
	obj.initConnection();
	
	obj.runSQLCommand("select * from csx");
//	obj.runSQLCommand("select * from demo");
//	obj.runSQLCommand("create table csx(First int, Second char(20), Third char(10))");
//	obj.runSQLCommand("insert into csx(First, Second, Third) values(100000, '123456789012345678901234567890', '12345678901234567890')");
//	obj.runSQLCommand("insert into demo(T1, T2, T3) values(30, 'This is a test for table demo', '616881845@qq.com111111111111111111111111111111')");
	
	auto ret = obj.getResult();

	for (auto i : ret) {
		for (auto j : i) {
		//	printf("%s ", j);
			std::cout << j << "**************";
		}
		printf("\n");
	}
}

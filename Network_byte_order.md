主机字节序和网络字节序的转换
=====
### 题记：最近在参与的项目（高频量化交易系统）里，设计到各个模块之间的通讯，比如客户端和量化交易网关之间的传输层都是基于TCP通讯的，但是应用协议层是用的htpp_protocol协议（一种我们组自定义的通讯协议数据传输格式）。当涉及到底层的TCP通讯时，就会自然而然想到数据是如何在各个机器上传输的，其中当然就少不了对 *网络字节序* 、 *主机字节序* 、 *大端字节序* 、 *小端字节序* 的讨论。

## 一、大小端字节序模式
不同的CPU有不一样的字节序类型（ **_大端字节序：_** 高位数据存储在低位内存中，低位数据存储在高位内存中。 **_小端字节序：_** 高位数据存储在高位内存中，低位数据存储在低位内存中。）。 **这些字节序是指整数在内存中保存的顺序：这就叫做主机字节序。**
最常见的就是以下两种：
* _**大端字节序（big endian）：**_ 高位数据存储在低位内存中，低位数据存储在高位内存中。 （即 将低序字节存储在起始内存地址）
* _**小端字节序（little endian）：**_ 高位数据存储在高位内存中，低位数据存储在低位内存中。（即 将高序字节存储在起始内存地址）

!["le_be"](https://github.com/tycao/tycao.github.io/blob/master/src_20180208/le_be.png "le_be")<br />

并且我们还可以通过以下程序去验证我们自己的电脑主机是哪一种字节序排列：

Linux 环境下：

```cpp
#include <stdio.h>  
#include <arpa/inet.h>  
  
int main() {
	unsigned long a = 0x12345678;  
	unsigned char *p = (unsigned char *)(&a);  

	printf("主机字节序:%0x    %0x   %0x   %0x\n",  p[0], p[1], p[2], p[3]);  

	unsigned long b = htonl(a);  //将主机字节序转化成了网络字节序  
	  
	p = (unsigned char *)(&b);  

	printf("网络字节序:%0x    %0x   %0x   %0x\n",  p[0], p[1], p[2], p[3]);  
	return 0;  
}
```
程序运行结果如下：
!["ret"](https://github.com/tycao/tycao.github.io/blob/master/src_20180208/ret.png "ret")<br />

由上图可知，我自己的虚拟机上的XBuntu系统的字节存储序列是： 小端字节序--高位数据存储在高位内存中，低位数据存储在低位内存中。


细心的同学可能已经堆上述短短几行代码产生兴趣了：**_那个htonl(unsigned int) 库函数是什么作用？_** （黑人问号脸=。=）
那么下面开始逐一讲解这个函数及其关联函数：
* **_htons:_** 
	* 把unsigned short类型从主机序转换到网络序
* **_htonl:_** 
	* 把unsigned long类型从主机序转换到网络序
* **_ntohs:_** 
	* 把unsigned short类型从网络序转换到主机序
* **_ntohl:_** 
	* 把unsigned long类型从网络序转换到主机序

## 二、模拟htonl、ntohl、htons、ntohs函数具体解释
接下来，我们可以重新实现这四个函数

```cpp

// 类型别名
typedef unsigned short int uint16;
typedef unsigned long int uint32;


// 短整型大小端互换
#define BigLittleSwap16(A)  ((((uint16)(A) & 0xff00) >> 8) | /
							 (((uint16)(A) & 0x00ff) << 8))

 

// 长整型大小端互换
#define BigLittleSwap32(A)  ((((uint32)(A) & 0xff000000) >> 24) | /
							 (((uint32)(A) & 0x00ff0000) >> 8) | /
							 (((uint32)(A) & 0x0000ff00) << 8) | /
							 (((uint32)(A) & 0x000000ff) << 24))

 

// 本机大端返回1，小端返回0
int checkCPUendian()
{
   union	// 联合：数据成员共享同一块内存（栈内内存）
   {
	  unsigned long int i;
	  unsigned char s[4];
   } c;
   
   c.i = 0x12345678;
   return (0x12 == c.s[0]);
}

 

// 模拟htonl函数，本机字节序转网络字节序
unsigned long int HtoNl(unsigned long int h)
{
   // 若本机为大端，与网络字节序同，直接返回
   // 若本机为小端，转换成大端再返回
   return checkCPUendian() ? h : BigLittleSwap32(h);
}

 

// 模拟ntohl函数，网络字节序转本机字节序
unsigned long int NtoHl(unsigned long int n)
{
   // 若本机为大端，与网络字节序同，直接返回
   // 若本机为小端，网络数据转换成小端再返回
   return checkCPUendian() ? n : BigLittleSwap32(n);
}

 

// 模拟htons函数，本机字节序转网络字节序
unsigned short int HtoNs(unsigned short int h)
{
   // 若本机为大端，与网络字节序同，直接返回
   // 若本机为小端，转换成大端再返回
   return checkCPUendian() ? h : BigLittleSwap16(h);
}

 

// 模拟ntohs函数，网络字节序转本机字节序
unsigned short int NtoHs(unsigned short int n)
{
	// 若本机为大端，与网络字节序同，直接返回
	// 若本机为小端，网络数据转换成小端再返回
	return checkCPUendian() ? n : BigLittleSwap16(n);
}
```





## 三、不同的CPU上运行不同的操作系统，字节序也是不同的，参见下表：
| 处理器 | 操作系统 | 字节排序 |
| - | :-: | -: |
| Alpha | 所有操作系统| 小端字节序 |
| HP-PA | NT | 小端字节序 |
| HP-PA | UNIX  | 大端字节序 |
| Intelx86 | 所有操作系统 | Little endian <-----x86系统是小端字节序系统 |
| Motorola680x() | 所有操作系统 | 大端字节序 |
| MIPS | NT | 小端字节序 |
| MIPS | UNIX | 大端字节序 |
| PowerPC | NT | 小端字节序 |
| PowerPC | 非NT | 大端字节序  <-----PPC系统是大端字节序系统 |
| RS/6000 | UNIX | 大端字节序 |
| SPARC | UNIX | 大端字节序 |
| IXP1200 ARM核心 | 所有操作系统 | 小端字节序 |






+ 参考文章：
	+ [主机字节序与网络字节序的转换函数：htonl、ntohl、htons、ntohs](http://blog.csdn.net/kulala082/article/details/53431473)<br />
	+ [网络字节序和主机字节序详解！！！](http://blog.csdn.net/msdnwolaile/article/details/50727653)<br />





	
	
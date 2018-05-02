linux 环境变量设置方法总结（PATH／LD_LIBRARY_PATH）
==============
### PATH:  可执行程序的查找路径
查看当前环境变量:

echo $PATH

设置: <br />

#### 方法一： export PATH=PATH:/XXX 但是登出后就失效

#### 方法二：修改~/.bashrc或~/.bash_profile或系统级别的/etc/profile

* 在其中添加例如export PATH=/opt/ActivePython-2.7/bin:$PATH

* source .bashrc  (Source命令也称为“点命令”，也就是一个点符号（.）。source命令通常用于重新执行刚修改的初始化文件，使之立即生效，而不必注销并重新登录)

### LD_LIBRARY_PATH: 动态库的查找路径
设置：<br />

#### 方法一： export  LD_LIBRARY_PATH=LD_LIBRARY_PATH:/XXX 但是登出后就失效

#### 方法二：  修改~/.bashrc或~/.bash_profile或系统级别的/etc/profile

* 在其中添加例如export PATH=/opt/ActiveP/lib:$LD_LIBRARY_PATH

* source .bashrc  (Source命令也称为“点命令”，也就是一个点符号（.）。source命令通常用于重新执行刚修改的初始化文件，使之立即生效，而不必注销并重新登录)

#### 方法三：这个没有修改LD_LIBRARY_PATH但是效果是一样的实现动态库的查找， 

* /etc/ld.so.conf下面加一行/usr/local/lib

* 保存过后ldconfig一下（ldconfig 命令的用途,主要是在默认搜寻目录(/lib和/usr/lib)以及动态库配置文件/etc/ld.so.conf内所列的目录下,搜索出可共享的动态链接库(格式如前介绍,lib*.so*),进而创建出动态装入程序(ld.so)所需的连接和缓存文件.缓存文件默认为/etc/ld.so.cache,此文件保存已排好序的动态链接库名字列表.）

**方法三设置稍微麻烦，好处是比较不受用户的限制。**


***********
### 第一种方法：
运行命令 `ls -alrt ~/.bash` 使用tap键补全命令，会得到以`.bash`开头的如下几个重要文件：<br />
```shell
.bash_history
.bash_logout
.bash_profile
.bashrc
```

开机自动运行的程序，就可以把绝对路径放在 `.bashrc` 或者 `.bash_profile` 里面。<br />
```shell
vim ~/.bashrc  或者
vim ~/.bash_profile

# 添加如下内容：
PATH=${PATH}:${HOME}/bin:${HOME}/.local/bin  # 想要添加的程序路径 都可以在尾后添加 ":绝对路径"
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${HOME}/路径.../lib		# 想要添加库路径 都可以在尾后添加 ":绝对路径"
```
### 第二种方法：
直接在终端运行如下命令：<br />
```shell
export PATH=${PATH}:路径1:路径2		# 想要添加的程序路径 都可以在尾后添加 ":绝对路径"
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:库路径1:库路径2		# 想要添加库路径 都可以在尾后添加 ":绝对路径"

```

******
### 参考链接：
[linux 环境变量设置方法总结（PATH／LD_LIBRARY_PATH）](https://blog.csdn.net/wangeen/article/details/8159500)<br />

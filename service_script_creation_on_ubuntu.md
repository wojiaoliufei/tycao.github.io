ubuntu 服务脚本编写
===========
* 主要步骤
	* 配置服务启动脚本
	* 配置命令处理脚本
	* 开机自启
### 配置服务启动脚本
**在ubuntu 16.04中,服务的目录为`/lib/systemd/system`。我们现在要建立一个名为`caosx`的服务，就在此目录下添加一个文件名为`caosx.service`的文件即可。** 其内容包含：<br />
```shell
[Unit]
Description=xxxxxxxxxxxxxxxx #描述服务 
After=network.target #用于指定服务启动的前置条件
Documentation=  #帮助文件的地址如http://baidu.com/ ，可缺省

[Service]
# User=  启动用户  
# Group=  启动用户组
ExecStart=  #服务启动命令，此项必填
# ExecStop=  服务终止命令，可缺省


[Install] #用来定义如何启动，以及是否开机启动。
WantedBy=multi-user.target #当服务开机启动后，会放入什么文件夹，影响启动顺序
```

**根据上述语法规则，现在我们举一个例子，编写一个自定义的服务脚本caosx.service**。其内容如下：<br />
#### /lib/systemd/system/caosx.service
* 创建服务脚本：
```shell
touch /lib/systemd/system/caosx.service
chmod 777 /lib/systemd/system/caosx.service
vi /lib/systemd/system/caosx.service
```

打开`/lib/systemd/system/caosx.service`文件后，输入一下内容：<br />

```shell
[Unit]
Description=My Fucking Service	# 描述
After=network.target

[Service]
ExecStart=/root/server_http	# 需要运行的路径
SuccessExitStatus=143	# 成功时返回的状态
TimeoutStopSec=10
Restart=on-failure	# 非正常dead，自动重启
RestartSec=5	# 5秒后启动


[Install]
WantedBy=multi-user.target
```
至此，服务脚本已经创建完成！

:warning: **需要注意的是， 服务启动命令需要输入绝对路径的形式，因为在服务启动时，可能相关的环境变量还未加载。**


### 在 `/lib/systemd/system` 路径下添加此文件并保存为`caosx.service`后，就可以通过 `systemctl start caosx` 命令启动服务了：<br />
!["service_script_01"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/service_script_01 "service_script_01")<br />









***********
### 参考连接：https://aak1247.coding.me/java-jar-as-service.html
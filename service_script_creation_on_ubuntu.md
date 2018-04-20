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

**根据上述语法规则，现在我们举一个例子，编写一个自定义的服务脚本`caosx.service`**。其内容如下：<br />
#### `caosx.service`的文件路径： `/lib/systemd/system/caosx.service`
* 创建服务脚本：
```shell
touch /lib/systemd/system/caosx.service
chmod 777 /lib/systemd/system/caosx.service
vi /lib/systemd/system/caosx.service
```

打开`/lib/systemd/system/caosx.service`文件后，输入下面的内容：<br />

```shell
[Unit]
Description=My Fucking Service	# 描述
After=network.target

[Service]
ExecStart=/root/server_http	# 需要运行的路径
SuccessExitStatus=143	# 成功时返回的状态
TimeoutStopSec=10
Restart=always	# 非正常dead，自动重启
RestartSec=5	# 5秒后启动


[Install]
WantedBy=multi-user.target
```
至此，服务脚本已经创建完成！

:warning: 
* 需要注意的是， 服务启动命令需要输入绝对路径的形式，因为在服务启动时，可能相关的环境变量还未加载。
* 上述内容中，我把自己的前段时间的`实现简单的web服务项目`放在了`/root目录下。` 即 `/root/server_http`是一个轻量型的web可执行程序

# 上述内容中 `Restart=always`表示我们可以通过`ps -ef | grep 进程名称`得到启动的进程pid, 使用`kill -9 pid`。这样，过了`RestartSec=5`秒后，再次运行`ps -ef | grep 进程名称`,就会发现 `进程被自动再次启动了！` 这就是本次服务脚本的核心作用！！！

### 完成了caosx.service文件的创建后：需要依次运行以下命令：
```shell
systemctl daemon-reload
systemctl enable caosx.service 

# 接下来的命令不分顺序，用来查询、停止，开启服务
systemctl status caosx.service  或者 systemctl status caosx
systemctl start  caosx.service  或者 systemctl start  caosx
systemctl stop caosx.service    或者 systemctl stop   caosx
```


### 在 `/lib/systemd/system` 路径下添加此文件并保存为`caosx.service`后，就可以通过 `systemctl start caosx` 命令启动服务了：<br />
!["service_script_01"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/service_script_01.png "service_script_01")<br />
!["service_script_02"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/service_script_02.png "service_script_02")<br />



### history命令：
```shell
392  vi caosx.service 
  393  systemctl daemon-reload
  394  systemctl enable caosx.service 
  395  systemctl status caosx.service 
  396  systemctl start caosx.service 
  397  systemctl status caosx.service 
  398  vi caosx.service 
  399  systemctl status caosx.service 
  400  systemctl daemon-reload
  401  systemctl status caosx.service 
  402  systemctl start caosx.service 
  403  systemctl status caosx.service 
  404  systemctl stop caosx.service 
  405  systemctl status caosx.service 
  406  systemctl start caosx.service 
  407  systemctl status caosx.service 
  408  systemctl stop caosx.service 
  409  systemctl status caosx.service 
  410  vi caosx.service 
  411  systemctl daemon-reload
  412  systemctl start caosx.service 
  413  systemctl status caosx.service 
  414  systemctl stop caosx.service 
  415  systemctl status caosx.service 
  416  vi caosx.service 
  417  systemctl daemon-reload
  418  systemctl status caosx.service 
  419  systemctl start caosx.service 
  420  systemctl status caosx.service 
  421  vi caosx.service 
  422  vi /usr/sbin/shell.sh
  423  ll
  424  systemctl status caosx.service 
  425  ll /usr/sbin/
  426  find / -name "v2*jpg*"
  427  locate v2*jpg*
  428  locate *jpg*
  429  systemctl daemon-reload
  430  systemctl stop caosx.service 
  431  systemctl status caosx.service 
  432  systemctl start caosx.service 
  433  systemctl status caosx.service 
  434  ll /rrot
  435  ll /root
  436  vi caosx.service 
  437  systemctl daemon-reload
  438  systemctl status caosx.service 
  439  systemctl start caosx.service 
  440  systemctl status caosx.service 
  441  systemctl stop caosx.service 
  442  systemctl status caosx.service 
  443  systemctl start caosx.service 
  444  systemctl status caosx.service 
  445  systemctl start caosx.service 
  446  systemctl status caosx.service 
  447  systemctl enable caosx.service 
  448  systemctl status caosx.service 
  449  systemctl start caosx.service 
  450  systemctl status caosx.service 
  451  systemctl daemon-reload
  452  systemctl start caosx.service 
  453  systemctl status caosx.service 
  454  vi /root/mydaemon.sh 
  455  systemctl daemon-reload
  456  systemctl start caosx.service 
  457  systemctl status caosx.service 
  458  systemctl start caosx.service 
  459  cht
  460  vi /root/mydaemon.sh 
  461  systemctl start caosx.service 
  462  systemctl status caosx.service 
  463  cd /mnt/hgfs/share/
  464  ll
  465  cd HTTP/
  466  ll
  467  cp -avrp server_http /root/
  468  cd -
  469  cd /lib/systemd/system
  470  ll
  471  vi caosx.service 
  472  systemctl daemon-reload
  473  systemctl start caosx.service 
  474  systemctl status caosx.service 
  475  systemctl enable caosx.service 
  476  systemctl status caosx.service 
  477  exit
  478  ll /root
  479  vi /root/index/html
  480  touch /root/index.html
  481  chmod 777 /root/index.html 
  482  vi /root/index.html 
  483  systemctl status caosx.service 
  484  mv /root/index.html /lib/systemd/system/
  485  vi /mnt/hgfs/share/HTTP/server_http.h 
  486  vi /mnt/hgfs/share/HTTP/handler.h 
  487  mkdir /root/web
  488  chmod 777 /rootweb
  489  chmod 777 /root/web
  490  mkdir /lib/systemd/system/web
  491  chmod 777 /lib/systemd/system/web
  492  mv /lib/systemd/system/index.html /lib/systemd/system/web/
  493  mv /lib/systemd/system/web/index.html /root/web/
  494  vi caosx.service 
  495  cd /root
  496  ll
  497  cd -
  498  systemctl status caosx.service 
  499  cd ..
  500  systemctl status caosx.service 
  501  cd /home/
  502  systemctl status caosx.service 
  503  cd /home/zogy/
  504  systemctl status caosx.service 
  505  cd /root
  506  systemctl status caosx.service 
  507  systemctl status caosx.service
  508  systemctl stop caosx.service
  509  systemctl status caosx.service
  510  systemctl start caosx.service
  511  systemctl status caosx.service
  512  systemctl stop caosx.service
  513  systemctl status caosx.service
  514  systemctl start caosx.service
  515  systemctl status caosx.service
  516  systemctl stop caosx.service
  517  systemctl status caosx.service
  518  systemctl status caosx
  519  systemctl start caosx
  520  systemctl status caosx
  521  systemctl start caosx
  522  vi /lib/systemd/system/caosx.service 
  523  systemctl status caosx
  524  systemctl stop caosx.service
  525  systemctl daemon-reload
  526  systemctl status caosx
  527  systemctl stop caosx.service
  528  cd /lib/systemd/system
  529  vi caosx.service 
  530  systemctl daemon-reload
  531  systemctl status caosx
  532  vi caosx.service 
  533  systemctl daemon-reload
  534  systemctl status caosx
  535  systemctl daemon-reload
  536  systemctl status caosx.service
  537  systemctl start caosx
  538  systemctl status caosx.service
  539  vi caosx.service 
  540  systemctl daemon-reload
  541  systemctl status caosx.service
  542  systemctl stop caosx.service
  543  systemctl status caosx.service
  544  systemctl start caosx
  545  systemctl status caosx.service
  546  vi caosx.service 
  547  systemctl daemon-reload
  548  systemctl stop caosx.service
  549  systemctl status caosx.service
  550  systemctl start caosx
  551  systemctl status caosx.service
  552  vi caosx.service 
  553  systemctl daemon-reload
  554  systemctl status caosx.service
  555  systemctl stop caosx.service
  556  systemctl status caosx.service
  557  systemctl start caosx
  558  systemctl status caosx.service
  559  systemctl stop caosx
  560  systemctl status caosx.service
  561  systemctl start caosx
  562  systemctl status caosx.service
  563  cat caosx.service 
```

************
CentOS7 上编写服务脚本
===========
### CentOS下的 `systemd 目录` 是在 `/usr/lib/systemd/system`
```shell
cd /usr/lib/systemd/system
touch caosx.service
chmod 777 caosx.service
vi caosx.service
```
进入到`caosx.service`之后，输入以下内容：<br />
```shell
[Unit]
Description=My Fucking Service  # 描述
After=network.target

[Service]
ExecStart=/root/HTTP/server_http        # 需要运行的路径
SuccessExitStatus=143   # 成功时返回的状态
TimeoutStopSec=10
Restart=on-failure      # 非正常dead，自动重启
RestartSec=5    # 5秒后启动


[Install]
WantedBy=multi-user.target
```
!["service_script_03"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/service_script_03.png "service_script_03")<br /><br /><br />

下图是我的另一个机器上的配置 ： **环境不是UBubtu16.04, 而是CentOS7 64bit**， 仅供参考：<br />
!["service_script_02"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/service_script.PNG "service_script_02")<br />
#### 然后，依次运行如下命令：
```shell
systemctl daemon-reload
systemctl enable caosx.service  或者 systemctl enable caosx

# 接下来的命令不分顺序，用来查询、停止，开启服务
systemctl status caosx.service  或者 systemctl status caosx
systemctl start  caosx.service  或者 systemctl start  caosx
systemctl stop caosx.service    或者 systemctl stop   caosx
```

### 即CentOS7下，只有 `system目录` 跟上述的 `UBuntu16.04` 不一样。其它步骤完全一样。
* CentOS7下的 system目录：
	* /usr/lib/systemd/system
* UBuntu16.04下的 systemd目录：
	* /lib/systemd/system











***********
### 参考连接：
* https://aak1247.coding.me/java-jar-as-service.html
* https://blog.csdn.net/dgfj8x57/article/details/61199354

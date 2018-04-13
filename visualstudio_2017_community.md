如何正确安装Visual Studio 2017
=========
* 下载在线安装程序：
[Visual Studio 下载](https://www.visualstudio.com/zh-hans/downloads/)<br /><br />

* 右下角点击 `如何离线安装`：
!["offline_install"](https://github.com/tycao/tycao.github.io/blob/master/src/vs2017_01.png "offline_install")<br />

* 通过正确理解页面里的内容，最终会把你带到这里 :left_point: [离线安装vs 2017](https://docs.microsoft.com/en-us/visualstudio/install/create-an-offline-installation-of-visual-studio)<br />
!["offline_install2"](https://github.com/tycao/tycao.github.io/blob/master/src/vs2017_02.png "offline_install2")<br />

按照上述截图，点击箭头指向的地址之后，就如如下页面：<br />
!["offline_install3"](https://docs.microsoft.com/en-us/visualstudio/install/install-vs-inconsistent-quality-network "offline_install3")<br />

然后，点击安装 visual studio 2017 社区版安装程序： `vs_community.exe`

* 于是就很容易了，先下载`Visual Studio 2017 社区版`的安装程序，然后开个admin权限的cmd输入以下内容：
```shell
		vs_community.exe --layout D:\Fuck --lang en-US
```

保持网络通畅，最好翻个墙（如果你要开发Android或者Xamarin等），等一段时间，30G的东西会下载到`D:\Fuck`里面。以后你把它保存在U盘或者是把目录共享出去，所有人都可以离线安装Visual Studio 2017的任何组件。<br />
!["offline_install4"](https://github.com/tycao/tycao.github.io/blob/master/src/vs2017_04.png "offline_install4")<br /><br />
!["offline_install5"](https://github.com/tycao/tycao.github.io/blob/master/src/vs2017_05.png "offline_install5")<br /><br />




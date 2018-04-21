TrafficMonitor 源码剖析
==========
#### 第一次更新时间：2018-04-22 12:40AM
### 最近在Github上看到一个非常好玩的项目：_TrafficMonitor_。 Github地址 :point_right: [TrafficMonitor开源项目](https://github.com/zhongyang219/TrafficMonitor) 出于兴趣驱动学习的自然规律，最近开始研究源代码，且心得会写在这里。兴趣真是人类最好的老师啊！

于我而言，学习的第一步就是首先要会使用这个工具。等该工具的各个功能都熟悉了之后，巨大的兴趣会驱动你去学习如何实现这些功能。然后接下来的事情就是水到渠成了--- **研究源码。**
我是在visual studio 2017 community版本下，运行的该工具的source code。是作者公开出来的第一个版本v1.66版本，而非最新的v1.72。之后解释为什么不用最新版本。
!["vs2017"](https://github.com/tycao/tycao.github.io/blob/master/src_TrafficMonitor/vs2017.png "vs2017")<br />

#### 运行成功之后的效果图：<br />
!["build_ret"](https://github.com/tycao/tycao.github.io/blob/master/src_TrafficMonitor/build_ret.png "build_ret")<br />
通过上述截图可以看出，这个小工具可以实时监控Windows系统下的`cpu使用率`和`内存使用情况`等等。是不是很好玩！？功能和效果就是类似于你下载一个xx管家一样，会有一个小球悬浮窗运行在屏幕的右下角。




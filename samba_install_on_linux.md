Linux下安装samba （包括 `UBuntu16.04` 和 `CentOS7` ）
===============
**时间：** 2018-05-05 18:00 <br />
**刚刚17:00开始写到17:50的时候，`notepad++` 坑爹的异常退出了。还没来得及push到github上，写的所有的内容全没了。再写就还需要一个小时，已经写了那么久，有点累了。就把安装的整个记录贴上来吧~** <br />

******************
## 环境： CentOS7 64bit
### 注意 <br />
* `netstat -anp | grep smb` 会得到samba服务的端口 <br />
* 安装好samba之后，需要在 `阿里云控制台 -> 安全组` 那里添加139和445端口，那样Windows才能访问Linux下的共享文件夹。 <br />
* CentOS 7 下，samba服务不能通过匿名访问共享文件夹。因此需要创建samba用户和密码。 最重要的一步！（这一点跟UBuntu不一样，UBuntu无需创建samba用户和密码，可以直接匿名访问） <br />
```shell
[root@iZt4n12effj3d79928coatZ ~]# sudo smbpasswd -L -a root
New SMB password:
Retype new SMB password:
Added user root.
[root@iZt4n12effj3d79928coatZ ~]# sudo smbpasswd -L -e root
Enabled user root.
```
!["samba_12"](https://github.com/tycao/tycao.github.io/blob/master/src/samba_12.png "samba_12")<br /><br />


## history 命令<br /><br />
```shell
[root@iZt4n12effj3d79928coatZ ~]# history
    1  yum search java
    2  yum install -y java-1.8.0-openjdk.x86_64
    3  java -version
    4  yum search jenkins
    5  sudo wget -O /etc/yum.repos.d/jenkins.repo http://pkg.jenkins-ci.org/redhat/jenkins.repo
    6  sudo rpm --import https://jenkins-ci.org/redhat/jenkins-ci.org.key
    7  sudo yum install jenkins
    8  systemctl status jenkins
    9  systemctl start jenkins
   10  systemctl status jenkins
   11  find / -name "jenkins.war"
   12  cd /usr/lib/jenkins/
   13  java -jar jenkins.war
   14  ldconfig
   15  exit
   16  cd /usr/lib/jenkins/
   17  java -jar jenkins.war
   18  yum update jenkins
   19  java -version
   20  java -jar jenkins.war
   21  vi /etc/init.d/jenkins
   22  find / -name "java"
   23  find / -name "*jdk*"
   24  find / -name "*jdk*java*"
   25  systemctl status jenkins
   26  vi /var/lib/jenkins/secrets/initialAdminPassword
   27  history
   28  rpm -qa|grep jenkins
   29  pwd
   30  ll /usr/
   31  exit
   32  systemctl status jenkins
   33  systemctl staop jenkins
   34  systemctl stop jenkins
   35  systemctl status jenkins
   36  systemctl start jenkins
   37  df
   38  pwd
   39  ll
   40  exit
   41  df
   42  exit
   43  pwd
   44  ll
   45  cd /temp
   46  cd /home/www
   47  gcc -v
   48  history | grep scl
   49  history | grep sc
   50  history
   51  exit
   52  curl www.baidu.com
   53  exit
   54  find / -name "mysql"
   55  find / -name mysql
   56  rpm -qa | grep -i mysql
   57  systemctl status mysql
   58  gcc -v
   59  exit
   60  wget
   61  wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz
   62  ll
   63  tar -zxvf release-1.8.0.tar.gz
   64  ll
   65  cd googletest-release-1.8.0/
   66  ll
   67  cd ../
   68  ll
   69  mkdir mybuild
   70  cd mybuild/
   71  cmake ../googletest-release-1.8.0/ -Dgtest_build_samples=ON
   72  yum search cmake
   73  yum install cmake.x86_64
   74  cmake -h
   75  cmake -v
   76  cmake -V
   77  cmake -Version
   78  cmake ../googletest-release-1.8.0/ -Dgtest_build_samples=ON
   79  vim ../googletest-release-1.8.0/CMakeLists.txt
   80  g++ -v
   81  yum search g++
   82  yum search gcc-c++
   83  uname -a
   84  yum install gcc-c++.x86_64
   85  g++ -v
   86  ll
   87  pwd
   88  rm -rf ./*
   89  ll
   90  cmake ../googletest-release-1.8.0/ -Dgtest_build_samples=ON
   91  ll
   92  make
   93  ll
   94  ll ../googletest-release-1.8.0/
   95  ll
   96  find / -name "libgtest_main.so"
   97  ll
   98  cd ../googletest-release-1.8.0/
   99  ll
  100  find / -type d -name "gtest"
  101  cd googletest/
  102  ll
  103  cp -avrp include/gtest/ /usr/include/
  104  find / -name "gtest-all.o"
  105  ll
  106  cd ..
  107  ll
  108  cd googletest/
  109  ll
  110  cd make
  111  ll
  112  make
  113  ll
  114  ./sample1_unittest
  115  rm -rf ../../../mybuild/
  116  ./sample1_unittest
  117  cd ..
  118  ll
  119  cd ..
  120  ll
  121  cd googletest/
  122  ll
  123  pwd
  124  ll
  125  mkdir ../../gtest_program
  126  cp -avrp include/ ../../gtest_program/
  127  mkdir ../../gtest_program/lib
  128  ll
  129  ll make
  130  cp -avrp make/gtest_main.a ../../gtest_program/lib/
  131  cd ../../gtest_program/
  132  vim Makefile
  133  ll
  134  pwd
  135  cd -
  136  ll
  137  ll samples/
  138  cp -avrp samples/sample1* ../../gtest_program/
  139  cd -
  140  ll
  141  make
  142  vim Makefile
  143  make clean
  144  make
  145  ll
  146  ./SampleUnitTest
  147  history
  148  vim Makefile
  149  pwd
  150  cd gtest_program/
  151  vim Makefile
  152  cd gtest_program/
  153  vim Makefile
  154  exit
  155  cd gtest_program/
  156  ll
  157  vim Makefile
  158  exit
  159  ll
  160  cd googletest-release-1.8.0/
  161  ll
  162  cd googletest/
  163  ll
  164  pwd
  165  cd ../../gtest_program/
  166  cmake /root/googletest-release-1.8.0/googletest
  167  ll
  168  make clean
  169  cd ..
  170  ll
  171  mkdir mybuild
  172  cd mybuild/
  173  cmake /root/googletest-release-1.8.0/googletest
  174  ll
  175  make
  176  ll
  177  make install
  178  ll
  179  cmake -Dgtest_build_samples=ON /root/googletest-release-1.8.0/googletest
  180  ll
  181  make clean
  182  make
  183  ll
  184  make install
  185  ll
  186  ./sample10_unittest
  187  vim /root/googletest-release-1.8.0/googletest/CMakeLists.txt
  188  ll
  189  vim Makefile
  190  exit
  191  systemctl status jenkins
  192  systemctl stop jenkins
  193  systemctl status jenkins
  194  systemctl start jenkins
  195  systemctl status jenkins
  196  exit
  197  history
  198  pwd
  199  mkdir mybuild
  200  ll
  201  cd mybuild/
  202  ll
  203  touch demo.h
  204  vim demo.h
  205  vim demo.cpp
  206  vim Test.cpp
  207  ll
  208  g++ *.cpp -I/root//googletest-release-1.8.0/include -L./ -lgtest_main -o test
  209  vim Test.cpp
  210  g++ *.cpp -I/root//googletest-release-1.8.0/include -L./ -lgtest_main -o test
  211  ll
  212  cd mybuild/
  213  ll
  214  g++ *.cpp -I/root/googletest-release-1.8.0/include -L./ -lgtest_main -o test
  215  ll /root/googletest-release-1.8.0/include
  216  cd /root/googletest-release-1.8.0/
  217  ll
  218  cd googletest/
  219  ll
  220  cd -
  221  cd ../mybuild/
  222  ll
  223  g++ *.cpp -I/root/googletest-release-1.8.0/googletest/include -L./ -lgtest_main -o test
  224  g++ *.cpp -I/root/googletest-release-1.8.0/googletest/include -L./ -lgtest -o test
  225  vim Test.cpp
  226  g++ *.cpp -I/root/googletest-release-1.8.0/googletest/include -L./ -lgtest -o test
  227  vim Test.cpp
  228  g++ *.cpp -I/root/googletest-release-1.8.0/googletest/include -L./ -lgtest -o test
  229  cd mybuild/
  230  ll
  231  make clean
  232  vim Makefile
  233  vim Test.cpp
  234  g++ *.cpp -I/root/googletest-release-1.8.0/googletest/include -L./ -lgtest -o test
  235  g++ *.cpp -I/root/googletest-release-1.8.0/googletest/include -L./ -lgtest -o test -lpthread
  236  ./test
  237  ll
  238  mkdir src
  239  mv demo.* src/
  240  mv Test.cpp src/
  241  ll
  242  rm -f test
  243  ll
  244  cd src/
  245  vim Makefile
  246  cd ..
  247  ll
  248  mkdir lib
  249  ll
  250  cd src/
  251  ll
  252  cd ..
  253  cp -avrp ../googletest-release-1.8.0/googletest/libgtest.a ./lib/
  254  cd ../googletest-release-1.8.0/googletest/
  255  ll
  256  cd make/
  257  ll
  258  cd ..
  259  ll
  260  cmake
  261  ll
  262  ll include/
  263  ll include/gtest/
  264  cd make/
  265  ll
  266  cp -avrp gtest_main.a ../../../mybuild/lib/
  267  cd ../../../mybuild/
  268  ll
  269  cd lib/
  270  ll
  271  mv gtest_main.a  libgtest.a
  272  cd ..
  273  ll
  274  make clean
  275  cd src/
  276  ll
  277  make
  278  ll
  279  ./test
  280  make clean
  281  ll
  282  exit
  283  cd mybuild/src/
  284  ll
  285  make run
  286  ll
  287  ./test
  288  make clean
  289  vim Makefile
  290  make
  291  ll
  292  make
  293  make run
  294  ll
  295  make
  296  ll
  297  vim Makefile
  298  make clean
  299  make run
  300  ./test
  301  make clean
  302  exit
  303  systemctl status jenkins
  304  systemctl stop jenkins
  305  systemctl status jenkins
  306  systemctl start jenkins
  307  systemctl status jenkins
  308  exit
  309  ll
  310  cd mybuild/
  311  ll
  312  cd src/
  313  ll
  314  vim Makefile
  315  ll
  316  vim Makefile
  317  ll ../lib/
  318  exit
  319  pwd
  320  mysql -v
  321  find / -name "release*"
  322  mkdir temp
  323  cd temp/
  324  rm -rf ../temp/
  325  ll
  326  cd ..
  327  ll
  328  mkdir /temp
  329  cd /temp/
  330  yum search mysql-community-release*
  331  yum search mysql-community-release
  332  wget http://repo.mysql.com/mysql-community-release-el7-5.noarch.rpm
  333  ll
  334  rpm -ivh mysql-community-release-el7-5.noarch.rpm
  335  yum install mysql-server
  336  systemctl status mysql
  337  systemctl start mysql
  338  systemctl status mysql
  339  mysql -v
  340  mysql -V
  341  mysql -uroot -p
  342  mysqladmin -uroot -p password "1"
  343  mysql -uroot -p1
  344  mysql -ucaosx -p1
  345  history
  346  mysqladmin -uroot password "12"
  347  mysqladmin -uroot -p  password "12"
  348  mysqladmin -uroot -p  password "1"
  349  mysql -u root -p1
  350  mysql -ucaosx -p1
  351  mysqladmin -ucaosx
  352  mysqladmin -ucaosx password "12"
  353  mysqladmin -ucaosx -p password "12"
  354  mysqladmin -ucaosx -p password "1"
  355  exit
  356  pwd
  357  ll
  358  cd mybuild/
  359  ll
  360  cd ../
  361  pwd
  362  vim temp
  363  sed "s/pig/ppig/g" temp
  364  sed 's/ccow/cow/g' temp
  365  sed 's/cow//g' temp
  366  sed 's//cow/g' temp
  367  sed 's/\/cow/g' temp
  368  vim temp
  369  sed "1,$s/pig/ppig" temp
  370  sed "s/pig/ppig/g" temp
  371  sed "s/ppig/pig/g" temp
  372  sed "1, $s/ppig/pig/g" temp
  373  sed "1, $ s/ppig/pig/g" temp
  374  sed "1, $ s/boy/boyyyy/" temp
  375  vim temp
  376  sed -e "%s/pig/ppig/g" temp
  377  sed -e "1,$ s/pig/ppig/g" temp
  378  cat temp
  379  sed -e "1,$ s/pig/ppig/" temp
  380  vim temp
  381  sed "s/pig/ppig/" temp
  382  sed "s/pig/ppig/g" temp
  383  sed -e "s/pig//g" temp
  384  sed -e "s/pig\ //g" temp
  385  sed -e "s/pig//g" temp
  386  sed -e "s/pig\ //g" temp
  387  sed "s/pig/piig/g" temp  >> teemp
  388  vim teemp
  389  rm -f teemp
  390  vim temp
  391  sed "32,&dd" temp
  392  sed "32dd" temp
  393  sed "32,$d" temp
  394  sed "32d" temp
  395  vim temp
  396  rm -f temp
  397  ll
  398  vim teemp
  399  sed "s/pig/ppig/g" teemp >> temp
  400  vim temp
  401  sed -i "s/ppig/pig/g" temp
  402  vim temp
  403  sed -i "s/ppig/pig/g" temp
  404  vim temp
  405  nl temp
  406  nl -5 temp
  407  nl -help
  408  nl --help
  409  vim teemp
  410  vim temp
  411  sed -i "s/piig/pig/g"
  412  sed -i "s/piig/pig/g" te
  413  sed -i "s/piig/pig/g" temp
  414  vim temp
  415  vim teemp
  416  sed -i "s/piig/caosx/g" teemp
  417  vim teemp
  418  set -a "The last line of the content" temp
  419  vim temp
  420  sed -i "s/caosx/pig/g" temp
  421  vim temp
  422  sed -i "s/pig/p_i_g/g" temp
  423  vim temp
  424  sed -i "s/p_i_g/piig/g" temp
  425  vim temp
  426  vim teemp
  427  sed -i "s/caosx/csx_v/g" teemp
  428  vim teemp
  429  sed -i "s/csx_v/piig/g" teemp
  430  vim teemp
  431  ip addr
  432  ip addr | grep sth0
  433  ip addr | grep eth0
  434  ip addr | grep eth0 | sed "s/^inet\ //g"
  435  ip addr | grep eth0 | sed "s/^inet //g"
  436  ip addr | grep eth0 | sed "s/^.*inet//g"
  437  ip addr | grep eth0 | sed "s/^.*inet //g"
  438  ip addr | grep eth0 | sed "s/A.*inet //g"
  439  ip addr | grep eth0 | sed "s/^.*inet //gci"
  440  ip addr | grep eth0 | sed -e "s/^.*inet //gci"
  441  ip addr | grep eth0 | sed  "s/^.*inet //g"
  442  ip addr | grep eth0 | sed  "s/^.*eth0.*//g"
  443  ip addr | grep eth0 | sed  "s/^.*eth0.*inet //g"
  444  ip addr | grep eth0 | sed  "s/^.*eth0.*\r\ninet //g"
  445  exity
  446  exiy
  447  exit
  448  sed "s/pig/ppig/g" temp
  449  sed "1d" temp
  450  sed "$d" temp
  451  sed "|pig|d" temp
  452  sed "/pig/d" temp
  453  sed "s/pig/ppig/g" temp
  454  ll
  455  sed "s/pig/piig/g" temp >> teemp
  456  vim te
  457  vim temp
  458  systemctl vsftpd
  459  systemctl status vsftpd
  460  yum search vsftpd
  461  yum install vsftpd.x86_64
  462  systemctl status vsftpd
  463  systemctl start vsftpd
  464  systemctl status vsftpd
  465  curl ftp://localhost/root/temp
  466   ftp://localhost/root/temp
  467  vim te
  468  vim temp
  469  netstat a-np | grep vsftpd
  470  netstat -anp | grep vsftpd
  471  wget
  472  wget  http://ibiblio.org/pub/Linux/ALPHA/freetds/stable/freetds-stable.tgz
  473  tar -axvf freetds-stable.tgz
  474  ll
  475  cd freetds-
  476  cd freetds-0.91/
  477  ./configure --prefix=/usr/local/freetds --with-tdsver=8.0 --enable-msdblib
  478  make
  479  make install
  480  ll
  481  ll /usr/local/freetds/
  482  vim ~/.bash_profile
  483  source ~/.bash_profile
  484  exit
  485  yum search samba-client
  486  yum install samba-client.x86_64
```

## 安装的整个过程
```shell
     ┌────────────────────────────────────────────────────────────────────┐
     │                        ? MobaXterm 10.4 ?                          │
     │            (SSH client, X-server and networking tools)             │
     │                                                                    │
     │ ? SSH session to root@47.88.218.246                                │
     │   ? SSH compression : ?                                            │
     │   ? SSH-browser     : ?                                            │
     │   ? X11-forwarding  : ?  (disabled or not supported by server)     │
     │   ? DISPLAY         : 192.168.1.107:0.0                            │
     │                                                                    │
     │ ? For more info, ctrl+click on help or visit our website           │
     └────────────────────────────────────────────────────────────────────┘

Last failed login: Sat May  5 14:41:34 CST 2018 from 97.65.64.222 on ssh:notty
There were 4 failed login attempts since the last successful login.
Last login: Thu May  3 20:52:30 2018 from 210.22.94.234

Welcome to Alibaba Cloud Elastic Compute Service !

[root@iZt4n12effj3d79928coatZ ~]# yum info samba
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
Available Packages
Name        : samba
Arch        : x86_64
Version     : 4.6.2
Release     : 12.el7_4
Size        : 633 k
Repo        : updates/7/x86_64
Summary     : Server and Client software to interoperate with Windows machines
URL         : http://www.samba.org/
License     : GPLv3+ and LGPLv3+
Description : Samba is the standard Windows interoperability suite of programs for Linux and
            : Unix.

[root@iZt4n12effj3d79928coatZ ~]# yum search samba
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
======================================================================= N/S matched: samba =======================================================================
kdenetwork-fileshare-samba.x86_64 : Share files via samba
pcp-pmda-samba.x86_64 : Performance Co-Pilot (PCP) metrics for Samba
php-pear-Auth-samba.noarch : Samba support for php-pear-Auth
samba-client.x86_64 : Samba client programs
samba-client-libs.i686 : Samba client libraries
samba-client-libs.x86_64 : Samba client libraries
samba-common.noarch : Files used by both Samba servers and clients
samba-common-libs.x86_64 : Libraries used by both Samba servers and clients
samba-common-tools.x86_64 : Tools for Samba servers and clients
samba-dc.x86_64 : Samba AD Domain Controller
samba-dc-libs.x86_64 : Samba AD Domain Controller Libraries
samba-devel.i686 : Developer tools for Samba libraries
samba-devel.x86_64 : Developer tools for Samba libraries
samba-krb5-printing.x86_64 : Samba CUPS backend for printing with Kerberos
samba-libs.i686 : Samba libraries
samba-libs.x86_64 : Samba libraries
samba-python.x86_64 : Samba Python libraries
samba-test.x86_64 : Testing tools for Samba servers and clients
samba-test-libs.i686 : Libraries need by the testing tools for Samba servers and clients
samba-test-libs.x86_64 : Libraries need by the testing tools for Samba servers and clients
samba-vfs-glusterfs.x86_64 : Samba VFS module for GlusterFS
samba-winbind.x86_64 : Samba winbind
samba-winbind-clients.x86_64 : Samba winbind clients
samba-winbind-krb5-locator.x86_64 : Samba winbind krb5 locator
samba-winbind-modules.i686 : Samba winbind modules
samba-winbind-modules.x86_64 : Samba winbind modules
caja-share.x86_64 : Easy sharing folder via Samba (CIFS protocol)
ctdb.x86_64 : A Clustered Database based on Samba's Trivial Database (TDB)
php-pear-File-SMBPasswd.noarch : Class for managing SAMBA style password files
python-smbc.x86_64 : Python bindings for libsmbclient API from Samba
samba.x86_64 : Server and Client software to interoperate with Windows machines
samba-pidl.noarch : Perl IDL compiler
smbldap-tools.noarch : User and group administration tools for Samba/OpenLDAP

  Name and summary matches only, use "search all" for everything.
[root@iZt4n12effj3d79928coatZ ~]# yum install samba.x86_64
Loaded plugins: fastestmirror
base                                                                                                                                       | 3.6 kB  00:00:00
epel                                                                                                                                       | 4.7 kB  00:00:00
extras                                                                                                                                     | 3.4 kB  00:00:00
jenkins                                                                                                                                    | 2.9 kB  00:00:00
mysql-connectors-community                                                                                                                 | 2.5 kB  00:00:00
mysql-tools-community                                                                                                                      | 2.5 kB  00:00:00
mysql56-community                                                                                                                          | 2.5 kB  00:00:00
updates                                                                                                                                    | 3.4 kB  00:00:00
(1/3): epel/x86_64/updateinfo                                                                                                              | 919 kB  00:00:00
(2/3): epel/x86_64/primary_db                                                                                                              | 6.4 MB  00:00:00
(3/3): jenkins/primary_db                                                                                                                  | 110 kB  00:00:01
Loading mirror speeds from cached hostfile
Resolving Dependencies
--> Running transaction check
---> Package samba.x86_64 0:4.6.2-12.el7_4 will be installed
--> Processing Dependency: samba-libs = 4.6.2-12.el7_4 for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: samba-common-tools = 4.6.2-12.el7_4 for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: samba-common-libs = 4.6.2-12.el7_4 for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: samba-common = 4.6.2-12.el7_4 for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: samba-common = 4.6.2-12.el7_4 for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: samba-client-libs = 4.6.2-12.el7_4 for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libwbclient = 4.6.2-12.el7_4 for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libxattr-tdb-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libwbclient.so.0(WBCLIENT_0.9)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libutil-tdb-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libutil-reg-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libtevent.so.0(TEVENT_0.9.9)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libtevent.so.0(TEVENT_0.9.16)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libtevent-util.so.0(TEVENT_UTIL_0.0.1)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libtdb.so.1(TDB_1.2.5)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libtdb.so.1(TDB_1.2.1)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libtalloc.so.2(TALLOC_2.0.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsys-rw-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsocket-blocking-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsmbd-shim-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsmbd-base-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsmbconf.so.0(SMBCONF_0)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsmb-transport-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libserver-id-db-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsecrets3-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba3-util-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-util.so.0(SAMBA_UTIL_0.0.1)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-sockets-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-security-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-passdb.so.0(SAMBA_PASSDB_0.2.0)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-hostconfig.so.0(SAMBA_HOSTCONFIG_0.0.1)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-errors.so.1(SAMBA_ERRORS_1)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-debug-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-cluster-support-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libreplace-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libpopt-samba3-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libndr.so.0(NDR_0.0.1)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libndr-standard.so.0(NDR_STANDARD_0.0.1)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libndr-samba-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libndr-nbt.so.0(NDR_NBT_0.0.1)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libmsghdr-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libmessages-dgm-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: liblibsmb-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libgse-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libgenrand-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libdbwrap-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libcliauth-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libcli-smb-common-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libcli-nbt-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libcli-cldap-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libauth-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libCHARSET3-samba4.so(SAMBA_4.6.2)(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libxattr-tdb-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libwbclient.so.0()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libutil-tdb-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libutil-reg-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libtevent.so.0()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libtevent-util.so.0()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libtdb.so.1()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libtalloc.so.2()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsys-rw-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsocket-blocking-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsmbd-shim-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsmbd-base-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsmbconf.so.0()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsmb-transport-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libserver-id-db-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsecrets3-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba3-util-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-util.so.0()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-sockets-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-security-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-passdb.so.0()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-hostconfig.so.0()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-errors.so.1()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-debug-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libsamba-cluster-support-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libreplace-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libpopt-samba3-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libndr.so.0()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libndr-standard.so.0()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libndr-samba-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libndr-nbt.so.0()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libmsghdr-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libmessages-dgm-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: liblibsmb-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libgse-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libgenrand-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libdbwrap-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libcliauth-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libcli-smb-common-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libcli-nbt-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libcli-cldap-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libauth-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libCHARSET3-samba4.so()(64bit) for package: samba-4.6.2-12.el7_4.x86_64
--> Running transaction check
---> Package libtalloc.x86_64 0:2.1.9-1.el7 will be installed
---> Package libtdb.x86_64 0:1.3.12-2.el7 will be installed
---> Package libtevent.x86_64 0:0.9.31-2.el7_4 will be installed
---> Package libwbclient.x86_64 0:4.6.2-12.el7_4 will be installed
---> Package samba-client-libs.x86_64 0:4.6.2-12.el7_4 will be installed
--> Processing Dependency: libldb.so.1(LDB_1.1.19)(64bit) for package: samba-client-libs-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libldb.so.1(LDB_1.1.1)(64bit) for package: samba-client-libs-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libldb.so.1(LDB_0.9.23)(64bit) for package: samba-client-libs-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libldb.so.1(LDB_0.9.15)(64bit) for package: samba-client-libs-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libldb.so.1(LDB_0.9.10)(64bit) for package: samba-client-libs-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libldb.so.1()(64bit) for package: samba-client-libs-4.6.2-12.el7_4.x86_64
---> Package samba-common.noarch 0:4.6.2-12.el7_4 will be installed
---> Package samba-common-libs.x86_64 0:4.6.2-12.el7_4 will be installed
---> Package samba-common-tools.x86_64 0:4.6.2-12.el7_4 will be installed
---> Package samba-libs.x86_64 0:4.6.2-12.el7_4 will be installed
--> Processing Dependency: libpytalloc-util.so.2(PYTALLOC_UTIL_2.1.9)(64bit) for package: samba-libs-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libpytalloc-util.so.2(PYTALLOC_UTIL_2.1.6)(64bit) for package: samba-libs-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libpytalloc-util.so.2(PYTALLOC_UTIL_2.0.6)(64bit) for package: samba-libs-4.6.2-12.el7_4.x86_64
--> Processing Dependency: libpytalloc-util.so.2()(64bit) for package: samba-libs-4.6.2-12.el7_4.x86_64
--> Running transaction check
---> Package libldb.x86_64 0:1.1.29-1.el7 will be installed
---> Package pytalloc.x86_64 0:2.1.9-1.el7 will be installed
--> Finished Dependency Resolution

Dependencies Resolved

==================================================================================================================================================================
 Package                                      Arch                             Version                                    Repository                         Size
==================================================================================================================================================================
Installing:
 samba                                        x86_64                           4.6.2-12.el7_4                             updates                           633 k
Installing for dependencies:
 libldb                                       x86_64                           1.1.29-1.el7                               base                              128 k
 libtalloc                                    x86_64                           2.1.9-1.el7                                base                               33 k
 libtdb                                       x86_64                           1.3.12-2.el7                               base                               47 k
 libtevent                                    x86_64                           0.9.31-2.el7_4                             updates                            36 k
 libwbclient                                  x86_64                           4.6.2-12.el7_4                             updates                           104 k
 pytalloc                                     x86_64                           2.1.9-1.el7                                base                               16 k
 samba-client-libs                            x86_64                           4.6.2-12.el7_4                             updates                           4.7 M
 samba-common                                 noarch                           4.6.2-12.el7_4                             updates                           197 k
 samba-common-libs                            x86_64                           4.6.2-12.el7_4                             updates                           164 k
 samba-common-tools                           x86_64                           4.6.2-12.el7_4                             updates                           456 k
 samba-libs                                   x86_64                           4.6.2-12.el7_4                             updates                           265 k

Transaction Summary
==================================================================================================================================================================
Install  1 Package (+11 Dependent packages)

Total download size: 6.7 M
Installed size: 23 M
Is this ok [y/d/N]: y
Downloading packages:
(1/12): libldb-1.1.29-1.el7.x86_64.rpm                                                                                                     | 128 kB  00:00:00
(2/12): libtalloc-2.1.9-1.el7.x86_64.rpm                                                                                                   |  33 kB  00:00:00
(3/12): libtdb-1.3.12-2.el7.x86_64.rpm                                                                                                     |  47 kB  00:00:00
(4/12): pytalloc-2.1.9-1.el7.x86_64.rpm                                                                                                    |  16 kB  00:00:00
(5/12): libtevent-0.9.31-2.el7_4.x86_64.rpm                                                                                                |  36 kB  00:00:00
(6/12): libwbclient-4.6.2-12.el7_4.x86_64.rpm                                                                                              | 104 kB  00:00:00
(7/12): samba-client-libs-4.6.2-12.el7_4.x86_64.rpm                                                                                        | 4.7 MB  00:00:00
(8/12): samba-4.6.2-12.el7_4.x86_64.rpm                                                                                                    | 633 kB  00:00:00
(9/12): samba-common-4.6.2-12.el7_4.noarch.rpm                                                                                             | 197 kB  00:00:00
(10/12): samba-common-libs-4.6.2-12.el7_4.x86_64.rpm                                                                                       | 164 kB  00:00:00
(11/12): samba-libs-4.6.2-12.el7_4.x86_64.rpm                                                                                              | 265 kB  00:00:00
(12/12): samba-common-tools-4.6.2-12.el7_4.x86_64.rpm                                                                                      | 456 kB  00:00:00
------------------------------------------------------------------------------------------------------------------------------------------------------------------
Total                                                                                                                             5.4 MB/s | 6.7 MB  00:00:01
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
  Installing : libtalloc-2.1.9-1.el7.x86_64                                                                                                                  1/12
  Installing : libtdb-1.3.12-2.el7.x86_64                                                                                                                    2/12
  Installing : libtevent-0.9.31-2.el7_4.x86_64                                                                                                               3/12
  Installing : samba-common-4.6.2-12.el7_4.noarch                                                                                                            4/12
  Installing : libldb-1.1.29-1.el7.x86_64                                                                                                                    5/12
  Installing : libwbclient-4.6.2-12.el7_4.x86_64                                                                                                             6/12
  Installing : samba-client-libs-4.6.2-12.el7_4.x86_64                                                                                                       7/12
  Installing : samba-common-libs-4.6.2-12.el7_4.x86_64                                                                                                       8/12
  Installing : pytalloc-2.1.9-1.el7.x86_64                                                                                                                   9/12
  Installing : samba-libs-4.6.2-12.el7_4.x86_64                                                                                                             10/12
  Installing : samba-common-tools-4.6.2-12.el7_4.x86_64                                                                                                     11/12
  Installing : samba-4.6.2-12.el7_4.x86_64                                                                                                                  12/12
  Verifying  : samba-common-libs-4.6.2-12.el7_4.x86_64                                                                                                       1/12
  Verifying  : samba-common-tools-4.6.2-12.el7_4.x86_64                                                                                                      2/12
  Verifying  : samba-common-4.6.2-12.el7_4.noarch                                                                                                            3/12
  Verifying  : libtevent-0.9.31-2.el7_4.x86_64                                                                                                               4/12
  Verifying  : libwbclient-4.6.2-12.el7_4.x86_64                                                                                                             5/12
  Verifying  : samba-libs-4.6.2-12.el7_4.x86_64                                                                                                              6/12
  Verifying  : libtalloc-2.1.9-1.el7.x86_64                                                                                                                  7/12
  Verifying  : libtdb-1.3.12-2.el7.x86_64                                                                                                                    8/12
  Verifying  : pytalloc-2.1.9-1.el7.x86_64                                                                                                                   9/12
  Verifying  : libldb-1.1.29-1.el7.x86_64                                                                                                                   10/12
  Verifying  : samba-client-libs-4.6.2-12.el7_4.x86_64                                                                                                      11/12
  Verifying  : samba-4.6.2-12.el7_4.x86_64                                                                                                                  12/12

Installed:
  samba.x86_64 0:4.6.2-12.el7_4

Dependency Installed:
  libldb.x86_64 0:1.1.29-1.el7                            libtalloc.x86_64 0:2.1.9-1.el7                    libtdb.x86_64 0:1.3.12-2.el7
  libtevent.x86_64 0:0.9.31-2.el7_4                       libwbclient.x86_64 0:4.6.2-12.el7_4               pytalloc.x86_64 0:2.1.9-1.el7
  samba-client-libs.x86_64 0:4.6.2-12.el7_4               samba-common.noarch 0:4.6.2-12.el7_4              samba-common-libs.x86_64 0:4.6.2-12.el7_4
  samba-common-tools.x86_64 0:4.6.2-12.el7_4              samba-libs.x86_64 0:4.6.2-12.el7_4

Complete!
[root@iZt4n12effj3d79928coatZ ~]# ll /etc/samba/
lmhosts           smb.conf          smb.conf.example
[root@iZt4n12effj3d79928coatZ ~]# cp /etc/samba/smb.conf /etc/samba/smb_bak.conf
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]# vim /etc/samba/smb.conf
[root@iZt4n12effj3d79928coatZ ~]# mkdir /share
[root@iZt4n12effj3d79928coatZ ~]# ll /share/
total 0
[root@iZt4n12effj3d79928coatZ ~]# chmod 777 /share
[root@iZt4n12effj3d79928coatZ ~]# find / -name "samba"
/var/log/samba
/var/spool/samba
/var/lib/samba
/run/samba
/etc/pam.d/samba
/etc/selinux/targeted/active/modules/100/samba
/etc/samba
/etc/logrotate.d/samba
/etc/sysconfig/samba
/usr/lib64/samba
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]# rpm -qa | grep samba
samba-libs-4.6.2-12.el7_4.x86_64
samba-client-libs-4.6.2-12.el7_4.x86_64
samba-common-tools-4.6.2-12.el7_4.x86_64
samba-common-4.6.2-12.el7_4.noarch
samba-common-libs-4.6.2-12.el7_4.x86_64
samba-4.6.2-12.el7_4.x86_64
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]# systemctl status smb
● smb.service - Samba SMB Daemon
   Loaded: loaded (/usr/lib/systemd/system/smb.service; disabled; vendor preset: disabled)
   Active: inactive (dead)
[root@iZt4n12effj3d79928coatZ ~]# systemctl start smb
[root@iZt4n12effj3d79928coatZ ~]# systemctl status smb
● smb.service - Samba SMB Daemon
   Loaded: loaded (/usr/lib/systemd/system/smb.service; disabled; vendor preset: disabled)
   Active: active (running) since Sat 2018-05-05 16:14:15 CST; 6s ago
 Main PID: 12503 (smbd)
   Status: "smbd: ready to serve connections..."
   CGroup: /system.slice/smb.service
           ├─12503 /usr/sbin/smbd
           ├─12504 /usr/sbin/smbd
           ├─12505 /usr/sbin/smbd
           └─12506 /usr/sbin/smbd

May 05 16:14:15 iZt4n12effj3d79928coatZ systemd[1]: Starting Samba SMB Daemon...
May 05 16:14:15 iZt4n12effj3d79928coatZ smbd[12503]: [2018/05/05 16:14:15.571767,  0] ../lib/util/become_daemon.c:124(daemon_ready)
May 05 16:14:15 iZt4n12effj3d79928coatZ systemd[1]: Started Samba SMB Daemon.
May 05 16:14:15 iZt4n12effj3d79928coatZ smbd[12503]:   STATUS=daemon 'smbd' finished starting up and ready to serve connections
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]# systemctl enable smb
Created symlink from /etc/systemd/system/multi-user.target.wants/smb.service to /usr/lib/systemd/system/smb.service.
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]# netstat -anp | grep smb
tcp        0      0 0.0.0.0:139             0.0.0.0:*               LISTEN      12503/smbd
tcp        0      0 0.0.0.0:445             0.0.0.0:*               LISTEN      12503/smbd
tcp6       0      0 :::139                  :::*                    LISTEN      12503/smbd
tcp6       0      0 :::445                  :::*                    LISTEN      12503/smbd
unix  2      [ ]         DGRAM                    922253   12503/smbd           /var/lib/samba/private/msg.sock/12503
unix  2      [ ]         DGRAM                    922256   12505/smbd           /var/lib/samba/private/msg.sock/12505
unix  2      [ ]         DGRAM                    922257   12504/smbd           /var/lib/samba/private/msg.sock/12504
unix  2      [ ]         DGRAM                    922282   12506/smbd           /var/lib/samba/private/msg.sock/12506
unix  2      [ ]         DGRAM                    922266   12503/smbd
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]# systemctl status smb
● smb.service - Samba SMB Daemon
   Loaded: loaded (/usr/lib/systemd/system/smb.service; enabled; vendor preset: disabled)
   Active: active (running) since Sat 2018-05-05 16:14:15 CST; 6min ago
 Main PID: 12503 (smbd)
   Status: "smbd: ready to serve connections..."
   CGroup: /system.slice/smb.service
           ├─12503 /usr/sbin/smbd
           ├─12504 /usr/sbin/smbd
           ├─12505 /usr/sbin/smbd
           └─12506 /usr/sbin/smbd

May 05 16:14:15 iZt4n12effj3d79928coatZ systemd[1]: Starting Samba SMB Daemon...
May 05 16:14:15 iZt4n12effj3d79928coatZ smbd[12503]: [2018/05/05 16:14:15.571767,  0] ../lib/util/become_daemon.c:124(daemon_ready)
May 05 16:14:15 iZt4n12effj3d79928coatZ systemd[1]: Started Samba SMB Daemon.
May 05 16:14:15 iZt4n12effj3d79928coatZ smbd[12503]:   STATUS=daemon 'smbd' finished starting up and ready to serve connections
[root@iZt4n12effj3d79928coatZ ~]# testparm
Load smb config files from /etc/samba/smb.conf
Processing section "[homes]"
Processing section "[printers]"
Processing section "[print$]"
Processing section "[share]"
Loaded services file OK.
WARNING: The 'netbios name' is too long (max. 15 chars).

Server role: ROLE_STANDALONE

Press enter to see a dump of your service definitions

# Global parameters
[global]
        workgroup = SAMBA
        printcap name = cups
        security = USER
        idmap config * : backend = tdb
        cups options = raw


[homes]
        comment = Home Directories
        browseable = No
        inherit acls = Yes
        read only = No
        valid users = %S %D%w%S


[printers]
        comment = All Printers
        path = /var/tmp
        browseable = No
        printable = Yes
        create mask = 0600


[print$]
        comment = Printer Drivers
        path = /var/lib/samba/drivers
        create mask = 0664
        directory mask = 0775
        write list = root


[share]
        comment = This is a shared directory, you can access the below path thru windows
        path = /share
        guest ok = Yes
        read only = No
[root@iZt4n12effj3d79928coatZ ~]# vim /etc/samba/samba.conf
[root@iZt4n12effj3d79928coatZ ~]# ll /etc/samba
total 24
-rw-r--r-- 1 root root    20 Nov 28 00:21 lmhosts
-rw-r--r-- 1 root root   667 May  5 16:03 smb_bak.conf
-rw-r--r-- 1 root root   817 May  5 16:05 smb.conf
-rw-r--r-- 1 root root 11327 Nov 28 00:21 smb.conf.example
[root@iZt4n12effj3d79928coatZ ~]# vim /etc/samba/smb.conf
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]# systemctl status smb
● smb.service - Samba SMB Daemon
   Loaded: loaded (/usr/lib/systemd/system/smb.service; enabled; vendor preset: disabled)
   Active: active (running) since Sat 2018-05-05 16:14:15 CST; 15min ago
 Main PID: 12503 (smbd)
   Status: "smbd: ready to serve connections..."
   CGroup: /system.slice/smb.service
           ├─12503 /usr/sbin/smbd
           ├─12504 /usr/sbin/smbd
           ├─12505 /usr/sbin/smbd
           └─12506 /usr/sbin/smbd

May 05 16:14:15 iZt4n12effj3d79928coatZ systemd[1]: Starting Samba SMB Daemon...
May 05 16:14:15 iZt4n12effj3d79928coatZ smbd[12503]: [2018/05/05 16:14:15.571767,  0] ../lib/util/become_daemon.c:124(daemon_ready)
May 05 16:14:15 iZt4n12effj3d79928coatZ systemd[1]: Started Samba SMB Daemon.
May 05 16:14:15 iZt4n12effj3d79928coatZ smbd[12503]:   STATUS=daemon 'smbd' finished starting up and ready to serve connections
May 05 16:29:20 iZt4n12effj3d79928coatZ smbd[12604]: [2018/05/05 16:29:20.560768,  0] ../lib/param/loadparm.c:1809(lpcfg_do_service_parameter)
May 05 16:29:20 iZt4n12effj3d79928coatZ smbd[12604]:   Global parameter security found in service section!
May 05 16:29:20 iZt4n12effj3d79928coatZ smbd[12604]: [2018/05/05 16:29:20.870280,  0] ../lib/param/loadparm.c:1809(lpcfg_do_service_parameter)
May 05 16:29:20 iZt4n12effj3d79928coatZ smbd[12604]:   Global parameter security found in service section!
[root@iZt4n12effj3d79928coatZ ~]# systemctl restart smb
[root@iZt4n12effj3d79928coatZ ~]# systemctl status smb
● smb.service - Samba SMB Daemon
   Loaded: loaded (/usr/lib/systemd/system/smb.service; enabled; vendor preset: disabled)
   Active: active (running) since Sat 2018-05-05 16:29:27 CST; 1s ago
 Main PID: 12617 (smbd)
   Status: "smbd: ready to serve connections..."
   CGroup: /system.slice/smb.service
           ├─12617 /usr/sbin/smbd
           ├─12618 /usr/sbin/smbd
           ├─12619 /usr/sbin/smbd
           └─12620 /usr/sbin/smbd

May 05 16:29:27 iZt4n12effj3d79928coatZ systemd[1]: Starting Samba SMB Daemon...
May 05 16:29:27 iZt4n12effj3d79928coatZ smbd[12614]: [2018/05/05 16:29:27.576182,  0] ../lib/param/loadparm.c:1809(lpcfg_do_service_parameter)
May 05 16:29:27 iZt4n12effj3d79928coatZ systemd[1]: Started Samba SMB Daemon.
May 05 16:29:27 iZt4n12effj3d79928coatZ smbd[12617]: [2018/05/05 16:29:27.584664,  0] ../lib/util/become_daemon.c:124(daemon_ready)
May 05 16:29:27 iZt4n12effj3d79928coatZ smbd[12617]:   STATUS=daemon 'smbd' finished starting up and ready to serve connections
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]# testparm -V
Version 4.6.2
[root@iZt4n12effj3d79928coatZ ~]# vim /etc/samba/smb.conf
[root@iZt4n12effj3d79928coatZ ~]# ll /etc/samba/
total 24
-rw-r--r-- 1 root root    20 Nov 28 00:21 lmhosts
-rw-r--r-- 1 root root   667 May  5 16:03 smb_bak.conf
-rw-r--r-- 1 root root   832 May  5 16:29 smb.conf
-rw-r--r-- 1 root root 11327 Nov 28 00:21 smb.conf.example
[root@iZt4n12effj3d79928coatZ ~]# smb passwd file = /etc/samba/smbpasswd
-bash: smb: command not found
[root@iZt4n12effj3d79928coatZ ~]# smb
-bash: smb: command not found
[root@iZt4n12effj3d79928coatZ ~]# smbpasswd root
New SMB password:
Retype new SMB password:
Failed to find entry for user root.
[root@iZt4n12effj3d79928coatZ ~]# mkdir /etc/samba/smbpasswd
[root@iZt4n12effj3d79928coatZ ~]# smbpasswd root
New SMB password:
Retype new SMB password:
Failed to find entry for user root.
[root@iZt4n12effj3d79928coatZ ~]# mkdir /etc/samba/smbpasswd
mkdir: cannot create directory ‘/etc/samba/smbpasswd’: File exists
[root@iZt4n12effj3d79928coatZ ~]#  /etc/samba/smbusers
-bash: /etc/samba/smbusers: No such file or directory
[root@iZt4n12effj3d79928coatZ ~]# mkdir  /etc/samba/smbusers
[root@iZt4n12effj3d79928coatZ ~]# vim  /etc/samba/smbusers
[root@iZt4n12effj3d79928coatZ ~]# rm -rf /etc/samba/smbusers
[root@iZt4n12effj3d79928coatZ ~]# touch  /etc/samba/smbusers
[root@iZt4n12effj3d79928coatZ ~]# vim  /etc/samba/smbusers
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]# rm -rf /etc/samba/smbpasswd
[root@iZt4n12effj3d79928coatZ ~]# touch /etc/samba/smbpasswd
[root@iZt4n12effj3d79928coatZ ~]# smbpasswd root
New SMB password:
Retype new SMB password:
Failed to find entry for user root.
[root@iZt4n12effj3d79928coatZ ~]# sudo smbpasswd -L -a root
New SMB password:
Retype new SMB password:
Added user root.
[root@iZt4n12effj3d79928coatZ ~]# sudo smbpasswd -L -e root
Enabled user root.
[root@iZt4n12effj3d79928coatZ ~]# vim /etc/samba/smb.conf
[root@iZt4n12effj3d79928coatZ ~]# tail /etc/samba/smb.conf
        write list = root
        create mask = 0664
        directory mask = 0775
# newly added 2018-05-05
security=share
[share]
comment = This is a shared directory, you can access the below path thru windows
path=/share
public=yes
writable=yes
[root@iZt4n12effj3d79928coatZ ~]# vim /etc/samba/smb.conf
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]#
[root@iZt4n12effj3d79928coatZ ~]# touch /share/a.txt
[root@iZt4n12effj3d79928coatZ ~]# touch /share/b.txt
[root@iZt4n12effj3d79928coatZ ~]# touch /share/c.txt
[root@iZt4n12effj3d79928coatZ ~]# ll /share/
total 0
-rw-r--r-- 1 root root 0 May  5 16:46 a.txt
-rw-r--r-- 1 root root 0 May  5 16:46 b.txt
-rw-r--r-- 1 root root 0 May  5 16:46 c.txt
[root@iZt4n12effj3d79928coatZ ~]#
```

* 安装 `samba`
!["samba_01"](https://github.com/tycao/tycao.github.io/blob/master/src/samba_01.png "samba_01")<br /><br />

* 查看samba端口： <br />
!["samba_03"](https://github.com/tycao/tycao.github.io/blob/master/src/samba_01.png "samba_01")<br /><br />

* 开启 `samba` 服务 <br />
!["samba_04"](https://github.com/tycao/tycao.github.io/blob/master/src/samba_01.png "samba_01")<br /><br />

* 修改smb.conf文件： `vim /etc/samba/smb.conf`  <br />
!["samba_05"](https://github.com/tycao/tycao.github.io/blob/master/src/samba_01.png "samba_01")<br /><br />

***************
## UBuntu16.04 64bit
!["samba_02"](https://github.com/tycao/tycao.github.io/blob/master/src/samba_02.jpg "samba_02")<br /><br />






******************
## CentOS7安装 `samba-client`
```shell
yum install samba-client
```
!["samba_06"](https://github.com/tycao/tycao.github.io/blob/master/src/samba_06.png "samba_06")<br /><br />
!["samba_11"](https://github.com/tycao/tycao.github.io/blob/master/src/samba_11.png "samba_11")<br /><br />


## UBuntu16.04 安装 `samba-client`
参考连接 : [Ubuntu 下用smbclient访问smb](https://blog.csdn.net/FruitDrop/article/details/66475465)<br />
```shell
sudo apt-get install smbclient
```

## smbclient命令行用法 <br /><br />
[smbclient命令行用法](https://blog.csdn.net/smstong/article/details/4977976)<br /><br />
```shell
1，列出某个IP地址所提供的共享文件夹 
smbclient -L 198.168.0.1 -U username%password 

2,像FTP客户端一样使用smbclient 
smbclient //192.168.0.1/tmp -U username%password
执行smbclient命令成功后，进入smbclient环境，出现提示符： smb:/> 这时输入？会看到支持的命令
这里有许多命令和ftp命令相似，如cd 、lcd、get、megt、put、mput等。通过这些命令，我们可以访问远程主机的共享资源。 

3,直接一次性使用smbclient命令 
smbclient -c "ls" //192.168.0.1/tmp -U username%password
和 
smbclient //192.168.0.1/tmp -U username%password
smb:/>ls 
功能一样的 

例，创建一个共享文件夹 
smbclient -c "mkdir share1" //192.168.0.1/tmp -U username%password 
如果用户共享//192.168.0.1/tmp的方式是只读的，会提示 
NT_STATUS_ACCESS_DENIED making remote directory /share1 

4，除了使用smbclient，还可以通过mount和smbcount挂载远程共享文件夹 
挂载 mount -t cifs -o username=administrator,password=123456 //192.168.0.1/tmp /mnt/tmp 
取消挂载 umount /mnt/tmp
```

****************
### 参考文档：<br />
[CentOS 7下Samba服务器的安装与配置](http://www.cnblogs.com/muscleape/p/6385583.html)<br />
[CentOS7需要创建samba用户和密码才能访问Linux共享文件夹](https://ubuntuforums.org/showthread.php?t=1474213)<br />





***********
!["samba_07"](https://github.com/tycao/tycao.github.io/blob/master/src/samba_07.jpg "samba_07")<br /><br />
!["samba_08"](https://github.com/tycao/tycao.github.io/blob/master/src/samba_08.jpg "samba_08")<br /><br />
!["samba_09"](https://github.com/tycao/tycao.github.io/blob/master/src/samba_09.jpg "samba_09")<br /><br />
!["samba_10"](https://github.com/tycao/tycao.github.io/blob/master/src/samba_10.jpg "samba_10")<br /><br />

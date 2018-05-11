Linux�²���boost::property_tree �� `����xml�ļ�`
========================
### ����: UBuntu 16.04 64bit

### �����У�
```shell
# �������� �� һ����λ��������ɿ�ִ�г���main
root@ubuntu:/home/zogy/Desktop/Project# c++ -g -std=c++11 -Wall -DBOOST_LOG_DYN_LINK -o  ./tsd_config.cpp ./main.cpp -o main -rdynamic -lpthread -lboost_log -lboost_system -lboost_thread -lboost_filesystem 

# ��ǰĿ¼ `/home/zogy/Desktop/Project` �µ��ļ��ṹ
root@ubuntu:/home/zogy/Desktop/Project# ls -alrt
total 1440
-rwxrwxrwx 1 zogy zogy     660 5��  11 22:21 test_data.xml
-rwxrwxrwx 1 root root      67 5��  11 22:59 main.cpp
-rwxrwxrwx 1 zogy zogy    1833 5��  11 23:02 tsd_config.cpp
-rwxrwxrwx 1 zogy zogy    3489 5��  11 23:19 tsd_config.h
drwxr-xr-x 3 zogy zogy    4096 5��  11 23:26 ..
drwxrwxr-x 2 zogy zogy    4096 5��  11 23:35 .
-rwxr-xr-x 1 root root 1447092 5��  11 23:35 main
```
���߿���ʹ�÷ֲ����룺<br />
```shell
# ��������main.o�����ļ�
root@ubuntu:/home/zogy/Desktop/Project# c++ -g -std=c++11 -Wall -DBOOST_LOG_DYN_LINK -o ./main.o -c ./main.cpp

# �������ɿ�ִ�г���main
root@ubuntu:/home/zogy/Desktop/Project# c++ -g -std=c++11  ./main.o -o main -rdynamic -lpthread -lboost_log -lboost_system -lboost_thread -lboost_filesystem

# �鿴��ǰ���ɵ����ļ�
root@ubuntu:/home/zogy/Desktop/Project# ll
total 3064
drwxrwxr-x 2 zogy zogy    4096 5��  11 23:51 ./
drwxr-xr-x 3 zogy zogy    4096 5��  11 23:49 ../
-rwxr-xr-x 1 root root 1447092 5��  11 23:51 main*
-rwxrwxrwx 1 root root      67 5��  11 22:59 main.cpp*
-rw-r--r-- 1 root root 1659288 5��  11 23:51 main.o
-rwxrwxrwx 1 zogy zogy     660 5��  11 22:21 test_data.xml*
-rwxrwxrwx 1 zogy zogy    1833 5��  11 23:02 tsd_config.cpp*
-rwxrwxrwx 1 zogy zogy    3489 5��  11 23:19 tsd_config.h*

# ���п�ִ�г���
root@ubuntu:/home/zogy/Desktop/Project# ./main
ip_address_:127.0.0.1
mac_address_:mac_address
sys_id_:sys_id
srt_no_:
host_name_:host_name
os_name_:os_name
cpu_serial_no_:cpu_serial_no
disk_serial_no_:disk_serial_no
dbname_:dbname
opt_flag_:2
ar_account_id_:account_id
ar_account_type_:3
ar_adapter_type_:4
ar_adapter_scope_no_:5
ar_opt_flag_:2
root@ubuntu:/home/zogy/Desktop/Project# 
```
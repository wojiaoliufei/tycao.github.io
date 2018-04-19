一个简单的tomcat监控脚本
========
### 直接上代码：
#### monitor.sh
```shell
#!/bin/sh
# usage: check_once <port> <path>  
# 使用curl检查网页是否可以正常访问，如果不能访问就重启tomcat。  
check_once()  
{
        echo "$(date)  Tomcat check once"
        # add 200 OK test  
	# grep -q ： 表示禁止输出任何结果，以退出状态表示搜索是否成功。1代表搜索成功匹配。0代表匹配失败
        if curl -s -I --connect-timeout 5 --max-time 10 http://localhost:$1/$2 | grep -q '200 OK'; then  
                echo "$(date)  Tomcat maybe OK"  
        else  
                echo "$(date)  Tomcat maybe FAULT" 
		exec /usr/local/tomcat7/bin/startup.sh &
		sleep 30
        fi  
}  
  
# usage: check_loop <port> <path>  
# 每隔一分钟检查一次网页是否正常  
check_loop()  
{  
        while true
        do  
                sleep 6
                check_once $1 $2 >> ./check.$(date +%Y-%m-%d).log  2>&1
        done  
}  
  
# usage: monitor <path>  
# 对path指定的本机网页进行监控  
monitor()  
{  
        PORT=8080
		if	grep 'Connector port="8080"' /usr/local/tomcat7/conf/server.xml; then
				PORT=8080
		elif	grep 'Connector port="80"' /usr/local/tomcat7/conf/server.xml; then
				PORT=80
		else
				echo "Cannot detect connection port for Tomcat..."
				return -1
		fi
        echo "Tomcat server port is $PORT"  
		
       #if  [ $? -eq 0 ]; then
		# & 符号是使进程在后台运行
		check_loop $PORT "$1" &
}

# 监控路径 ： http://localhost:8080/examples/
monitor "examples/"
```


### 执行脚本：
```shell
bash monitor.sh
```

### 实时查看日志：
```shell
tail -f check-data.log
```
### history 命令：
```shell

[root@iZm5e1s45jg5kxtcyyoq13Z ~]# bash monitor_tomcat.sh
    <Connector port="8080" protocol="HTTP/1.1"
Tomcat server port is 8080
[root@iZm5e1s45jg5kxtcyyoq13Z ~]# tail -f chec
check.2018-04-19.log
[root@iZm5e1s45jg5kxtcyyoq13Z ~]# tail -f check.2018-04-19.log
Thu Apr 19 17:15:53 CST 2018  Tomcat check once
Thu Apr 19 17:15:54 CST 2018  Tomcat maybe OK
Thu Apr 19 17:16:00 CST 2018  Tomcat check once
Thu Apr 19 17:16:00 CST 2018  Tomcat maybe OK
Thu Apr 19 17:16:07 CST 2018  Tomcat check once
Thu Apr 19 17:16:08 CST 2018  Tomcat maybe OK
Thu Apr 19 17:16:15 CST 2018  Tomcat check once
Thu Apr 19 17:16:17 CST 2018  Tomcat maybe OK
^C
[root@iZm5e1s45jg5kxtcyyoq13Z ~]# ps -ef | grep monitor_tomcat.sh
root      8635     1  0 17:15 pts/0    00:00:00 bash monitor_tomcat.sh
root      8708  3809  0 17:16 pts/0    00:00:00 grep --color=auto monitor_tomcat.sh
[root@iZm5e1s45jg5kxtcyyoq13Z ~]# kill -9 8635
[root@iZm5e1s45jg5kxtcyyoq13Z ~]#
```

***********
### 参考文档：
[一个tomcat监控脚本](https://www.cnblogs.com/dim2046/p/5913701.html)<br />

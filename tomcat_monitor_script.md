一个简单的tomcat监控脚本
========
### 直接上代码：
#### monitor.sh
```shell
# usage: check_once <port> <path>  
# 使用curl检查网页是否可以正常访问，如果不能访问就重启tomcat。  
check_once()  
{  
        echo  
        echo "$(date)  Tomcat check once"  
        # 2008.08.21 -I/--head -s/--silent  
        #if curl -s -I --connect-timeout 5 --max-time 10 http://localhost:$1/; then  
        # 2010.02.16 add 200 OK test  
        if curl -s -I --connect-timeout 5 --max-time 10 http://localhost:$1/$2 | grep -q '200 OK';  
  
  
		then  
                echo "$(date)  Tomcat maybe OK"  
        else  
                echo "$(date)  Tomcat maybe FAULT" 
        fi  
}  
  
# usage: check_loop <port> <path>  
# 每隔一分钟检查一次网页是否正常  
check_loop()  
{  
        while true
        do  
                sleep 60 
                check_once $1 $2 >> ./check.$(date +%Y-%m-%d).log  2>&1
        done  
}  
  
# usage: monitor <path>  
# 对path指定的本机网页进行监控  
monitor()  
{  
        PORT=8080 
        echo "Tomcat server port is $PORT"  
  
                check_loop $PORT "$1" &  
                #check_loop $PORT "$1"  
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


***********
### 参考文档：
[一个tomcat监控脚本](https://www.cnblogs.com/dim2046/p/5913701.html)<br />

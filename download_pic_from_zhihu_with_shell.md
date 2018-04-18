使用`shell`爬取知乎的图片
==========

今天看到了这篇文章，觉得很有趣，然后就自己用自己的知乎id账号运行了一遍：<br />
### 首先，我使用Google浏览器，登录知乎，然后利用Chrome的debug模式，得到了自己的`知乎账号的authorization：`<br />
```shell
authorization: Bearer 2|1:0|10:1522680027|4:z_c0|92:Mi4xSjNWT0F3QUFBQUFBc082YzhNWmhEU1lBQUFCZ0FsVk4yNDZ2V3dCMjZmUHRUdlFJUTZZWXFOOUZkSkxUZWlNZUFB|a0fe09415ac4d5835c94d3c28a4f986d2ff7c94d64581bcfd80260cbe04eba54
```
!["08"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/sh_08.png "08")<br />


然后运行下面的命令，却报错了：<br />
```shell
curl --user-agent 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36' 'https://www.zhihu.com/api/v4/questions/40854395/answers?sort_by=default&include=data%5B%2A%5D.is_normal%2Cis_collapsed%2Cannotation_action%2Cannotation_detail%2Ccollapse_reason%2Cis_sticky%2Ccollapsed_by%2Csuggest_edit%2Ccomment_count%2Ccan_comment%2Ccontent%2Ceditable_content%2Cvoteup_count%2Creshipment_settings%2Ccomment_permission%2Cmark_infos%2Ccreated_time%2Cupdated_time%2Creview_info%2Crelationship.is_authorized%2Cis_author%2Cvoting%2Cis_thanked%2Cis_nothelp%2Cupvoted_followees%3Bdata%5B%2A%5D.author.follower_count%2Cbadge%5B%3F%28type%3Dbest_answerer%29%5D.topics&limit=20&offset=20'
```
!["07"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/sh_07.png "07")<br />
如上图所示，返回来错误的json信息：<br />
`{"error": {"message": "ZERR_NO_AUTH_TOKEN", "code": 100, "name": "AuthenticationInvalidRequest"}}`
<br /><br /><br />

#### 这是因为没有加上 `authorization`验证。加上之后，就会返回正常（且很长很长的）的json字符串：<br />
#### 现在把`authorization`添加上，万事俱备。接下来，我们运行下面的这个命令：<br />
```shell
curl --user-agent 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36' -H 'authorization: Bearer 2|1:0|10:1522680027|4:z_c0|92:Mi4xSjNWT0F3QUFBQUFBc082YzhNWmhEU1lBQUFCZ0FsVk4yNDZ2V3dCMjZmUHRUdlFJUTZZWXFOOUZkSkxUZWlNZUFB|a0fe09415ac4d5835c94d3c28a4f986d2ff7c94d64581bcfd80260cbe04eba54' 'https://www.zhihu.com/api/v4/questions/40854395/answers?sort_by=default&include=data%5B%2A%5D.is_normal%2Cis_collapsed%2Cannotation_action%2Cannotation_detail%2Ccollapse_reason%2Cis_sticky%2Ccollapsed_by%2Csuggest_edit%2Ccomment_count%2Ccan_comment%2Ccontent%2Ceditable_content%2Cvoteup_count%2Creshipment_settings%2Ccomment_permission%2Cmark_infos%2Ccreated_time%2Cupdated_time%2Creview_info%2Crelationship.is_authorized%2Cis_author%2Cvoting%2Cis_thanked%2Cis_nothelp%2Cupvoted_followees%3Bdata%5B%2A%5D.author.follower_count%2Cbadge%5B%3F%28type%3Dbest_answerer%29%5D.topics&limit=20&offset=20'
```
!["09"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/sh_09.png "09")<br />


结下来，就可以使用使用`正则表达式来解析知乎问题下的所有图片的绝对路径了。` 然后用`wget 来下载所有的图片。`<br />
#### download.sh
```shell
#!/bin/bash
# download.sh
# 使用方法 eg: ./download.sh https://www.zhihu.com/question/${question_number}
# 使用正则表达式获取每页回答中图片的url,并用wget下载
if [ ! $1 ]
then
echo 'need question url'
exit 1
fi

function gethtml(){
curl --user-agent 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36' -H 'authorization: oauth c3cef7c66a1843f8b3a9e6a1e3160e20' $1
}

ques_num=`echo $1 | egrep -o '[0-9]+'`
gethtml $1 | egrep -o 'data-original="[^"]*' | egrep -o 'https://[^ ]*'| sort |uniq >> $$.log
api="https://www.zhihu.com/api/v4/questions/${ques_num}/answers?sort_by=default&include=data%5B%2A%5D.is_normal%2Cis_collapsed%2Cannotation_action%2Cannotation_detail%2Ccollapse_reason%2Cis_sticky%2Ccollapsed_by%2Csuggest_edit%2Ccomment_count%2Ccan_comment%2Ccontent%2Ceditable_content%2Cvoteup_count%2Creshipment_settings%2Ccomment_permission%2Cmark_infos%2Ccreated_time%2Cupdated_time%2Creview_info%2Crelationship.is_authorized%2Cis_author%2Cvoting%2Cis_thanked%2Cis_nothelp%2Cupvoted_followees%3Bdata%5B%2A%5D.author.follower_count%2Cbadge%5B%3F%28type%3Dbest_answerer%29%5D.topics&limit=20&offset="
offset=3 
total=`gethtml $api$offset | egrep -o '"totals": [0-9][^,]*' | egrep -o '[0-9]+'`
total=`expr $total + 20`
api_html=''
for((offset=3;offset<$total;offset+=20)) 
do
    api_html=`echo $api${offset}` 
    gethtml $api_html| egrep -o 'data-original=\\"[^\]*' | egrep -o 'https://[^ ]*'|sort|uniq>>$$.log &
done
wait
echo 'get img url complete'
max_th=50 #指定最大线程数
# 线程控制
function getimg()
{
    if [[ $max_th -ge $((`ps | grep download.sh | wc -l` - 1)) ]] # 减一是前去‘grep fileme'的行
    then
    {
          wget --timeout 10 $url #设置超时时间
    }&
    else
        getimg
    fi
}
# 下载图片
for url in `cat $$.log`
do
    getimg
done
wait
echo 'img download complete'
```



然后，运行该脚本。注意：命令行参数必须要给，且是知乎问题的URL，形如：`https://www.zhihu.com/question/40854395` ：<br />
```shell
bash download.sh https://www.zhihu.com/question/40854395
```

### 运行截图：
!["01"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/sh_01.png "01")<br />
!["02"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/sh_02.png "02")<br />
!["03"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/sh_03.png "03")<br />
!["04"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/sh_04.png "04")<br />
!["05"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/sh_05.png "05")<br />
!["06"](https://github.com/tycao/tycao.github.io/blob/master/shell_crawler/sh_05.png "06")<br />





### history 命令：
```shell
Request:
GET /info HTTP/1.1
Accept-Language: zh-CN,zh;q=0.9
Accept-Encoding: gzip, deflate
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
Connection: keep-alive
Host: 120.27.18.180:12345
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36


api_url = 
https://www.zhihu.com/api/v4/questions/28258932/answers?sort_by=default&include=data%5B%2A%5D.is_normal%2Cis_collapsed%2Cannotation_action%2Cannotation_detail%2Ccollapse_reason%2Cis_sticky%2Ccollapsed_by%2Csuggest_edit%2Ccomment_count%2Ccan_comment%2Ccontent%2Ceditable_content%2Cvoteup_count%2Creshipment_settings%2Ccomment_permission%2Cmark_infos%2Ccreated_time%2Cupdated_time%2Creview_info%2Crelationship.is_authorized%2Cis_author%2Cvoting%2Cis_thanked%2Cis_nothelp%2Cupvoted_followees%3Bdata%5B%2A%5D.author.follower_count%2Cbadge%5B%3F%28type%3Dbest_answerer%29%5D.topics&limit=20&offset=3

authorization: Bearer 2|1:0|10:1522680027|4:z_c0|92:Mi4xSjNWT0F3QUFBQUFBc082YzhNWmhEU1lBQUFCZ0FsVk4yNDZ2V3dCMjZmUHRUdlFJUTZZWXFOOUZkSkxUZWlNZUFB|a0fe09415ac4d5835c94d3c28a4f986d2ff7c94d64581bcfd80260cbe04eba54

curl --user-agent 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36' -H 'authorization: Bearer 2|1:0|10:1522680027|4:z_c0|92:Mi4xSjNWT0F3QUFBQUFBc082YzhNWmhEU1lBQUFCZ0FsVk4yNDZ2V3dCMjZmUHRUdlFJUTZZWXFOOUZkSkxUZWlNZUFB|a0fe09415ac4d5835c94d3c28a4f986d2ff7c94d64581bcfd80260cbe04eba54'  'https://www.zhihu.com/api/v4/questions/27792828/answers?sort_by=default&include=data%5B%2A%5D.is_normal%2Cis_collapsed%2Cannotation_action%2Cannotation_detail%2Ccollapse_reason%2Cis_sticky%2Ccollapsed_by%2Csuggest_edit%2Ccomment_count%2Ccan_comment%2Ccontent%2Ceditable_content%2Cvoteup_count%2Creshipment_settings%2Ccomment_permission%2Cmark_infos%2Ccreated_time%2Cupdated_time%2Creview_info%2Crelationship.is_authorized%2Cis_author%2Cvoting%2Cis_thanked%2Cis_nothelp%2Cupvoted_followees%3Bdata%5B%2A%5D.author.follower_count%2Cbadge%5B%3F%28type%3Dbest_answerer%29%5D.topics&limit=20&offset=3'
```




**************
```shell
知乎链接：https://zhuanlan.zhihu.com/p/28258932
		  https://www.zhihu.com/question/40854395/answer/357230006
作者：娶不到静香的胖虎
```
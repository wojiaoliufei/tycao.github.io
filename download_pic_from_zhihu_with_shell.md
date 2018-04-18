使用`shell`爬去知乎的图片
==========
```shell
知乎链接：https://zhuanlan.zhihu.com/p/28258932
作者：娶不到静香的胖虎
```

今天看到了这篇文章，觉得很有趣，然后就自己用自己的知乎id账号运行了一遍：<br />
### 首先，我使用Google浏览器，登录知乎，然后利用Chrome的debug模式，得到了自己的`知乎账号的authorization：`<br />
```shell
authorization: Bearer 2|1:0|10:1522680027|4:z_c0|92:Mi4xSjNWT0F3QUFBQUFBc082YzhNWmhEU1lBQUFCZ0FsVk4yNDZ2V3dCMjZmUHRUdlFJUTZZWXFOOUZkSkxUZWlNZUFB|a0fe09415ac4d5835c94d3c28a4f986d2ff7c94d64581bcfd80260cbe04eba54
```

然后运行一下命令，却报错了：<br />
```shell
curl --user-agent 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36' 'https://www.zhihu.com/api/v4/questions/40854395/answers?sort_by=default&include=data%5B%2A%5D.is_normal%2Cis_collapsed%2Cannotation_action%2Cannotation_detail%2Ccollapse_reason%2Cis_sticky%2Ccollapsed_by%2Csuggest_edit%2Ccomment_count%2Ccan_comment%2Ccontent%2Ceditable_content%2Cvoteup_count%2Creshipment_settings%2Ccomment_permission%2Cmark_infos%2Ccreated_time%2Cupdated_time%2Creview_info%2Crelationship.is_authorized%2Cis_author%2Cvoting%2Cis_thanked%2Cis_nothelp%2Cupvoted_followees%3Bdata%5B%2A%5D.author.follower_count%2Cbadge%5B%3F%28type%3Dbest_answerer%29%5D.topics&limit=20&offset=20'
```

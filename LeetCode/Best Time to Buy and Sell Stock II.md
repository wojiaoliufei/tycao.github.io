最佳时间买卖股票
============
LeetCode地址 :point_right: [122. Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/)<br>

本题需要找出规律：<br>
如何才能获得最大利益? 我想到的就是, 我在最低的时候买, 在最高的时候卖不就行了? 于是我先随手列出测试用例, 看看自己想的对不对:<br>
		    4 3 6 7 8 9 10 4 6 3 9
最低为3, 最高是10, 赚了7块. 由于题意没有限制交易次数. 所以我在赚了一发之后, 还可以再玩, 开启上帝视角, 我发现 4买6卖, 3买9卖, 又可以再赚两把. 一共是7 + 2 + 6 = 15块. 貌似低买高卖有一个很重要的前提: 这个区间应该是一个 `从低到高的有序序列!`
<br>譬如, 4买为何在6卖? 而不是到9卖? 因为中间有个3 破坏了有序. 4买9卖, 赚5块; 4买6卖加3买9卖, 赚8块. 擦, 我一下子就明白了.<br>
如果基于有序这个前提, 那么我们的题意可以化简为: **找到全部有序子序列, 计算各序列首尾差值, 返回差值总和!**  核心代码就出来了：<br>
```cpp
int profit = 0;
for (auto i = v.begin(); i != v.end(); ++i)
  if (*i < *(i+1)) profit += *(i+1) - *i; // 写到这里, 应该发现风险, i+1敢随便用? 判断一下, i+1 != v.end();
return profit;
```

我的代码如下：<br>
#### best_time_to_sell_and_buy.h
```cpp
#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profits = 0;
        for (auto iter = prices.begin(); iter != prices.end(); ++iter) {
            if (((iter + 1) != prices.end()) && *iter < *(iter + 1)) {
                profits += *(iter + 1) - *iter;
            }
        }
        return profits;
    }
};
```

#### main.cpp
```cpp
#include "best_time_to_sell_and_buy.h"

int main(int argc, char *argv[])
{
    Solution s;
    std::vector<int> vInt = {4, 5, 7, 9, 1, 3, 6, 2, 3, 5, 9};
    std::cout << s.maxProfit(vInt) << "\n";
    return 0;
}
```

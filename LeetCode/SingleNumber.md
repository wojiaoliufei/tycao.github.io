找出一个数组（vector容器）里，单个出现的那个元素
=====================
LeetCode地址 :point_right: [Single Number](https://leetcode.com/problems/single-number/description/)<br />

使用了数字之间的 `异或` 运算，巧妙地找出了那个单个出现的数组元素。下面是我的代码：<br />
```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int j = 0;
        for (auto i : nums) {
            j ^= i;
        }
        return j;
    }
};
```

�ҳ�һ�����飨vector��������������ֵ��Ǹ�Ԫ��
=====================
LeetCode��ַ :point_right: [Single Number](https://leetcode.com/problems/single-number/description/)<br />

ʹ��������֮��� `���` ���㣬������ҳ����Ǹ��������ֵ�����Ԫ�ء��������ҵĴ��룺<br />
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

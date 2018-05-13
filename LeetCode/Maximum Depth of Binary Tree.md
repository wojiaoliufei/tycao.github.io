计算 `二叉树的最大路径长度`
=======================
LeetCode地址 :point_right: [104. Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/description/)<br />

本题是计算一个 `二叉查找树` 的最大路径长度。我的代码如下<br />
```cpp
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (NULL == root) return 0;
        return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

```
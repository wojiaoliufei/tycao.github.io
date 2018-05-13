#pragma once

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if (p && q) // 情况1：都不为空树
            return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        else if (!q && !p)  // 情况2：都为空树
            return true;
        else    // 情况3：只有一个为空树，另外一个非空树
            return false;
    }
};

#pragma once
#include <cstddef>
#include <vector>

struct TreeNode
{
    int val;
    TreeNode *right;
    TreeNode *left;
    TreeNode(int x) : val(x), right(NULL), left(NULL){}
};

class Solution {
public:
    std::vector<int> inorderTraverse(TreeNode *root) {
        std::vector<int> ret;
        if (NULL != root) {
            if (root->left)
                ret = inorderTraverse(root->left);
            ret.push_back(root->val);
            if (root->right) {
                auto vec = inorderTraverse(root->right);
                ret.insert(ret.end(), vec.begin(), vec.end());
            }
        }
        return ret;
    }
};

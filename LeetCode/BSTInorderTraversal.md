二叉树的中序遍历
===============
_**给定一个二叉树，返回它的节点权值的中序遍历**_
**********
#### C:\tycao.github.io\LeetCode\BSTInorderTraversal\bstinordertraversal.h
```cpp
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
```

#### main.cpp
```cpp
#include <iostream>
#include "bstinordertraversal.h"

/// Test Unit
/// {1,2,3,null,null,4,null,null,5}
/*
 *          1
 *         / \
 *        2   3
 *           /
 *          4
 *           \
 *            5
 */

int main(int argc, char *argv[])
{
    TreeNode root(1);
    TreeNode node2(2);
    TreeNode node3(3);
    TreeNode node4(4);
    TreeNode node5(5);

    root.left = &node2;
    root.right = &node3;
    node3.left = &node4;
    node4.right = &node5;

    for (auto i : Solution().inorderTraverse(&root)) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return 0;
}
```

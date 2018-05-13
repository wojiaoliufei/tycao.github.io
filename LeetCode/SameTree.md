给定两个二叉树，写一个函数判断它们是否相同
=================
### 两棵二叉树相同的定义：  `两棵二叉树结构相同，且对应节点的值相同，则被认为是这两颗二叉树相同。`
Example 01: <br>
	
	Input:     1         1
	          / \       / \
	         2   3     2   3
	
	        [1,2,3],   [1,2,3]
	
	Output: true

Example 02:<br>
	Input:     1         1
	          /           \
	         2             2
	
	        [1,2],     [1,null,2]
	
	Output: false
	
Example 03:
	Input:     1         1
	          / \       / \
	         2   1     1   2
	
	        [1,2,1],   [1,1,2]
	
	Output: false
*****************
本题目主要是运用了递归，和上次的那个 `找出一棵二叉树的最大路径长度` 很相似。都是运用了递归的思想去解决问题。
接下来，我们给出代码：<br>
#### sametree.h
```cpp
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
```

#### main.cpp
```cpp
#include <iostream>
#include "sametree.h"

/**
 * create a tree for test
 *                    1
 *                  /   \
 *                 2     3
 *                / \   /
 *               4   5  6
 *              / \
 *             7   8
 *                  \
 *                   9
*/


int main(int argc, char *argv[])
{
    TreeNode root1(1);
    TreeNode root2(1);
    TreeNode t2(2);
    TreeNode t3(3);
    TreeNode t4(4);
    TreeNode t5(5);
    TreeNode t6(6);
    TreeNode t7(7);
    TreeNode t8(8);
    TreeNode t9(9);

    root1.left = &t2;
    root1.right = &t3;
    root2.left = &t2;
    root2.right = &t3;

    t2.left = &t4;
    t2.right = &t5;
    t3.left = &t6;
    t4.left = &t7;
    t4.right = &t8;
    t8.right = &t9;

    Solution s;
    std::cout << std::boolalpha << s.isSameTree(&root1, &root2) << std::endl;

    return 0;
}
```

����������������дһ�������ж������Ƿ���ͬ
=================
### ���ö�������ͬ�Ķ��壺  `���ö������ṹ��ͬ���Ҷ�Ӧ�ڵ��ֵ��ͬ������Ϊ�������Ŷ�������ͬ��`
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
����Ŀ��Ҫ�������˵ݹ飬���ϴε��Ǹ� `�ҳ�һ�ö����������·������` �����ơ����������˵ݹ��˼��ȥ������⡣
�����������Ǹ������룺<br>
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
        if (p && q) // ���1������Ϊ����
            return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        else if (!q && !p)  // ���2����Ϊ����
            return true;
        else    // ���3��ֻ��һ��Ϊ����������һ���ǿ���
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

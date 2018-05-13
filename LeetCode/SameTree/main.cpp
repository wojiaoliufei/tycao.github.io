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

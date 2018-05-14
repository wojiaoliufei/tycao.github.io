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

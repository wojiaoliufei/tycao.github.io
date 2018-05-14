Linked List Cycle ： 检查一个链表里是否有环
==========================
_**给定一个链表，检测它是否有环。**_
**************

#### linkedcycle.h
```cpp
#pragma once

#include <cstddef>  /** for NULL */

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/**
 * 这个方法只能
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head && head->next) {
            for (ListNode *runner = head->next; runner; runner = runner->next) {
                if (head == runner) {
                    return true;
                }
            }
        }
        return false;
    }
};
*/

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head && head->next) {
            for (ListNode *slower = head, *faster = head->next;
                 faster && faster->next;
                 slower = slower->next, faster = faster->next->next) {
                if (slower == faster) {
                    return true;
                }
            }
        }
        return false;
    }
};
```

#### main.cpp
```cpp
#include <iostream>
#include "linkedcycle.h"

// Unit Test
//
//    |1|-|--> |2|-|--> |3|||
//    /|\                  |
//     |                  \|/
//    |||6| <--|-|5| <--|-|4|

int main(int argc, char *argv[])
{
    ListNode node1(1);
    ListNode node2(2);
    ListNode node3(3);
    ListNode node4(4);
    ListNode node5(5);
    ListNode node6(6);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node6;
    node6.next = &node1;

    std::cout << std::boolalpha << Solution().hasCycle(&node1) << "\n";
    return 0;
}

```

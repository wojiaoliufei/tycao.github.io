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

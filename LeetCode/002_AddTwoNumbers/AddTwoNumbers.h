//
//  AddTwoNumbers.h
//  LeetCode
//
//  Created by Lin Luo on 1/16/19.
//  Copyright © 2019 Linfinity. All rights reserved.
//

#pragma once

#ifndef AddTwoNumbers_h
#define AddTwoNumbers_h

namespace LeetCode_002 {
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };

    class Solution {
    public:
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            auto l1x = l1;
            auto l2x = l2;
            auto head = ListNode{-1};
            auto lx = &head;
            int carry = 0;
            while (l1x != nullptr || l2x != nullptr) {
                auto val = (l1x ? l1x->val : 0) + (l2x ? l2x->val : 0) + carry;
                if (val >= 10) {
                    val -= 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                l1x = l1x ? l1x->next : nullptr;
                l2x = l2x ? l2x->next : nullptr;
                lx->next = new ListNode(val);
                lx = lx->next;
            }
            if (carry == 1) {
                lx->next = new ListNode(1);
            }
            return head.next;
        }
    private:
    };
}

#endif /* AddTwoNumbers_h */

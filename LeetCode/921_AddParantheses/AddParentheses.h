//
//  AddParentheses.h
//  LeetCode
//
//  Created by Lin Luo on 1/5/19.
//  Copyright © 2019 Linfinity. All rights reserved.
//

#pragma once

#ifndef AddParentheses_h
#define AddParentheses_h

#include <stack>
#include <sstream>

namespace LeetCode_921
{
    class Solution {
    public:
        /*
         Algorithm: use a stack - when an opening parenthese '(' is encountered, push it onto the stack
         when a closing parenthese ')' is encountered, pop one '(' from the stack - if the stack is empty, it means an previous opening '(' is missing
         when the original string is finished, for all the opening '(' still remaining on the stack, we are missing all the matching closing ')'
         */
        int minAddToMakeValid(const std::string& s) {
            int r = 0;
            std::stack<char> stack;
            for (auto c : s) {
                if (c == '(') {
                    stack.push(c);
                } else if (c == ')') {
                    if (!stack.empty()) {
                        stack.pop();
                    } else {
                        ++r;
                    }
                }
            }
            r += stack.size();
            return r;
        }

        /*
         Algorithm: not using extra space (space complexity - O(1))
         when an opening parens is encountered, increment nopening by 1
         when a closing parens is encountered, if there are remaining opening parens (nopening > 0), decrement nopening by 1 (which means it's balanced)
         if there are no remaining opening parens, we have an orphaned closing parens, increment nclosing by 1
         when the string is finished, if all the parens are balanced, the end result should be 0 (nopening and nclosing should both be 0)
         if not, then any remaining opening parens are missing the number of closing parens, and any outstanding closing parens (nclosing) requires the same
         number of opening parens to balance, so the result is nopening + nclosing
         */
        int minAddToMakeValid2(const std::string& s) {
            int nopening = 0;
            int nclosing = 0;
            for (auto c : s) {
                if (c == '(') {
                    ++nopening;
                } else if (c == ')') {
                    if (nopening > 0) {
                        --nopening;
                    } else {
                        ++nclosing;
                    }
                }
            }
            return nopening + nclosing;
        }
    };
}

#endif /* AddParentheses_h */

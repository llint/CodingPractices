//
//  IsSubsequence.h
//  LeetCode
//
//  Created by Lin Luo on 1/6/19.
//  Copyright © 2019 Linfinity. All rights reserved.
//

#pragma once

#ifndef IsSubsequence_h
#define IsSubsequence_h

#include <set>
#include <string>
#include <iostream>

namespace LeetCode_392
{
    class Solution {
    public:
        /*
         Algorithm: t is huge, s is short - it would not be practical to iterate through t, and trying to find out if s is a subsequence
         furthermore, if we have a lot of s to check, it is practically not feasible to iterate through t every time
         since we may assume that there are only lower case english characters, i.e. 26 possible occurrences, we can preprocess t, and put
         the indices of each given character in a sorted set, so for each input s, and for each character, we get its current index from the
         table, and then for the next character, we need to locate an index bigger than the current index - if not existing, we can return false
         or if for the next character we cannot find an valid index that is larger than the previous index, return false
         */
        bool isSubsequence(const std::string& s, const std::string& t) {
            std::set<ssize_t> occurrences[26]; // NB: use of ssize_t instead of size_t for putting the initial condition as -1
            for (size_t i = 0; i < t.size(); ++i) {
                // save all the indices each character has appeared in the string t
                // the set is essentially ordered in a binary tree, so searching is O(lgN)
                occurrences[t[i] - 'a'].insert(i);
            }

            ssize_t lastIndex = -1; // NB: initial value, less than 0, since the first upper_bound index could be 0
            for (size_t i = 0; i < s.size(); ++i) {
                size_t idx = s[i] - 'a';
                auto it = occurrences[idx].upper_bound(lastIndex); // use of upper_bound for strictly larger value
                if (it != occurrences[idx].end()) {
                    lastIndex = *it;
                } else {
                    return false;
                }
            }

            return true;
        }

        /*
         Algorithm: this is a little brutal force - find the first character from s in t
         from this index for t and 0 for s, for each character in t from this index x, check if there is a match for the current s at index y
         if yes, increment y (while x is always incrementing) until either string is consumed
         the tricky part is: once this one pass is finished, if a subsequence is found, all good, and we are done; while we are also done if no
         subsequence is found - there is no need to check the next starting position and repeat the process - (XXX - always return)
         the method we are using here implicitly is a greedy search - meaning if a subsequence is not found, there must be a character missing in t
         so even if you try other starting positions, this missing character is still missing, so no need to try - so the algorithm is essentiall O(n)
         */
        bool isSubsequence2(const std::string& s, const std::string& t) {
            for (size_t i = 0; i < t.size(); ++i) {
                if (t[i] == s[0]) {
                    size_t y = 0;
                    for (size_t x = i; x < t.size() && y < s.size(); ++x) {
                        if (t[x] == s[y]) {
                            ++y;
                        }
                    }
                    return y == s.size(); // XXX
                }
            }
            return false;
        }
    };

    void Test_IsSubsequence() {
        Solution solution;

        {
            std::string t = "yyyyylyyyyeyyyyyyeyyyyyeyytyyyycyyyyyoyyydyyyyyyyeyyyyyy";
            std::string s = "leetcode";
            std::cout << solution.isSubsequence(s, t) << std::endl;
        }

        {
            std::string t = "ahbgdc";
            std::string s = "abc";
            std::cout << solution.isSubsequence(s, t) << std::endl;
        }
    }
}

#endif /* IsSubsequence_h */

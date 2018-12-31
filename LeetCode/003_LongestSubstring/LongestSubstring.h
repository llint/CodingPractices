//
//  LongestSubstring.h
//  LeetCode
//
//  Created by Lin Luo on 12/24/18.
//  Copyright © 2018 Linfinity. All rights reserved.
//

#pragma once

#ifndef LongestSubstring_h
#define LongestSubstring_h

#include <string>
#include <optional>

namespace LeetCode_003
{
    /*
     * there is a similar problem: how to detect if a string has non-repeating characters
     * brutal force approach would be: for each character in the string, check it against all the other characters, complexity is O(n^2)
     * optimal approach: for each character in the string, build an occurrences table incrementally, check each character against the occurrences table
     * mark the occurrence of the new character if not existing, or otherwise, we've found a duplicate - complexity is O(n) - since we are going through
     * the string only once, and we build the table incrementally!
     *
     * Algorithm:
     * - keep track of the start and end indices, both begin at 0
     * - keep track of the character occurrences of the current string [start, end), with the index of the character in the original whole string
     * - move the end index forward, for each new character introduced, if it is not in the occurrences table, add the character with the absolute index in the original string
     * - if it is in the occurrences table, we've found a duplicate in the current (start, end) substring; so we move the start index all the way to the index that is after
     *   the duplicated character index (which could be retrieved from the occurrences table);
     * - while moving the start index to the new location, reset the entries in the occurrences table for those characters that are skipped by the start index (since they may
     *   re-appear later), the new start index marks the start of the new substring to check - up until the current end index (which caused the duplicate)
     * - add the new character to the occurrences table - even if it is the one which caused the duplicate (since it has been removed from the occurrences table by the move of the
     *   start index to the new location.
     *
     */
    size_t LongestSubstring(const std::string& s) {
        std::optional<size_t> occurrences[256];
        size_t start = 0;
        size_t end = 0;
        size_t longest = 0;
        while (end < s.size()) {
            auto c = s[end];
            if (occurrences[c]) {
                // if the new character already occurred in the existing sequence,
                // move the 'newStart' up to one after the position of the duplicated character
                size_t newStart = occurrences[c].value() + 1;
                // reset the occurrence table for the characters that have just been skipped (including the duplicated character)
                for (size_t i = start; i < newStart; ++i) {
                    occurrences[s[i]].reset();
                }
                // set the 'start' to 'newStart', and we are on the new string, with the part before the duplicated character (inclusive) truncated
                start = newStart;
            }
            // then set the position of the new character in the occurrence table
            occurrences[c] = end++;
            if (end - start > longest) {
                longest = end - start;
            }
        }
        return longest;
    }

    void Test_LongestSubstring()
    {
        std::string s = "abcdecxyzx";
        std::cout << LongestSubstring(s) << std::endl;
    }
}

#endif /* LongestSubstring_h */

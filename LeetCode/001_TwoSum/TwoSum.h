//
//  TwoSum.h
//  LeetCode
//
//  Created by Lin Luo on 1/16/19.
//  Copyright © 2019 Linfinity. All rights reserved.
//

#pragma once

#ifndef TwoSum_h
#define TwoSum_h

#include <vector>
#include <unordered_map>

namespace LeetCode_001 {
    class Solution {
    public:
        /*
         Algorithm: instead of doing brutal force, we use a table 'others' to track any past numbers while we go through the vector
         if the difference between the target and the next number has an entry in 'others', we've found a match!
         */
        std::vector<size_t> twoSum(std::vector<int>& nums, int target) {
            std::unordered_map<int, size_t> others;
            for (size_t i = 0; i < nums.size(); ++i) {
                int other = target - nums[i]; // compute the other
                auto it = others.find(other);
                if (it != others.end()) {
                    // match found, and the match must have appeared before
                    return {it->second, i}; // not the ordering, since we always put the earlier items in the table, the current index must be later!
                }
                others[nums[i]] = i; // no match yet, incrementally put it in the others table
            }
            return {};
        }
    private:
    };
}


#endif /* TwoSum_h */

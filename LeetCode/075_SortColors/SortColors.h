//
//  SortColor.h
//  LeetCode
//
//  Created by Lin Luo on 12/29/18.
//  Copyright © 2018 Linfinity. All rights reserved.
//

#pragma once

#ifndef SortColor_h
#define SortColor_h

#include <vector>
#include <sstream>

namespace LeetCode_075
{
    class Solution {
    public:
        /*
         Algorithm: swap 0 towards the front of the list, swap 2 towards the end of the list
         Keep track of 3 indices:
         - idx_0: when the next 0 is encountered, the index, towards the start of the list, of the number where the newly encountered 0 can be swapped with
           idx_0 starts from 0, and grow towards the end of the list
         - idx_2: when the next 2 is encountered, the index, towards the end of the list, of the number where the newly encountered 2 can be swapped with
           idx_2 starts from nums.size()-1, and grow towards the start of the list
         - index: this is the cursor going through the list itself - the next 0, or 1, or 2 is indicated by this index

         when the next 0 is swapped with a previous number at idx_0, idx_0 is incremented by 1, and index is also incremented by 1
         - special case: {0, 0, 0, ...} if a list starts like this, each 0 will be swapped with itself, until it reaches a non-zero value!
         when the next 1 is encountered (by index), index is incremented by 1
         when the next 2 is encountered (by index), 2 is swapped with the number at idx_2, and idx_2 is decremented by 1, but index is not incremented, since we need
         to recheck the newly swapped number - it could be either 0, 1, 2
         0: this 0 will be swapped towards the start of the list (causing idx_0 to increment), and the swapped value can only be 1 (any 2 before this index would have already been swapped!)
         so our index increment logic would not break (remember that after we swap a 0 to the front, we increment the index by 1?)
         1: the normal logic will increment index by 1
         2: {2, 0, 2} - if 2 is swapped with another 2 at the end, it causes idx_2 to be decremented by 1, so if we re-process the swapped 2, we would swap it with the number
            at the decremented idx_2, which is another number, which might be any of the 0, 1, 2 again - until all the continguous 2's are consumed by decrementing idx_2 - either
         idx_2 runs below idx_0, then we reach the end condition: like {1, 1, 2, 2}
         */
        void sortColors(std::vector<int>& nums) {
            size_t idx_0 = 0;
            size_t idx_2 = nums.size() - 1;

            size_t i = idx_0;
            while ((ssize_t)(i - idx_2) <= 0) {
                if (nums[i] == 0) {
                    nums[i++] = nums[idx_0]; // NB: this cannot be 2, since any 2 before this index would have been swapped to the end
                    nums[idx_0++] = 0;
                } else if (nums[i] == 2) {
                    nums[i] = nums[idx_2]; // could be 0 or 1 - note that since we need to check the newly swapped value in this index again, i is not incremented
                    nums[idx_2--] = 2;
                } else if (nums[i] == 1) {
                    ++i;
                }
            }
        }
    };

    std::string stringize(const std::vector<int>& nums)
    {
        if (nums.empty()) {
            return "[]";
        }
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0; i < nums.size() - 1; ++i)
        {
            ss << nums[i] << ", ";
        }
        ss << nums.back() << "]";
        return ss.str();
    }
 
    void Test_SortColors()
    {
        Solution solution;

        {
            // case A: this is the case, where 2 is swapped with 0, and then 0 is rechecked and swapped with 1
            std::vector<int> nums = {1, 2, 0};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            // case A: this is the case, where 2 is swapped with 0, and then 0 is rechecked and swapped with 1
            std::vector<int> nums = {1, 1, 2, 2};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {0};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {1};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {2};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {2, 0};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {0, 2};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {1, 1, 1};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {0, 0, 1, 1, 1, 2, 2};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {0, 0, 0, 0, 0, 0, 0};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {2, 2, 2, 2, 2, 2, 2};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {0, 0, 1, 1, 0, 2, 2};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {2, 0, 2, 1, 1, 2, 2};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }

        {
            std::vector<int> nums = {2, 1, 0, 2, 0, 1, 0, 1, 0};
            solution.sortColors(nums);
            std::cout << stringize(nums) << std::endl;
        }
    }
}

#endif /* SortColor_h */

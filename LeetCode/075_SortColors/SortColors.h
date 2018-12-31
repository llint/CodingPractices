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
            return "<empty>";
        }
        std::stringstream ss;
        for (size_t i = 0; i < nums.size() - 1; ++i)
        {
            ss << nums[i] << ", ";
        }
        ss << nums.back();
        return ss.str();
    }

    void Test_SortColors()
    {
        Solution solution;

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

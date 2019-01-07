//
//  FindDuplicate.h
//  LeetCode
//
//  Created by Lin Luo on 1/6/19.
//  Copyright © 2019 Linfinity. All rights reserved.
//

#pragma once

#ifndef FindDuplicate_h
#define FindDuplicate_h

#include <vector>
#include <algorithm>

namespace LeetCode_287
{
    class Solution {
    public:
        /*
         Algorithm: based on the fact that the numbers range from 1 to n and we have n+1 slot array
         based on the pegion theorithm, there must be at least one duplicate of one number
         the algorithm to find the duplicate without using any extra space (e.g. no hashmap, or tree) is:
         starting from the first item in the input array, swap it with the number in the corresponding index
         if the number at a given index is matching (number == index + 1), move to the next index and repeat the process
         if a number is larger than the valid index, it is a duplicate, we are done.
         Note: the basic algorithm is actually try to place each number to its actual index (in place), and if there are duplicates
         the corresponding location should already have that number

         NB: this algorithm may feel like O(n^2) at first glance, since a rough thinking is every value would be potentially swapped with other values
         and worst case at each index, remaining - 1 swaps would happen, so it feels like n x (n-1) * (n-2) * ... * 1, and this is roughly O(n^2)
         however, each swapping has a significant effect, in that each swap will put a number back to its corresponding index
         so a seemingly worst cast swapping at index 0 for n - 1 times would already put all the number in place already, and the duplicate already found (XXX)!
         so the runtime complexity is still O(n)
         */
        int findDuplicate(std::vector<int>& nums) {
            for (size_t i = 0; i < nums.size();) {
                if (nums[i] == i + 1) {
                    // the number matches its index, move to the next
                    ++i;
                } else if (nums[i] < i + 1) {
                    // the number is less than the current iteration index, it means its duplicate should have existed before the current index
                    return nums[i];
                } else {
                    // the number is in the future, try to swap the number to its actual corresponding location
                    size_t i2 = nums[i] - 1;
                    if (nums[i] == nums[i2]) {
                        // duplicate already! (XXX)
                        return nums[i];
                    }
                    // nums[i2] should contain the corresponding number
                    // nums[i] now contains the number that we'll check again (i not incremented)
                    // it could make the index move forward if this number is at the index
                    // or more swapping will happen, until one value swapped in makes the index move forward
                    std::swap(nums[i], nums[i2]);
                }
            }
            return 0;
        }

        /*
         Algorithm: this is both tricky and simple - (and elegant)
         for each number in the array, mark the value in the corresponding index (n - 1) to be negative
         as we go through the array, if there is another number in the array that tries to mark the corresponding value, and found it is already negative
         it means this number must be a duplicate of a number that has already appeared
         the reason for setting the corresponding value to be minus is that it preserves the original number, and also provides a flag for "marked" already
         one needs to be careful that since any value along going through the array could be already negative, so we need to use std::abs to get the original value
         */
        int findDuplicate2(std::vector<int>& nums) {
            for (size_t i = 0; i < nums.size(); ++i) {
                size_t i2 = std::abs(nums[i]) - 1;

                if (nums[i2] < 0) {
                    return std::abs(nums[i]);
                }

                nums[i2] = -nums[i2];
            }
            return 0;
        }
    };
}

#endif /* FindDuplicate_h */

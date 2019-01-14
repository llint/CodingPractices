//
//  MaxPointsInRange.h
//  LeetCode
//
//  Created by Lin Luo on 1/12/19.
//  Copyright © 2019 Linfinity. All rights reserved.
//

#pragma once

#ifndef MaxPointsInRange_h
#define MaxPointsInRange_h

#include <set>
#include <vector>
#include <algorithm>

namespace CruiseOnsite
{
    /*
     Problem: given a list of numbers, and a range, return the maximum number of indices the range can cover
     Algorithm: basically a sliding window algorithm
     1. sort the numbers using a map
     2. the range is a sliding window, and from the smallest number, use each number as a starting point
     3. for each next numbers starting from the start window, check the distance, if the distance is smaller than the range, increment the count
     4. keep moving until it reachs the end

     The issue of the above algorithm is that the complexity is at the level of O(n^2), since for each new window start (the next number), it's
     rechecking the distance of the already included numbers against the windows starting number

     A better algorithm is: once the start window index moves to the next number, the numbers that were in the previous window must still in the new window range, EXCEPT
     the first number of the old window is now skipped! we don't have to recheck those numbers against the new window start - even though the differences would
     be different from the old window, but those numbers are still in the number (EXCEPT the first number of the old window!) - so we don't have to perform
     the re-calculations!

     What is needed for the new window is only to start from the index past the last number of the old window, and check as many as the new numbers that are
     within the range against the new start number - and the process repeats until we reach the end
     */
    size_t MaxPointsInRange_O_n_squared(std::vector<int>& numbers, int range) {
        size_t mcount = 0;
        std::sort(numbers.begin(), numbers.end());
        for (size_t i = 0; i < numbers.size(); ++i) {
            size_t count = 0;
            for (size_t j = i; j < numbers.size(); ++j) { // XXX: note that j starts from i, so it always counts the start index
                if (numbers[j] - numbers[i] <= range) {
                    ++count;
                }
            }
            if (count > mcount) {
                mcount = count;
            }
        }
        return mcount;
    }

    size_t MaxPointsInRange_O_n(std::vector<int>& numbers, int range) {
        std::sort(numbers.begin(), numbers.end());

        size_t count = 0, mcount = 0;
        for (size_t startIndex = 0, endIndex = 0; endIndex < numbers.size();) {
            if (numbers[endIndex] - numbers[startIndex] <= range) {
                ++count;
                ++endIndex;
            } else {
                if (count > mcount) {
                    mcount = count;
                }
                --count;
                ++startIndex;
            }
        }

        if (count > mcount) {
            mcount = count;
        }
        return mcount;
    }

    void Test_MaxPointsInRange_O_n() {
        std::vector<int> numbers = {0, 1, 2, 5};
        std::cout << MaxPointsInRange_O_n(numbers, 2) << std::endl;
    }
}


#endif /* MaxPointsInRange_h */

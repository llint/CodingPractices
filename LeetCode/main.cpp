//
//  main.cpp
//  LeetCode
//
//  Created by Lin Luo on 12/24/18.
//  Copyright © 2018 Linfinity. All rights reserved.
//

#include <iostream>

#include "003_LongestSubstring/LongestSubstring.h"
#include "133_CloneGraph/CloneGraph.h"
#include "075_SortColors/SortColors.h"
#include "079_WordSearch/WordSearch.h"
#include "056_MergeInterval/MergeInterval.h"
#include "921_AddParantheses/AddParentheses.h"
#include "287_FindDuplicate/FindDuplicate.h"
#include "392_IsSubsequence/IsSubsequence.h"
#include "x01_PathExists/PathExists.h"
#include "x02_MaxPointsInRange/MaxPointsInRange.h"

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";

    LeetCode_003::Test_LongestSubstring();

    LeetCode_075::Test_SortColors();

    LeetCode_079::Test_WordSearch();

    LeetCode_392::Test_IsSubsequence();

    LeetCode_x01::Test_PathExists();

    CruiseOnsite::Test_MaxPointsInRange_O_n();

    return 0;
}

//
//  WordSearch.h
//  LeetCode
//
//  Created by Lin Luo on 1/3/19.
//  Copyright © 2019 Linfinity. All rights reserved.
//

#pragma once

#ifndef WordSearch_h
#define WordSearch_h

#include <tuple>
#include <string>
#include <vector>
#include <iostream>

namespace LeetCode_079
{
    /*
     Algorithm: this is essentially DFS
     1. look for the first character in the input word in the board in a linear fashion
     2. once the first character is located in the board, from this location conduct the recursive DFS process
     3. the recursive DFS process takes the folloing inputs:
        - the board itself
        - the pivot location
        - the word string (immutable)
        - the current index into the world to check
     4. if the character at the pivot location is the same as the current character to check in the input word,
        mark the pivot position as visited
     5. for the 4 directions around the pivot position, conduct the same DFS process on each branch, and if any
        branch returns true, we are done - no need to check other directions (early exit)
     6. when the current level of DFS is finished, restore the original character at the pivot position, so the
        this character is not marked as visited anymore, so the previous level DFS would check another direction
        and this location can be visited again - remember this is a recursive process, back tracking should make
        sure the state is restored when the current level finished? and as a side effect, when the full word is
        verified, and all the DFS stack is rewinded, the board is then restored to its original content, without
        any marks!
        note that originally I was using a hashset to track the visited locations instead of directly marking,
        and pass the hashset by value to each lower level of DFS, to achieve automatic state restore after rewinding
        the overhead of copying the hashset (and destructing) at each DFS level is quite expensive, even though
        with the benefits of automatic back tracking restoring - this is similar to functional programming, but
        just too expensive.
     */
    class Solution {
    public:
        bool exist(std::vector<std::vector<char>>& board, const std::string& word) {
            for (size_t y = 0; y < board.size(); ++y) {
                for (size_t x = 0; x < board[y].size(); ++x) {
                    // start the DFS only when the first character in the word matches any location in the board
                    if (word[0] == board[y][x]) {
                        if (check(board, y, x, word, 0)) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    private:
        static constexpr const char VISITED = '\0';

        // recursive DFS check process, with in-place marking of the board for visited locations
        bool check(std::vector<std::vector<char>>& board, size_t y, size_t x, const std::string& word, size_t charIndex) {
            // four directions around the pivot location
            static const std::tuple<size_t, size_t> dirs[] = {{-1,0}, {0,1}, {1,0}, {0,-1}}; // {dy,dx}

            auto c1 = board[y][x];
            auto c2 = word[charIndex];

            bool verified = false;
            if (c1 != VISITED && c1 == c2) { // the pivot location is not yet visited, and it matches the character to check
                if (charIndex+1 == word.size()) {
                    // this is also the last character to check in the input word, we are done!
                    verified = true;
                } else {
                    board[y][x] = VISITED; // mark this location as visited, so any deeper level checking will know
                    for (const auto& [dy, dx] : dirs) {
                        // next location to check as one of the four directions from the current pivot
                        auto [y2, x2] = std::make_tuple(y + dy, x + dx);
                        if ((ssize_t)y2 >= 0 && y2 < board.size() &&
                            (ssize_t)x2 >= 0 && x2 < board[y2].size()) { // make sure the new location is a valid location - the board could be jagged, or we are at the edge
                            if (check(board, y2, x2, word, charIndex+1)) { // recursive DFS to one direction, and the next character in the word to check
                                verified = true; // as soon as this branch is verified - it must have gone down all the way and still being successful, we are done
                                break; // not returning directly lets the board restoring logic to execute
                            }
                        }
                    }
                    board[y][x] = c1; // restore the original character so the upper level moves to another location and this location is clean
                }
            }
            return verified;
        }
    };

    void Test_WordSearch()
    {
        Solution solution;

        {
            std::vector<std::vector<char>> board = {
                {'a'}
            };
            std::cout << (solution.exist(board, "a") ? "true" : "false") << std::endl;
        }

        {
            std::vector<std::vector<char>> board = {
                {'A','B','C','_'},
                {'_','_','D','_'},
                {'_','F','E','_'}};
            std::cout << (solution.exist(board, "ABCDEF") ? "true" : "false") << std::endl;
        }
    }
}

#endif /* WordSearch_h */

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
    class Solution {
    public:
        bool exist(std::vector<std::vector<char>>& board, const std::string& word) {
            for (size_t y = 0; y < board.size(); ++y) {
                for (size_t x = 0; x < board[y].size(); ++x) {
                    if (word[0] == board[y][x]) {
                        if (check(board, x, y, word, 0)) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    private:
        static constexpr const char NONE = '\0';
        bool check(std::vector<std::vector<char>>& board, size_t x, size_t y, const std::string& word, size_t charIndex) {
            static const std::tuple<size_t, size_t> dirs[] = {{0,-1}, {1,0}, {0,1}, {-1,0}};

            auto c1 = board[y][x];
            auto c2 = word[charIndex];

            bool verified = false;
            if (c1 != NONE && c1 == c2) {
                if (charIndex+1 == word.size()) {
                    verified = true;
                } else {
                    board[y][x] = NONE;
                    for (const auto& [dx, dy] : dirs) {
                        auto [x2, y2] = std::make_tuple(x + dx, y + dy);
                        if ((ssize_t)y2 >= 0 && (ssize_t)x2 >= 0 && 
                            y2 < board.size() && x2 < board[y2].size()) {
                            if (check(board, x2, y2, word, charIndex+1)) {
                                verified = true;
                                break;
                            }
                        }
                    }
                    board[y][x] = c1;
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

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

#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

namespace std
{
    template<>
    struct hash<std::pair<size_t, size_t>>
    {
        size_t operator()(const std::pair<size_t, size_t>& p) const noexcept
        {
            return hash<size_t>()(p.first) ^ hash<size_t>()(p.second);
        }
    };
}

namespace LeetCode_079
{
    class Solution {
    public:
        bool exist(const std::vector<std::vector<char>>& board, const std::string& word) {
            for (size_t y = 0; y < board.size(); ++y) {
                for (size_t x = 0; x < board[y].size(); ++x) {
                    if (word[0] == board[y][x]) {
                        if (check(board, {x, y}, {}, word, 0)) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    private:
        bool check(const std::vector<std::vector<char>>& board, const std::pair<size_t, size_t>& location,
                   std::unordered_set<std::pair<size_t, size_t>> occurrences, const std::string& word, size_t charIndex) {
            static const std::pair<size_t, size_t> dirs[] = {{0,-1}, {1,0}, {0,1}, {-1,0}};

            auto c1 = board[location.second][location.first];
            auto c2 = word[charIndex];

            if (occurrences.find(location) == occurrences.end() && c1 == c2) {
                if (charIndex+1 == word.size())
                {
                    return true;
                }
                occurrences.insert(location); // add center
                for (const auto& dir : dirs) {
                    auto newLocation = std::make_pair(location.first + dir.first, location.second + dir.second);
                    if ((ssize_t)newLocation.first >= 0 && (ssize_t)newLocation.second >= 0 &&
                        newLocation.second < board.size() && newLocation.first < board[newLocation.second].size()) {
                        if (check(board, newLocation, occurrences, word, charIndex+1)) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    };

    void Test_WorldSearch()
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

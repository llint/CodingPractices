//
//  FindPath.h
//  LeetCode
//
//  Created by Lin Luo on 1/8/19.
//  Copyright © 2019 Linfinity. All rights reserved.
//

#pragma once

#ifndef FindPath_h
#define FindPath_h

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <iostream>

namespace LeetCode_x01
{
    class DirectedGraph {
    public:
        DirectedGraph(const std::vector<std::pair<int, int>>& segments) {
            for (const auto& segment : segments) {
                graph[segment.first].insert(segment.second);
            }
        }

        bool PathExists(int a, int b) {
            if (visited.find(a) != visited.end()) {
                return false; // cycle!
            }
            bool r = false;
            auto it = graph.find(a);
            if (it != graph.end()) {
                visited.insert(a);
                for (auto x : it->second) {
                    if (x == b || PathExists(x, b)) {
                        r = true;
                        break;
                    }
                }
                visited.erase(a);
            }
            return r;
        }
    private:
        std::unordered_set<int> visited;
        std::unordered_map<int, std::unordered_set<int>> graph;
    };

    void Test_PathExists() {
        DirectedGraph dg{{{1, 2}, {3, 2}, {2, 4}, {4, 1}, {4, 3}, {4, 5}, {6, 1}}};

        std::cout << "PathExists: " << dg.PathExists(6, 5) << std::endl;
    }
}

#endif /* FindPath_h */

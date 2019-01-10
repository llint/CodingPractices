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
    /*
     Algorithm: we used a slightly different way to represent the graph: an map of nodeId to its neighbor nodeIds
     The assumption is that each node has a unique ID. compare this to a more traditional way of representing a graph (133)
     the advantage of using a map is we can quickly locate the start node by its ID, otherwise, if we use a node struct
     a node pointer is probably needed - software engineering wise, one should use ID rather than pointer to be more cross platform
     Also, the start end pairs are given, it is much natural that each node is represented as IDs, and the preprocessing is much more naturally done

     The biggest difference in the node struct pointer strategy is all the neighbors are direct pointers as well, so there would be no extra map look up
     for the next node in order to find his neighbors. but cloning the graph involves some extra thinking (handling cycles, many paths, etc.)

     with the ID approach, there is a lookup for each new node to be explored (could be slower)

     but the biggest benefit, with the map data structure here, cloning graph is merely a deep copy of the "graph"! no complex traversal needs to be done!

     With the graph built, PathExists is a recursive function that recursively checks if a start node id can reach the end node id by checking the start node's
     immediate neighbors one by one, and then recursively doing the DFS

     visited is used to track the visited nodes, in order to rule out the cycles - when a cycle is detected, this path is considered false, and the DFS back track
     to the next neighbor, once all the neighbors are done, the visited is cleaned for that node and back track
     */
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
        // {nodeId: neighbor nodeIds}
        std::unordered_map<int, std::unordered_set<int>> graph;
    };

    void Test_PathExists() {
        DirectedGraph dg{{{1, 2}, {3, 2}, {2, 4}, {4, 1}, {4, 3}, {4, 5}, {6, 1}}};

        std::cout << "PathExists: " << dg.PathExists(6, 5) << std::endl;
    }
}

#endif /* FindPath_h */

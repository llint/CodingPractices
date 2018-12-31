//
//  CloneGraph.h
//  LeetCode
//
//  Created by Lin Luo on 12/26/18.
//  Copyright © 2018 Linfinity. All rights reserved.
//

#pragma once

#ifndef CloneGraph_h
#define CloneGraph_h

#include <vector>
#include <unordered_map>

struct UndirectedGraphNode {
    const int label;
    std::vector<UndirectedGraphNode*> neighbors;

    UndirectedGraphNode(int label) : label(label) {}
};

class Solution {
public:
    // UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node)
    // {
    //     if (node == nullptr) return nullptr;
    //     UndirectedGraphNode* node2 = new UndirectedGraphNode(node->label);
    //     visited.emplace(node, node2);
    //     for (auto* neighbor : node->neighbors) {
    //         auto it = visited.find(neighbor);
    //         if (it == visited.end()) {
    //             node2->neighbors.push_back(cloneGraph(neighbor));
    //         } else {
    //             node2->neighbors.push_back(it->second);
    //         }
    //     }
    //     return node2;
    // }

    /*
     * The tricky aspect is that the neighbors of a given node can be:
     * 1. an end node of itself (no more further neighbors)
     * 2. having one or more neighbors that form a cycle with previously visited nodes - directly, or indirectly
     * another fact to note is that: you don't have to worry if the root node given can "reach" all the other nodes in *any* graph
     * - you don't picture a cluster of nodes, and pick any random node, wishing it can reach all the nodes in the imaginary graph
     * the simple fact is: any node could be itself a root node, the graph starting from this node is all nodes it could reach following
     * the current neighbor relationship -
     * the basic thinking is: keep track of the visited nodes, for each cloned node, put the two matching nodes (source graph, and the cloned graph) into the mapping
     * if any node is visited, don't follow down the path (this is essentially a DFS);
     * for each neighbor of a node, clone is a recursive process, so the same clone function can be reused to traverse the graph in a DFS manner recursively
     * whenever the traversal meets a visited node on the original graph, the mapped node is returned and the DFS traveral for this branch should end;
     * recursion then handles the backtracking automatically
     */
    UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node)
    {
        if (node == nullptr) return nullptr;
        auto it = visited.find(node); // is the node already visited?
        if (it == visited.end()) {
            // the node has not been visited, need a full clone of it
            UndirectedGraphNode* node2 = new UndirectedGraphNode(node->label); // new cloned node with matching lable
            visited.emplace(node, node2); // keep track of the mapping
            for (auto* neighbor : node->neighbors) { // for all the neighbors of the node of the original graph
                node2->neighbors.push_back(cloneGraph(neighbor)); // add a corresponding node on the cloned graph (either another new node, or existing node)
            }
            return node2; // this is the node on the cloned node with all the properly cloned neighbors linked
        }
        return it->second; // the node is already visited on the original graph, return the mapped cloned node, and this branch is finished (DFS)
    }

private:
    // {nodeOfTheOriginalGraph: nodeOfTheClonedGraph}
    // this mapping answers the question: when we reach a visited node on the original graph, what is the corresponding node on the cloned graph!
    std::unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> visited;
};

#endif /* CloneGraph_h */

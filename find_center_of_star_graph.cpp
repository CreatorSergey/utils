#include <unordered_map>
#include <vector>

/*

Find Center of Star Graph

There is an undirected star graph consisting of n nodes labeled from 1 to n. A star graph is a graph where there is one center node and exactly n - 1 edges that connect the center node with every other node.

You are given a 2D integer array edges where each edges[i] = [ui, vi] indicates that there is an edge between the nodes ui and vi. Return the center of the given star graph.

Input: edges = [[1,2],[2,3],[4,2]]
Output: 2

Input: edges = [[1,2],[5,1],[1,3],[1,4]]
Output: 1

*/

class Solution 
{
public:
    int findCenter(vector<vector<int>>& edges) 
    {
        std::unordered_map<int, int> counter;
        for(const auto& edge: edges)
        {
            for(const auto& item: edge)
            {
                const auto value = ++counter[item];
                if(value == edges.size())
                    return item;
            }
        }
        return 0;
    }
};

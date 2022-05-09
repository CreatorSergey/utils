#include <queue>
#include <unordered_map>

/*
There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1 (inclusive). The edges in the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.

You want to determine if there is a valid path that exists from vertex source to vertex destination.

Given edges and the integers n, source, and destination, return true if there is a valid path from source to destination, or false otherwise.

Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
Output: true
Explanation: There are two paths from vertex 0 to vertex 2:
- 0 → 1 → 2
- 0 → 2

Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
Output: false
Explanation: There is no path from vertex 0 to vertex 5.

*/

class Solution 
{
public:
    bool validPath(int n, std::vector<std::vector<int>>& edges, int source, int destination) 
    {      
        // конвертирую в карту, для обращения по значениям, вместо индексов
        std::unordered_map<int, std::vector<int>> graph;
        for(const auto& edge: edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }        
        
        std::queue<int> q;
        q.push(source);
        
        std::vector<bool> used(n);
        used[source] = true;
        
        // поиск в ширину
        while(!q.empty())
        {
            int v = q.front();
            q.pop();
            
            for(std::size_t i = 0; i < graph[v].size(); ++i)
            {
                int to = graph[v][i];
                if(used[to] == false)
                {
                    used[to] = true;
                    q.push(to);
                }
            }
        }
        
        // Если вершину удалось посетить, значит путь есть
        return used[destination];
    }
};

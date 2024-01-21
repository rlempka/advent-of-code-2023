//
//  day25.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 1/20/24.
//

#include "day25.hpp"

void addUndirectedEdge(unordered_map<string, vector<string>>& adjList, string& v1, string& v2)
{
    adjList[v1].push_back(v2);
    adjList[v2].push_back(v1);

}

void addUndirectedEdgeSet(unordered_map<string, set<string>>& adjList, string& v1, string& v2)
{
    adjList[v1].insert(v2);
    adjList[v2].insert(v1);
}

void removeUndirectedEdge(unordered_map<string, vector<string>>& adjList, string& v1, string& v2)
{
    auto it1 = find(adjList[v1].begin(), adjList[v1].end(), v2);
    
    if (it1 != adjList[v1].end())
    {
        size_t index = distance(adjList[v1].begin(), it1);
        adjList[v1].erase(adjList[v1].begin() + index);
    }
    
    if (adjList[v1].size() == 0)
        adjList.erase(v1);
    
    auto it2 = find(adjList[v2].begin(), adjList[v2].end(), v1);
    
    if (it2 != adjList[v2].end())
    {
        size_t index = distance(adjList[v2].begin(), it2);
        adjList[v2].erase(adjList[v2].begin() + index);
    }
    
    if (adjList[v2].size() == 0)
        adjList.erase(v2);
}

void addDirectedEdge(unordered_map<string, vector<string>>& adjList, string& v1, string& v2)
{
    adjList[v1].push_back(v2);
}

void printGraph(unordered_map<string, vector<string>>& adjList)
{
    for (const auto& u : adjList)
    {
        cout << "u: " << u.first;
        cout << " list: ";
        for (const auto& v : adjList[u.first])
        {
            cout << v << " ";
        }
        cout << '\n';
    }
}

int setDiffCount(set<string>& s1, set<string>& s2)
{
    set<string> result { };
    
    set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(result, result.begin()));
    
    return static_cast<int>(result.size());
}

// Solution from: https://www.reddit.com/r/adventofcode/comments/18qbsxs/comment/ketzp94/?utm_source=share&utm_medium=web2x&context=3
// Adapted for C++

// The brute force solution is also in this file: graphPartitionGroupSizeProductPart1()
long long graphPartitionGroupSizeProductPart1Simple()
{
    unordered_map<string, set<string>> adjList { };
    ifstream componentConnections("./day-25/day25input.txt");
    
    string componentMap;
    
    while(getline(componentConnections, componentMap))
    {
        
        istringstream iss(componentMap);
        
        string first;
        string next;

        iss >> first;
        first = first.substr(0, first.size() - 1);
        
        while(iss >> next)
        {
            addUndirectedEdgeSet(adjList, first, next);
        }
    }
    
    set<string> S;
    
    for (const auto& v : adjList)
    {
        for (const auto& u : adjList[v.first])
        {
            S.insert(u);
        }
    }
    
    long long numNodes { static_cast<long long>(S.size()) };
    
    auto count = [&S, &adjList](const string& v)
    {
        int externalNeighbors = 0;
        
        for (const auto& neighbor: adjList[v])
        {
            if (S.find(neighbor) == S.end())
            {
                externalNeighbors++;
            }
        }
        return externalNeighbors;
    };
    
    while (accumulate(S.begin(), S.end(), 0, [&](int acc, const string& v) {
            return acc + count(v);
        }) != 3) {
            // Remove node with maximum count
            auto maxIt = max_element(S.begin(), S.end(), [&](const string& a, const string& b) {
                return count(a) < count(b);
            });
            S.erase(maxIt);
    }
    
    
    
    return S.size() * (numNodes - S.size());

}

long long graphPartitionGroupSizeProductPart1()
{
    unordered_map<string, vector<string>> adjList { };
    
    ifstream componentConnections("./day-25/day25input.txt");
    
    set<set<string>> edges { };
    
    string componentMap;

    while(getline(componentConnections, componentMap))
    {
        istringstream iss(componentMap);
        
        string entryPoint;
        string connection;
        
        iss >> entryPoint;
        entryPoint = entryPoint.substr(0, entryPoint.size() - 1);
        
        while(iss >> connection)
        {
            addUndirectedEdge(adjList, entryPoint, connection);
        }
    }
    
    // printGraph(adjList);
    
    for (const auto& u : adjList)
    {
        for (const auto& v : adjList[u.first])
        {
            edges.insert({u.first, v});
        }
    }
    
    /*
    for (const auto& edgeSet : edges) {
           for (const auto& element : edgeSet) {
               std::cout << element << " ";
           }
           std::cout << std::endl;
    }
    */
    
    long long numNodes = adjList.size();
    long long visitCount { 0 };
    std::vector<set<string>> combination;
    int k = 3;

    for (auto it1 = edges.begin(); it1 != std::prev(edges.end(), k - 1); ++it1) {
        combination.push_back(*it1);
        
        for (auto it2 = std::next(it1); it2 != std::prev(edges.end(), k - 2); ++it2) {
            combination.push_back(*it2);

            for (auto it3 = std::next(it2); it3 != edges.end(); ++it3) {
                combination.push_back(*it3);

                // Process or print the combination
                for (auto& comb : combination) {
                    auto it = comb.begin();
                    string v1 = *it;
                    ++it;
                    string v2 = *it;
                    removeUndirectedEdge(adjList, v1, v2);
                }
                
                    
                set<string> visited { };
                visitCount = 0;
                
                auto itAdj = adjList.begin();
                                
                dfs(itAdj->first, visited, adjList, visitCount);
                
                if (visitCount < numNodes)
                {
                    cout << "Total nodes: " << numNodes << '\n';
                    cout << "Visited nodes: " << visitCount << '\n';
                    cout << "Not visited nodes: " << numNodes - visitCount << '\n';
                    goto endLoop;
                }
                
                for (auto& comb : combination) {
                    auto it = comb.begin();
                    string v1 = *it;
                    ++it;
                    string v2 = *it;
                    addUndirectedEdge(adjList, v1, v2);
                }
                
                combination.pop_back();
            }

            combination.pop_back();
        }

        combination.pop_back();
    }
    
    endLoop:
    return visitCount * (numNodes - visitCount);
}


void dfs(const string& vertex, set<string>& visited, unordered_map<string, vector<string>> adjList, long long& visitCount)
{
    visited.insert(vertex);
    visitCount++;
    
    for (const string& neigbhor : adjList[vertex])
    {
        if (visited.find(neigbhor) == visited.end())
        {
            dfs(neigbhor, visited, adjList, visitCount);
        }
    }
    
}

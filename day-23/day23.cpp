//
//  day23.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 1/13/24.
//

#include "day23.hpp"
#include "../helpers/file-helpers.hpp"

#define F first
#define S second

ll longestHikePart1()
{

    vector<string> hikingTrails { convertFileToLines("./day-23/day23input.txt")};
    
    unordered_map<char, pair<int,int>> slopeDirs {
        {'>', {0, 1}},
        {'<', {0, -1}},
        {'^', {-1, 0}},
        {'v', {1, 0}}
    };
    
    set<pair<int, int>> visited { };
    
    int m { static_cast<int>(hikingTrails.size()) };
    int n { static_cast<int>(hikingTrails[0].size()) };
    
    cout << m - 1 << " " << n - 2 << '\n';
    
    return dfsLongestHike(0, 1, m - 1, n - 2, visited, hikingTrails, slopeDirs, m, n);
    
}

// Start at (i, j) and update (i, j)
// Destination is (k, l)
ll dfsLongestHike(int i, int j, int k, int l, set<pair<int,int>>& visited, vector<string>& hikingTrails, unordered_map<char, pair<int,int>>& slopeDirs, int m, int n)
{
    
    if (i < 0 || i >= m || j < 0 || j >= n || hikingTrails[i][j] == '#' ||
        visited.find({ i, j }) != visited.end())
    {
        return 0;
    }
    
    if (i == k && j == l)
    {
        
        return 0;
    }
    
    visited.insert({i, j});
        
    ll up { 0 }, down { 0 }, left { 0 }, right { 0 }, slopeDir { 0 };
    
    if (hikingTrails[i][j] == '.')
    {
        int diUp { i - 1 };
        int diDown { i + 1 };
        int djLeft { j - 1 };
        int djRight { j + 1 };
        
        if (diUp >= 0 && visited.find({diUp, j}) == visited.end())
        {
            up = 1 + dfsLongestHike(diUp, j, k, l, visited, hikingTrails, slopeDirs, m, n);
        }
        
        if (diDown < m && visited.find({diDown, j}) == visited.end())
        {
            down = 1 + dfsLongestHike(diDown, j, k, l, visited, hikingTrails, slopeDirs, m, n);
        }
        
        if (djLeft >= 0 && visited.find({i, djLeft}) == visited.end())
        {
            left = 1 + dfsLongestHike(i, djLeft, k, l, visited, hikingTrails, slopeDirs, m, n);
        }
        
        if (djRight < n && visited.find({i, djRight}) == visited.end())
        {
            right = 1 + dfsLongestHike(i, djRight, k, l, visited, hikingTrails, slopeDirs, m, n);
        }
    }

    if (hikingTrails[i][j] == '<' || hikingTrails[i][j] == '>' || hikingTrails[i][j] == '^' || hikingTrails[i][j] == 'v')
    {
        int di { slopeDirs[hikingTrails[i][j]].F };
        int dj { slopeDirs[hikingTrails[i][j]].S };
        
        slopeDir = 1 + dfsLongestHike(i + di, j + dj, k, l, visited, hikingTrails, slopeDirs, m, n);
    }
    
    visited.erase({ i, j });
    
    return max(slopeDir, max(down, max(up, max(left, right))));
}

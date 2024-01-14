//
//  day23.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 1/13/24.
//

#ifndef day23_hpp
#define day23_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <unordered_map>
#include <map>
#include <queue>
#include <numeric>
#include <regex>
#include <list>
#include <algorithm>
#include <iomanip>

typedef long long ll;
using namespace std;

ll longestHikePart1();
ll dfsLongestHike(int i, int j, int k, int l, set<pair<int,int>>& visited, vector<string>& hikingTrails, unordered_map<char, pair<int,int>>& slopeDirs, int m, int n);

#endif /* day23_hpp */

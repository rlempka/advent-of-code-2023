//
//  day25.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 1/20/24.
//

#ifndef day25_hpp
#define day25_hpp

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

using namespace std;

long long graphPartitionGroupSizeProductPart1();
long long graphPartitionGroupSizeProductPart1Simple();
void dfs(const string& vertex, set<string>& visited, unordered_map<string, vector<string>> adjList, long long& visitCount);

#endif /* day25_hpp */

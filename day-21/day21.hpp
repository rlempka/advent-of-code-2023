//
//  day21.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 1/4/24.
//

#ifndef day21_hpp
#define day21_hpp

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

using namespace std;
typedef long long ll;

long long gardenPlotsReachable64StepsPart1();
void BFSGardenShortestPaths(vector<string>& elfMap, vector<vector<ll>>& shortestPaths, pair<int, int> startPos, vector<vector<bool>>& visited);
void BFSGardenShortestPathsInfinite(vector<string>& elfMap, map<pair<ll,ll>, ll>& shortestPaths, pair<int, int> startPos, set<pair<ll, ll>>& visited, ll availableSteps);
long long gardenPlotsReachableInfinitePart2();
long long gardenPlotsReachableOddEven(map<pair<ll, ll>, ll>& shortestPaths, set<pair<ll, ll>>& visited,
                                      vector<string>& elfMap, bool even);
#endif /* day21_hpp */

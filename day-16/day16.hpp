//
//  day16.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/16/23.
//

#ifndef day16_hpp
#define day16_hpp

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

long long energizedTileCountPart1();
bool beamTypeSeenAtPos(std::map<std::pair<int, int>, std::vector<char>>& visitedWithBeamType, int i, int j, char beam);
void dfsContraption(std::vector<std::string>& contraption, long long& energizedTileCount,
                    std::map<std::pair<int, int>, std::vector<char>>& visitedWithBeamType, char beam,
                    int i, int j);
long long energizedTileCountPart2();

#endif /* day16_hpp */

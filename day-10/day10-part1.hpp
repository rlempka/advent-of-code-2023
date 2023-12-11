//
//  day10-part1.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/10/23.
//

#ifndef day10_part1_hpp
#define day10_part1_hpp

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

int stepsFarthestFromStart();

int dfsCycleLength(std::pair<int, int> sNode, std::pair<int, int> parent, std::pair<int, int> currNode,
                   std::vector<std::string>& lines,
                   std::set<std::pair<int, int>>& visited,
                   std::map<char, std::map<std::string, std::set<char>>>& validNextStep,
                   std::map<std::string, std::pair<int, int>>& directionMap);

#endif /* day10_part1_hpp */

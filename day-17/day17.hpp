//
//  day17.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/17/23.
//

#ifndef day17_hpp
#define day17_hpp

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

int leastHeatLoss();
int dijsktraBFSConstrained(const std::vector<std::string>& grid,
                                                     std::pair<int, int> start,
                           std::pair<int, int> end);
int dijsktraBFSConstrainedPart2(const std::vector<std::string>& grid,
                                                     std::pair<int, int> start,
                           std::pair<int, int> end);
int leastHeatLossPart2();


#endif /* day17_hpp */

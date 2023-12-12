//
//  day11-part2.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/11/23.
//

#ifndef day11_part2_hpp
#define day11_part2_hpp

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

long long sumOfShortestPathLengthsPart2();
long long countRowsBetween(std::vector<int>& emptyRows, std::pair<int, int> source, std::pair<int, int> dest);
long long countColsBetween(std::vector<int>& emptyCols, std::pair<int, int> source, std::pair<int, int> dest);

#endif /* day11_part2_hpp */

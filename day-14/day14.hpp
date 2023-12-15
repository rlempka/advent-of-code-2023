//
//  day14.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/14/23.
//

#ifndef day14_hpp
#define day14_hpp

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

void rotateMatrix90DegreesClockwise(std::vector<std::string>& platform);
long long totalLoadPart1();
void northTilt(std::vector<std::string>& platform);
long long totalLoadPart2();
std::vector<int> countRocksPerRow(std::vector<std::string>& platform);

#endif /* day14_hpp */

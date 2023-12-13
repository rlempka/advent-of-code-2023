//
//  day13.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/13/23.
//

#ifndef day13_hpp
#define day13_hpp

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

long long day13Part1();
long long day13Part2();
std::vector<std::vector<std::string>> processInput();
int getHorizontalReflectionPoint(std::vector<std::string>& pattern);
std::vector<std::string> transposeMatrix(const std::vector<std::string>& matrix);

#endif /* day13_hpp */

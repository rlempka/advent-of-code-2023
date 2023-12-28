//
//  day18.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/19/23.
//

#ifndef day18_hpp
#define day18_hpp

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

long long cubicMetersLavaPart1();
long long cubicMetersLavaPart2();
std::string getDirection(int dirNumber);
void digBorder(std::vector<std::string>& ground, std::vector<std::string>& digPlan, int startRow, int startCol);
int rayCastNorth(int row, int col, std::vector<std::string>& ground);
long long getArea(std::vector<std::pair<long long, long long>> latticeCoords);

#endif /* day18_hpp */

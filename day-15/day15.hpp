//
//  day15.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/16/23.
//

#ifndef day15_hpp
#define day15_hpp

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

long long day15Part1();
long long day15Part2();
std::vector<std::string> splitString(std::string& input, char delimiter);
int hashAlgo(const std::string& stringToHash);
long long hashInputSeqSum(const std::vector<std::string>& inputSeq);
void processStep(std::vector<std::list<std::pair<std::string, int>>>& hashTable, std::string& step);

#endif /* day15_hpp */

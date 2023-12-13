//
//  day12-part2.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/13/23.
//

#ifndef day12_part2_hpp
#define day12_part2_hpp

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
#include <tuple>


long long numArrangements(std::vector<char>& seq, std::vector<int>& groups, int groupSize, int seqIdx, int groupIdx,
                          std::unordered_map<std::string, long long>& memo);
long long numberOfArrangementsPart2();
std::string createMemoKey(std::vector<char>& seq, std::vector<int>& groups, int seqIdx, int groupIdx, int groupSize);

#endif /* day12_part2_hpp */

//
//  day12-part1.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/12/23.
//

#ifndef day12_part1_hpp
#define day12_part1_hpp

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


long long numberOfArrangements();
void backtrackArrangements(std::vector<char>& seq, std::vector<int>& consecList, int seqIdx, std::vector<char>& newSeq, long long& validSeqCount);
bool validSeq(std::vector<char>& seqToCheck, std::vector<int> consecCounts);
#endif /* day12_part1_hpp */

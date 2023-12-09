//
//  day7-part1.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/7/23.
//

#ifndef day7_part1_hpp
#define day7_part1_hpp

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


struct CompareCounts {
    bool operator()(const std::pair<char, long>& p1, const std::pair<char, long>& p2) const {
        return p1.second < p2.second;
    }
};

long totalWinnings();

std::vector<std::string> convertFileToLines(std::string fileLoc);

#endif /* day7_part1_hpp */

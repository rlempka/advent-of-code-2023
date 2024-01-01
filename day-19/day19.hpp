//
//  day19.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/29/23.
//

#ifndef day19_hpp
#define day19_hpp

#include <stdio.h>
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

long long sumOfAcceptedPartRatings();
std::string processPart(std::unordered_map<std::string, long long>& partMap, std::unordered_map<std::string, std::vector<std::string>>& workflowMap);
void dfsWorkflows(std::string node, std::vector<std::string>& currBounds, std::vector<std::vector<std::string>>& acceptedBounds, std::unordered_map<std::string, std::vector<std::string>>& workflowMap);
long long numberOfCombinationsPart2();


#endif /* day19_hpp */

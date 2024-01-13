//
//  day22.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 1/11/24.
//

#ifndef day22_hpp
#define day22_hpp

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
#include <algorithm>
#include <iomanip>

using namespace std;
typedef long long ll;

struct LabeledPoint;
struct CompareBySecondZ;
struct CompareBySecondZMaxHeap;
bool compareByFirstZ(const pair<LabeledPoint, LabeledPoint>& a, const pair<LabeledPoint, LabeledPoint>& b);
long long safeToDisintegrateBrickCount();
ll sumOfBricksThatWouldFallPart2();

#endif /* day22_hpp */

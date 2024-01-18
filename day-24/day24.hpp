//
//  day23.hpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 1/15/24.
//

#ifndef day24_hpp
#define day24_hpp

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
#include <Eigen/Dense>
#include <Eigen/Core>


typedef long long ll;

using namespace std;

struct Point;
ll numIntersectionsTestAreaPart1();
Point rayIntersectingRay(Point p, Point r, Point q, Point s);
ll xyzSumMagicRockInitialPositionPart2();
Eigen::Matrix3d crossMatrix(Eigen::Vector3d v);

#endif /* day24_hpp */

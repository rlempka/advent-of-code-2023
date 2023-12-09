//
//  day6-part1.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/6/23.
//

#include "day6-part1.hpp"

long getValidSolutionCount(long time, long distance)
{
    long validSols { 0 };
    
    for (long x { 1 }; x < time; ++x)
    {
        
        if (((time * x) - (x * x)) > distance)
        {
            validSols++;
        }
        
    }
    
    return validSols;
}


long multiplyValidSolutions()
{
    // int solutionProduct { 1 };
    
    std::vector<std::pair<int, int>> testPairs {
        { 7, 9 },
        { 15, 40 },
        { 30, 200 }
    };
    
    std::vector<std::pair<int, int>> timeDistPairs {
        { 47, 282 },
        { 70, 1079 },
        { 75, 1147 },
        { 66, 1062 }
    };
    
    /*
    std::vector<std::pair<int, int>> finalTimeDistPair {
        { 47 70 75 66, 282 1079 1147 1062 }
    };
     */
    
    
    /*
    for (const auto& p : finalTimeDistPair)
    {
        solutionProduct *= getValidSolutionCount(p.first, p.second);
    }
    */
    
    return getValidSolutionCount(47707566, 282107911471062);
}

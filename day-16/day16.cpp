//
//  day16.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/16/23.
//

#include "day16.hpp"
#include "../helpers/file-helpers.hpp"

long long energizedTileCountPart1()
{
    std::vector<std::string> contraption { convertFileToLines("./day-16/day16input.txt") };
    
    
    // Valid beam types are '<' '>' '^' and 'v'
    // The key indicates the (i, j) position on the contraption
    std::map<std::pair<int, int>, std::vector<char>> visitedWithBeamType { };
    
    long long energizedTileCount { 0 };
    
    dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '>', 0, 0);
    visitedWithBeamType.clear();

    return energizedTileCount;
}

long long energizedTileCountPart2()
{
    std::vector<std::string> contraption { convertFileToLines("./day-16/day16input.txt") };
    
    
    // Valid beam types are '<' '>' '^' and 'v'
    // The key indicates the (i, j) position on the contraption
    std::map<std::pair<int, int>, std::vector<char>> visitedWithBeamType { };
    
    long long energizedTileCountCurrMax { 0 };
    long long energizedTileCount { 0 };
        
    // Iterate over top row
    for (int i { 0 }; i < contraption[0].size(); ++i)
    {
        energizedTileCount = 0;
        dfsContraption(contraption, energizedTileCount, visitedWithBeamType, 'v', 0, i);
        energizedTileCountCurrMax = std::max(energizedTileCountCurrMax, energizedTileCount);
        visitedWithBeamType.clear();
    }
    
    // Iterate over bottom row
    for (int i { 0 }; i < contraption[0].size(); ++i)
    {
        energizedTileCount = 0;
        dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '^', static_cast<int>(contraption.size()) - 1, i);
        energizedTileCountCurrMax = std::max(energizedTileCountCurrMax, energizedTileCount);
        visitedWithBeamType.clear();
    }
    
    // Iterate over left column
    for (int j { 0 }; j < contraption.size(); ++j)
    {
        energizedTileCount = 0;
        dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '>', j, 0);
        energizedTileCountCurrMax = std::max(energizedTileCountCurrMax, energizedTileCount);
        visitedWithBeamType.clear();
    }
    
    // Iterate over right column
    for (int j { 0 }; j < contraption.size(); ++j)
    {
        energizedTileCount = 0;
        dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '<', j, static_cast<int>(contraption.size()) - 1);
        energizedTileCountCurrMax = std::max(energizedTileCountCurrMax, energizedTileCount);
        visitedWithBeamType.clear();
    }

    return energizedTileCountCurrMax;
}

bool beamTypeSeenAtPos(std::map<std::pair<int, int>, std::vector<char>>& visitedWithBeamType, int i, int j, char beam)
{
    for (auto& c : visitedWithBeamType[{i, j}])
    {
        if (beam == c)
        {
            return true;
        }
    }
    
    return false;
}


void dfsContraption(std::vector<std::string>& contraption, long long& energizedTileCount,
                    std::map<std::pair<int, int>, std::vector<char>>& visitedWithBeamType, char beam,
                    int i, int j)
{
    if (i < 0 || i >= contraption.size() || j < 0 || j >= contraption[0].size()
           || (visitedWithBeamType.find({i, j}) != visitedWithBeamType.end() && beamTypeSeenAtPos(visitedWithBeamType, i, j, beam)))

    {
        return;
    }
    
    char currPos = contraption[i][j];
    visitedWithBeamType[{i,j}].push_back(beam);
    
    if (visitedWithBeamType[{i,j}].size() == 1)
    {
        energizedTileCount++;
    }

    if (beam == '>')
    {

        if (currPos == '.' || currPos == '-')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '>', i, j+1);
        }
        else if (currPos == '/')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '^', i - 1, j);
        }
        else if (currPos == '\\')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, 'v', i + 1, j);
        }
        else if (currPos == '|')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '^', i - 1, j);
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, 'v', i + 1, j);
        }
    }
    else if (beam == '<')
    {
        if (currPos == '.' || currPos == '-')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '<', i, j - 1);
        }
        else if (currPos == '/')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, 'v', i + 1, j);
        }
        else if (currPos == '\\')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '^', i - 1, j);
        }
        else if (currPos == '|')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '^', i - 1, j);
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, 'v', i + 1, j);
        }
        
    }
    else if (beam == '^')
    {
        if (currPos == '.' || currPos == '|')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '^', i - 1, j);
        }
        else if (currPos == '/')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '>', i, j + 1);
        }
        else if (currPos == '\\')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '<', i, j - 1);
        }
        else if (currPos == '-')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '>', i, j + 1);
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '<', i, j - 1);
        }
    }
    else if (beam == 'v')
    {
        if (currPos == '.' || currPos == '|')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, 'v', i + 1, j);
        }
        else if (currPos == '/')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '<', i, j - 1);
        }
        else if (currPos == '\\')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '>', i, j + 1);
        }
        else if (currPos == '-')
        {
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '>', i, j + 1);
            dfsContraption(contraption, energizedTileCount, visitedWithBeamType, '<', i, j - 1);
        }
    }
    
}

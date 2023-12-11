//
//  day10-part1.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/10/23.
//

#include "day10-part1.hpp"
#include "../helpers/file-helpers.hpp"


int stepsFarthestFromStart()
{
    
    std::vector<std::string> lines { convertFileToLines("./day-10/day10input.txt") };
    std::pair<int, int> sPos { };
    
    for (int i { 0 }; i < lines.size(); ++i)
    {
        for (int j { 0 }; j < lines[i].size(); ++j)
        {
            if (lines[i][j] == 'S')
            {
                sPos = { i, j };
                break;
            }
        }
    }
    
    std::cout << sPos.first << " " << sPos.second << '\n';
    
    
    std::map<std::string, std::set<char>> validFirstSteps {
        {"up" , { '|', '7', 'F' }},
        {"down", { '|', 'J', 'L' }},
        {"left", { 'L', 'F', '-' }},
        {"right", { 'J', '7', '-' }}
    };
    
    // X indicates no valid moves from that pipe in that direction
    std::map<char, std::map<std::string, std::set<char>>> validNextStep {
        { '|', {{"up" , { '|', '7', 'F', 'S' }},
                {"down", { '|', 'J', 'L', 'S' }},
                {"left", { 'X' }},
                {"right", { 'X' }}}
        },
        { '-', {{"up" , { 'X' }},
                {"down", { 'X' }},
                {"left", { 'L', 'F', '-', 'S' }},
                {"right", { '7', 'J', '-', 'S' }}}
        },
        { '7', {{"up" , { 'X' }},
                {"down", { '|', 'L', 'J', 'S' }},
                {"left", { '-', 'L', 'F', 'S' }},
                {"right", { 'X' }}}
        },
        { 'L', {{"up" , { '|', '7', 'F', 'S' }},
                {"down", { 'X' }},
                {"left", { 'X' }},
                {"right", { '-', '7', 'J', 'S' }}}
        },
        { 'J', {{"up" , { '|', '7', 'F', 'S' }},
                {"down", { 'X' }},
                {"left", { '-', 'L', 'F', 'S' }},
                {"right", { 'X' }}}
        },
        { 'F', {{"up" , { 'X' }},
                {"down", { '|', 'J', 'L', 'S' }},
                {"left", { 'X' }},
                {"right", { '-', 'J', '7', 'S' }}}
        }
      };
    
    std::map<std::string, std::pair<int, int>> directionMap
    {
        { "up", {-1, 0} },
        { "down", {1, 0 } },
        { "left", {0, -1} },
        { "right", {0, 1 } }
    };

    std::set<std::pair<int, int>> visited { };
    
    // {35, 17} sPos start
    // start on a different node {36, 17}
    int cycleLength = dfsCycleLength(sPos, sPos, {36, 17}, lines, visited, validNextStep, directionMap);

    
    return cycleLength / 2;
    
}


int dfsCycleLength(std::pair<int, int> sNode, std::pair<int, int> parent, std::pair<int, int> currNode,
                   std::vector<std::string>& lines,
                   std::set<std::pair<int, int>>& visited,
                   std::map<char, std::map<std::string, std::set<char>>>& validNextStep,
                   std::map<std::string, std::pair<int, int>>& directionMap)
{
    if (currNode == sNode && sNode != parent)
    {
        return 1;
    }
    
    if (visited.find(currNode) != visited.end())
    {
        return 0;
    }
    
    visited.insert(currNode);
    
    int parI { parent.first };
    int parJ { parent.second };
    
    parent = currNode;
    

    int currI {currNode.first };
    int currJ {currNode.second };
        
    char currNodeSymbol = lines[currI][currJ];
        
    std::map<std::string, std::set<char>> nextSteps = validNextStep[currNodeSymbol];
    
    for (auto& dir : { "up", "down", "left", "right" })
    {
        
        int stepI { directionMap[dir].first };
        int stepJ { directionMap[dir].second };
        
        int nextI { currI + stepI };
        int nextJ { currJ + stepJ };
        
        if (nextI >= 0 && nextI < lines.size() && nextJ >= 0 && nextJ < lines[0].size() &&
            nextSteps[dir].find(lines[nextI][nextJ]) != nextSteps[dir].end() && (!(nextI == parI && nextJ == parJ)))
        {
            
            currNode = { nextI, nextJ };
            
            /*
            std::cout << '\n';
            std::cout << "curr symbol: " << lines[currI][currJ] << " currI: " << currI << " currJ: " << currJ;
            std::cout << '\n';
            std::cout << "next symbol: " << lines[nextI][nextJ] << " nextI: " << nextI << " nextJ: " << nextJ;
            std::cout << '\n';
            std::cout << '\n';
            std::cout << '\n';
             */
            
            break;
        }
    }
        
    
    return 1 + dfsCycleLength(sNode, parent, currNode, lines, visited, validNextStep, directionMap);
}

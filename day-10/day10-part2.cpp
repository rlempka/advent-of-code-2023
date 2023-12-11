//
//  day10-part2.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/11/23.
//

#include "day10-part2.hpp"
#include "day10-part1.hpp"
#include "../helpers/file-helpers.hpp"


int tilesEnclosedByCycle()
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
    // This is 1 row below S, we are starting off of S
    int cycleLength = dfsCycleLength(sPos, sPos, {sPos.first + 1, sPos.second}, lines, visited, validNextStep, directionMap);
    
    /*
    for (auto & p : visited)
    {
        std::cout << p.first << " " << p.second << '\n';
    }
    */
    
    // Need to correctly set the inferred value of starting position symbol
    lines[sPos.first][sPos.second] = '|';
    //Due to the way the dfsCycleLength() runs, sPos never gets visited so need to insert into visited
    visited.insert(sPos);
    
    // The logic below is that for any tile outside of the loop, it will cross the boundry of the loop
    // and even number of times
    
    // Only 1 direction is needed to be checked, and if it is found that the point in the grid crosses
    // an odd number of times, then that point is within the cycle
    
    // We only move vertically from each point, an L followed by a F is considered 2 overlaps, as is
    // a J followed by a 7, but when the following symbol is opposite (e.g. L followed by a 7), this is considerd
    // a single overlap as these 2 tiles offset eachother, so it's as if the line being crossed is still vertical '|'
    int enclosedTileCount { 0 };
    
    for (int i { 0 }; i < lines.size(); ++i)
    {
        for (int j { 0 }; j < lines[0].size(); ++j)
        {
            if (visited.find({ i, j }) == visited.end())
            {
                int row { i };
                int overLapCount { 0 };
                                
                char lastVisited { '.' };
                
                do
                {
                    --row;
                                        
                    if (visited.find({row, j}) != visited.end() && lines[row][j] != '|')
                    {
                        

                        if (lines[row][j] == '-' || lines[row][j] == 'L' || lines[row][j] == 'J')
                        {
                            overLapCount += 1;
                        }
                        else if ((lines[row][j] == 'F' && lastVisited == 'L')
                                 || (lines[row][j] == '7' && lastVisited == 'J'))
                        {
                            overLapCount += 1;
                        }
                        
                        lastVisited = lines[row][j];
                        
                    }
                    
                    
                } while (row >= 0);
                
                if (overLapCount % 2 == 1)
                {
                    enclosedTileCount += 1;
                }
                
            }
            

        }
    }
    
    return enclosedTileCount;
}


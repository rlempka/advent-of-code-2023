//
//  day11-part2.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/11/23.
//

#include "day11-part1.hpp"
#include "day11-part2.hpp"
#include "../helpers/file-helpers.hpp"


long long sumOfShortestPathLengthsPart2()
{
    std::vector<std::string> lines { convertFileToLines("./day-11/day11input.txt") };
        
    // int colLength { static_cast<int>(lines.size()) };
    
    std::vector<int> emptyColIndexes { };
    std::vector<int> emptyRowIndexes { };
    
    bool emptyCol { true };
    bool emptyRow { true };

    
    for (int j { 0 }; j < lines[0].size(); ++j)
    {
        for (int i { 0 }; i < lines.size(); ++i)
        {
            
            if (lines[i][j] == '#')
            {
                emptyCol = false;
                break;
            }
        }
        
        if (emptyCol)
        {
            emptyColIndexes.push_back(j);
        }
        
        emptyCol = true;
    }
    
    for (int i { 0 }; i < lines.size(); ++i)
    {
        for (int j { 0 }; j < lines.size(); ++j)
        {
            
            if (lines[i][j] == '#')
            {
                emptyRow = false;
                break;
            }
        }
        
        if (emptyRow)
        {
            emptyRowIndexes.push_back(i);
        }
        
        emptyRow = true;
    }
    
   
    // Get the x,y coordinates for all of the '#' characters (galaxy positions)
    
    std::vector<std::pair<int, int>> galaxyPoints { };
    
    for (int i { 0 }; i < lines.size(); ++i)
    {
        for (int j { 0 }; j < lines[0].size(); ++j)
        {
            if (lines[i][j] == '#')
            {
                galaxyPoints.push_back({i , j });
            }
            
        }
    }
    
    // In part 2 the code has been adjusted based on the observation that by counting the number of empty rows/cols
    // between the source and dest, it can be mathemtically determmined what the shortest path will be
    
    // The manhattan distance is used to calculate the original distance in the non-expanded graph
    // and then for each column / row added between source and dest the distance increases by 1.
    // Total number of columns and rows added per empty row will be the multiplier given (for instance 2)
    // minus 1 multiplied by the number of columns or rows. 1 is subtracted since you don't count the original row/col.
    
    int multiplier { 1000000 };
    long long sumBetweenGalaxies { 0 };
    
    for (int i { 0 }; i < galaxyPoints.size(); ++i)
    {
        for (int j { i + 1}; j < galaxyPoints.size(); ++j)
        {
            long long dist = (manhattanDistance(galaxyPoints[i], galaxyPoints[j])
                                   + (countRowsBetween(emptyRowIndexes, galaxyPoints[i], galaxyPoints[j]) * (multiplier - 1))
                                   + (countColsBetween(emptyColIndexes, galaxyPoints[i], galaxyPoints[j]) * (multiplier - 1)));
            
            /*
            std::cout << "Source: " << galaxyPoints[i].first << " " << galaxyPoints[i].second << '\n';
            std::cout << "Dest: " << galaxyPoints[j].first << " " << galaxyPoints[j].second << '\n';
            std::cout << "Dist: " << dist;
            std::cout << '\n';
             */

            
            sumBetweenGalaxies += dist;
        }
    }
    
    return sumBetweenGalaxies;
    
    
    return 0;
}

long long countRowsBetween(std::vector<int>& emptyRows, std::pair<int, int> source, std::pair<int, int> dest)
{
    int rowCount { 0 };
    
    for (auto& index : emptyRows)
    {
        if ((source.first < dest.first) && index >= source.first && index <= dest.first)
        {
            rowCount += 1;
        }
        else if ((source.first > dest.first) && index <= source.first && index >= dest.first)
        {
            rowCount += 1;
        }
        
    }
    
    return rowCount;
}

long long countColsBetween(std::vector<int>& emptyCols, std::pair<int, int> source, std::pair<int, int> dest)
{
    int colCount { 0 };
    
    for (auto& index : emptyCols)
    {
        if ((source.second < dest.second) && index >= source.second && index <= dest.second)
        {
            colCount += 1;
        }
        else if ((source.second > dest.second) && index <= source.second && index >= dest.second)
        {
            colCount += 1;
        }
    }
    
    return colCount;
}

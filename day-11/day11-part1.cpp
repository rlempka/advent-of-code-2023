//
//  day11-part1.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/11/23.
//

#include "day11-part1.hpp"
#include "../helpers/file-helpers.hpp"

long long sumOfShortestPathLengths()
{
    
    std::vector<std::string> lines { convertFileToLines("./day-11/day11input.txt") };
        
    // int colLength { static_cast<int>(lines.size()) };
    
    std::set<int> emptyColIndexes { };
    std::set<int> emptyRowIndexes { };
    
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
            emptyColIndexes.insert(j);
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
            emptyRowIndexes.insert(i);
        }
        
        emptyRow = true;
    }
    
    int rowLength { static_cast<int>(emptyColIndexes.size()) +
                    static_cast<int>(lines[0].size())
    };
    
    int colLength {
        static_cast<int>(emptyRowIndexes.size()) +
        static_cast<int>(lines.size())
    };
    
    std::vector<char> dummyRow(rowLength, '.');
    std::vector<std::vector<char>> universe(colLength, std::vector<char>(rowLength));
        
    // Create the final "universe" input
    int colOffset { 0 };
    int rowOffset { 0 };
    for (int i { 0 }; i < lines.size(); ++i)
    {
        for (int j { 0 }; j < lines[0].size(); ++j)
        {
            universe[i + rowOffset][j + colOffset] = lines[i][j];
            if (emptyColIndexes.find(j) != emptyColIndexes.end())
            {
                
                colOffset += 1;
                universe[i + rowOffset][j + colOffset] = '.';
            }
            
        }
        
        if (emptyRowIndexes.find(i) != emptyRowIndexes.end())
        {
            rowOffset += 1;
            for (int k { 0 }; k < rowLength; ++k)
            {
                universe[i + rowOffset][k] = '.';
            }
        }
        
        colOffset = 0;
        
    }
    
    /*
    for (const auto& row : universe) {
           for (char element : row) {
               std::cout << element << ' ';
           }
        std::cout << '\n';

       }
    std::cout << '\n';
    std::cout << '\n';
    std::cout << '\n';
    */
    
    // Get the x,y coordinates for all of the '#' characters (galaxy positions)
    
    std::vector<std::pair<int, int>> galaxyPoints { };
    
    for (int i { 0 }; i < universe.size(); ++i)
    {
        for (int j { 0 }; j < universe[0].size(); ++j)
        {
            if (universe[i][j] == '#')
            {
                galaxyPoints.push_back({i , j });
            }
            
        }
    }
    
    long long sumBetweenGalaxies { 0 };
    
    for (int i { 0 }; i < galaxyPoints.size(); ++i)
    {
        for (int j { i + 1}; j < galaxyPoints.size(); ++j)
        {
            sumBetweenGalaxies += manhattanDistance(galaxyPoints[i], galaxyPoints[j]);
        }
    }
    
    return sumBetweenGalaxies;
    
}

int manhattanDistance(std::pair<int, int> p1, std::pair<int, int> p2)
{
    return std::abs( p1.first - p2.first) + std::abs(p1.second - p2.second);
}

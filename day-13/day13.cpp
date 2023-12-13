//
//  day13.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/13/23.
//

#include "day13.hpp"

std::vector<std::vector<std::string>> processInput(std::string inputFileName)
{
    // Open the file
    
    std::ifstream inputFile(inputFileName);
    
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
    }
    
    std::vector<std::vector<std::string>> patterns;
    
    std::string line;
    std::vector<std::string> currPattern;
    
    while (std::getline(inputFile, line))
    {
        if (line.empty())
        {
            patterns.push_back(currPattern);
            currPattern.clear();
        }
        else
        {
            currPattern.push_back(line);
        }
    }
    
    // Because there is no empty line at the end, we manually add the last pattern
    if (!currPattern.empty())
    {
        patterns.push_back(currPattern);
    }
    
    return patterns;
}

std::vector<std::string> transposeMatrix(const std::vector<std::string>& matrix)
{
    
    int rows = static_cast<int>(matrix.size());
    int cols = static_cast<int>(matrix[0].size());
    
    std::vector<std::string> rotatedMatrix(cols, std::string(rows,' '));
    
    for (int i { 0 }; i < rows; ++i)
    {
        for (int j { 0 }; j < cols; ++j)
        {
            rotatedMatrix[j][i] = matrix[i][j];
        }
    }
    
    return rotatedMatrix;
}

int getHorizontalReflectionPoint(std::vector<std::string>& pattern)
{
    std::set<std::string> rowsVisitedSet { };
    rowsVisitedSet.insert(pattern[0] + (std::to_string(0)));
    
    int topRowReflectionBreakIdx { -1 };
    
    for (int i { 1 }; i < pattern.size(); ++i)
    {
        int reflectionOffset { -1 };

        
        if (rowsVisitedSet.find(pattern[i] + (std::to_string(i + reflectionOffset))) != rowsVisitedSet.end())
        {
            int minReflectionSize = std::min(i - 1, (static_cast<int>(pattern.size()) - i) - 1);

            bool allMatches { true };
            
            int j = i + 1;
            
            while (minReflectionSize > 0)
            {
                reflectionOffset -= 2;
                
                if (!(rowsVisitedSet.find(pattern[j] + (std::to_string(j + reflectionOffset))) != rowsVisitedSet.end()))
                {
                    allMatches = false;
                    break;
                }

                minReflectionSize -= 1;
                j++;
            }
            
            if (allMatches)
            {
                topRowReflectionBreakIdx = i;
            }
        }
        
        if (topRowReflectionBreakIdx != -1)
        {
            break;
        }
        
        rowsVisitedSet.insert(pattern[i] + (std::to_string(i)));
    }
    
    return topRowReflectionBreakIdx;
    
}


long long day13Part1()
{
    std::vector<std::vector<std::string>> patterns = processInput("./day-13/day13input.txt");
    
    long long result { 0 };
    
    for (auto& pattern : patterns)
    {
        std::vector<std::string> patternT = transposeMatrix(pattern);
        
        int horizontalReflectionPoint = getHorizontalReflectionPoint(pattern);
        int verticalReflectionPoint = getHorizontalReflectionPoint(patternT);
        
        if (horizontalReflectionPoint != -1)
        {
            result += (100 * (horizontalReflectionPoint));
        }
        else
        {
            result += (verticalReflectionPoint);
        }
        
    }
    
    
    return result;
}

long long day13Part2()
{
    
    return 0;
}


// Commented version of horizontal reflection point

/*

int getHorizontalReflectionPoint(std::vector<std::string>& pattern)
{
    std::set<std::string> rowsVisitedSet { };
    rowsVisitedSet.insert(pattern[0] + (std::to_string(0)));
 
 // If we find a reflection break point, we store the index of the bottom row of that reflection
 // For instance, if we have
 // Input:
 // #####.##.
 // #####.##.
 //
 // we would store 1
 
 // If our loop terminates with the index value at -1
 // we never found a valid break point
    
    int topRowReflectionBreakIdx { -1 };
    
    for (int i { 1 }; i < pattern.size(); ++i)
    {
 // The reflection offset is used to match a row in the set that is above the current row
 // if the current row matches the last seen row this boolean condition evaluates to true
 
 // For instance
 // Input:
 // #####.##.
 // #####.##.
 
 // #####.##.0 is in the set
 // i = 1 and we would then find "#####.##." + to_string(1 - 1)  which is ""#####.##." in the set
 
        int reflectionOffset { -1 };

        
        if (rowsVisitedSet.find(pattern[i] + (std::to_string(i + reflectionOffset))) != rowsVisitedSet.end())
        {
 
 
     // If this condition is true for the the first adjacent row above our current row
     // we then take the minimum size of the number of rows on either side of our current split
     // since the reflection cannot extend beyond this minimum
     
     // Note we subtract 1 because we already found 1 match and are looking for the
     // number of remaining matches we need
            int minReflectionSize = std::min(i - 1, (static_cast<int>(pattern.size()) - i) - 1);

            bool allMatches { true };
            
            int j = i + 1;
            
            while (minReflectionSize > 0)
            {
                reflectionOffset -= 2;
                
 // If we have minReflectionSize matches this value remains true
 // otherwise it gets set to false in the while loop
                if (!(rowsVisitedSet.find(pattern[j] + (std::to_string(j + reflectionOffset))) != rowsVisitedSet.end()))
                {
                    allMatches = false;
                    break;
                }

                minReflectionSize -= 1;
                j++;
            }
            
            if (allMatches)
            {
                topRowReflectionBreakIdx = i;
            }
        }
        
        if (topRowReflectionBreakIdx != -1)
        {
            break;
        }
        
        rowsVisitedSet.insert(pattern[i] + (std::to_string(i)));
    }
    
    return topRowReflectionBreakIdx;
    
}

*/

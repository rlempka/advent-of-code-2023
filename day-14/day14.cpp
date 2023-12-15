//
//  day14.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/14/23.
//

#include "day14.hpp"
#include "../helpers/file-helpers.hpp"


long long totalLoadPart1() {
    
    std::vector<std::string> platform { convertFileToLines("./day-14/day14input.txt") };
    
    // Have the last row be all square rocks to avoid edge case when iterating over rows
    std::string lastRowDummy(platform[0].size(), '#');
    
    platform.push_back(lastRowDummy);
    
    std::vector<int> roundRockCountsPerRow(platform.size() - 1, 0);
    
    // Iterate over each column
    for (int j { 0 }; j < platform[0].size(); ++j)
    {
        int lastSquareRockIdx { -1 };
        int zeroCount { 0 };
        
        for (int i { 0 }; i < platform.size(); ++i)
        {
            if (platform[i][j] == 'O')
            {
                zeroCount++;
            }
            else if (platform[i][j] == '#')
            {
                if (zeroCount > 0)
                {
                    for (int k { lastSquareRockIdx + 1}; k < (lastSquareRockIdx + 1 + zeroCount); ++k)
                    {
                        roundRockCountsPerRow[k] += 1;
                    }
                }
                
                lastSquareRockIdx = i;
                zeroCount = 0;
            }
        }
    }
    
    int numRows { static_cast<int>(roundRockCountsPerRow.size()) };
    long long totalLoad { 0 };
    
    for (int i { 0 }; i < roundRockCountsPerRow.size(); ++i)
    {
        totalLoad += (roundRockCountsPerRow[i] * (numRows - i));
    }
    
    
    return totalLoad;
}



long long totalLoadPart2()
{
    
    std::vector<std::string> platform { convertFileToLines("./day-14/day14input.txt") };
    
    // Have the entire platform bordered by square rocks
    std::string dummyRow(platform[0].size(), '#');
    
    platform.push_back(dummyRow);
    platform.insert(platform.begin(), dummyRow);
    
    char newColumnChar { '#' };
    
    

    for (auto& row : platform)
    {
        row.insert(row.begin(), newColumnChar);
        row.push_back(newColumnChar);
    }
    
    // 20 gives answer
    long long cycles { 126 };
    
    std::unordered_map<std::string , int> testCycleMatch { };
    

    bool foundMatch { false };
    
    // 372 match with 508
    // Rotate 93 cycles gets us to 372 rotations
    // 508 - 372 = 136 rotations (34 cycles)
    // Rotate 34 cycles repeatedly to almost 1 billion
    // (1000000000 - 93) mod 34 = 33
    // 126 rotations will do
    
    
    for (int i { 0 }; i < (cycles * 4); ++i)
    {
        northTilt(platform);
        rotateMatrix90DegreesClockwise(platform);
    
        
        
        std::string result { "" };

        for (const std::string& row : platform) {
            result += row;
        }
        
    
        
    
        if(!foundMatch && testCycleMatch.find(result) != testCycleMatch.end())
        {
            
            // The first match tells us when the first cycle occurs, this cycle will repeat from
            // its first occurence until the end r
            std::cout << '\n';
            std::cout << "FIRST ROTATION: " << testCycleMatch[result];
            std::cout << '\n';
            std::cout << "MATCH ROTATION: " << i + 1;
            std::cout << '\n';
            
            
            foundMatch = true;

        }
        
        
        testCycleMatch[result] = i + 1;
        
    
    }
    
    
    std::vector<int> roundRockCountsPerRow = countRocksPerRow(platform);

    int numRows { static_cast<int>(roundRockCountsPerRow.size()) };
    long long totalLoad { 0 };
    
    for (int i { 0 }; i < roundRockCountsPerRow.size(); ++i)
    {
        totalLoad += (roundRockCountsPerRow[i] * (numRows - i));
    }
    
    
    return totalLoad;
    
}

void rotateMatrix90DegreesClockwise(std::vector<std::string>& matrix)
{
    // Transpose the matrix (swap rows with columns)
      for (size_t i = 0; i < matrix.size(); ++i) {
          for (size_t j = i + 1; j < matrix[i].size(); ++j) {
              std::swap(matrix[i][j], matrix[j][i]);
          }
      }

      // Reverse the order of the columns
      for (size_t i = 0; i < matrix.size(); ++i) {
          std::reverse(matrix[i].begin(), matrix[i].end());
      }
    
}

void northTilt(std::vector<std::string>& platform)
{
    
    // Iterate over each column
    for (int j { 0 }; j < platform[0].size(); ++j)
    {
        int lastSquareRockIdx { 0 };
        int zeroCount { 0 };
        
        for (int i { 0 }; i < platform.size(); ++i)
        {
            if (platform[i][j] == 'O')
            {
                zeroCount++;
            }
            else if (platform[i][j] == '#')
            {
                if (zeroCount > 0)
                {
                    for (int k { lastSquareRockIdx + 1}; k < (lastSquareRockIdx + 1 + zeroCount); ++k)
                    {
                        platform[k][j] = 'O';
                    }
                    
                    for (int l {lastSquareRockIdx + 1 + zeroCount }; l < i; ++l)
                    {
                        platform[l][j] = '.';
                    }
                }
                else
                {
                    for (int k { lastSquareRockIdx + 1}; k < i; ++k)
                    {
                        platform[k][j] = '.';
                    }
                }
                
                lastSquareRockIdx = i;
                zeroCount = 0;
            }
        }
    }
    
}

std::vector<int> countRocksPerRow(std::vector<std::string>& platform)
{
    std::vector<int> roundRockCountsPerRow(platform.size() - 2, 0);
    
    for (int i { 1 }; i < platform.size() - 1; ++i)
    {
        for (int j { 0 }; j < platform[0].size(); ++j)
        {
            if (platform[i][j] == 'O')
            {
                roundRockCountsPerRow[i - 1] += 1;
            }
        }
    }
    
   
        
    return roundRockCountsPerRow;
}

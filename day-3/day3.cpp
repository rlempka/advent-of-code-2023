//
//  day3.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/4/23.
//

#include "day3.hpp"

int gearRatios()
{
    std::vector<std::string> lines;
    std::ifstream file("./day-3/day3input.txt");
    
    if (file.is_open()) {
        std::string line;
        
        while (std::getline(file, line)) {
            lines.push_back(line.append("."));
        }
        
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
    }
    
    int m { static_cast<int>(lines.size()) };
    int n { static_cast<int>(lines[0].size())};
    
    std::string currentNumber { "" };
    bool countNum { false };
    int result { 0 };
    
    // Every time a '*' is encountered
    // use charMap[&lines[i][j]] to use the pointer that char as a key
    // and store the value of the adjacent number as the value
    // At the end iterate through the charMap, when there are exactly 2 values sum them
    std::unordered_map<const char* , std::vector<int>> charMap;
    
    char* key { };
    
    for (int i { 0 }; i < m; ++i)
    {
        currentNumber.clear();
        countNum = false;
        
        for (int j { 0 }; j < n; ++j)
        {
            
            if (std::isdigit(lines[i][j]))
            {
                currentNumber += lines[i][j];
                
                if (i + 1 >= 0 && i + 1 < m && lines[i + 1][j] == '*')
                {
                    countNum = true;
                    key = &lines[i + 1][j];
                }
                
                if (i - 1 >= 0 && i - 1 < m && lines[i - 1][j] == '*')
                {
                    countNum = true;
                    key = &lines[i - 1][j];
                }
                
                if (j - 1 >= 0 && j - 1 < n && lines[i][j - 1] == '*')
                {
                    countNum = true;
                    key = &lines[i][j - 1];

                }
                
                if (j + 1 >= 0 && j + 1 < n && lines[i][j + 1] == '*')
                {
                    countNum = true;
                    key = &lines[i][j + 1];
                }
                                
                if (i - 1 >= 0 && i - 1 < m &&
                    j + 1 >= 0 && j + 1 < n &&
                    lines[i - 1][j + 1] == '*')
                {
                    countNum = true;
                    key = &lines[i - 1][j + 1];
                }
                
                if (i - 1 >= 0 && i - 1 < m &&
                    j - 1 >= 0 && j - 1 < n &&
                    lines[i - 1][j - 1] == '*')
                {
                    countNum = true;
                    key = &lines[i - 1][j - 1];

                }
                
                if (i + 1 >= 0 && i + 1 < m &&
                    j - 1 >= 0 && j - 1 < n &&
                    lines[i + 1][j - 1] == '*')
                {
                    countNum = true;
                    key = &lines[i + 1][j - 1];
                }
                
                if (i + 1 >= 0 && i + 1 < m &&
                    j + 1 >= 0 && j + 1 < n &&
                    lines[i + 1][j + 1] == '*')
                {
                    countNum = true;
                    key = &lines[i + 1][j + 1];
                }
            }
            else if (!currentNumber.empty())
            {
                if (countNum)
                {
                    charMap[key].push_back(std::stoi(currentNumber));
                }
                                
                currentNumber.clear();
                countNum = false;
            }
            

        }
    }
    
    int gRatio { };
    
    for (const auto& keyVal : charMap)
    {
        if (keyVal.second.size() == 2)
        {
            gRatio = keyVal.second[0] * keyVal.second[1];
            result += gRatio;
        }
    }
    
    return result;
    
}

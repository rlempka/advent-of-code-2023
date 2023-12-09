//
//  day1.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/4/23.
//

#include "day1.h"


int day1()
{
    
    
    std::vector<std::string> lines;
    
    std::ifstream file("./day-1/input.txt");
    
    if (file.is_open()) {
        std::string line;
        
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
    }
        
    std::vector<int> nums(lines.size());
    
    std::vector<std::string> substrings = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "1", "2", "3", "4", "5", "6", "7", "8", "9"
    };
    
    std::unordered_map<std::string, std::string> numMap = {
        {"one", "1"},
        {"two", "2"},
        {"three", "3"},
        {"four", "4"},
        {"five", "5"},
        {"six", "6"},
        {"seven", "7"},
        {"eight", "8"},
        {"nine", "9"},
        {"1", "1"},
        {"2", "2"},
        {"3", "3"},
        {"4", "4"},
        {"5", "5"},
        {"6", "6"},
        {"7", "7"},
        {"8", "8"},
        {"9", "9"}
    };
    
    const size_t positiveInfinity = std::numeric_limits<size_t>::max();
    const size_t zero = { 0 };
        
    for (int i { 0 }; i < lines.size(); ++i)
    {
        std::pair<size_t, std::string> firstStr { positiveInfinity, "" };
        std::pair<size_t, std::string> lastStr { zero, "" };
        
        std::string numStr { "" };
        
        for (const auto& str : substrings)
        {
            size_t firstIdx = lines[i].find(str);
            size_t lastIdx = lines[i].rfind(str);
            
            if ((firstIdx != std::string::npos) && firstIdx < firstStr.first)
            {
                firstStr.first = firstIdx;
                firstStr.second = str;
            }
            
            if ((lastIdx != std::string::npos) && (lastIdx + str.size() - 1) >= lastStr.first)
            {
                lastStr.first = lastIdx + str.size() - 1;
                lastStr.second = str;
            }
        }
        
        numStr += numMap[firstStr.second];
        numStr += numMap[lastStr.second];
            
        
        nums[i] = std::stoi(numStr);
        
    }
    
    int sum { };
    
    for (const auto& num : nums)
    {
        sum += num;
        std::cout << num << '\n';
    }
    
    return sum;
}

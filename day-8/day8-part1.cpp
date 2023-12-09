//
//  day8-part1.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/8/23.
//

#include "day8-part1.hpp"
#include "../helpers/file-helpers.hpp"

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

long long stepsRequiredZzz()
{
    
    std::vector<std::string> lines { convertFileToLines("./day-8/day8input.txt") };
    
    std::string directions { lines[0] };
    
    std::unordered_map<std::string, std::pair<std::string, std::string>> adjMap { };
    
    std::string key { };
    std::string dummy { };
    std::string left { };
    std::string right { };
    
    for (int i { 2 }; i < lines.size(); ++i)
    {
        std::istringstream iss(lines[i]);
        
        // Get the key
        iss >> key;
        
        iss >> dummy;
        
        iss >> left;
        iss >> right;
        
        adjMap[key] = { left.substr(1, 3), right.substr(0, 3) };
        
    }
    
    /*
    for (auto& val : adjMap)
    {
        std::cout << "Key: " << val.first << '\n';
        std::cout << "Pair: " << val.second.first << " " << val.second.second << '\n';
        std::cout << '\n';
    }
     */
    
    std::vector<std::string> startNodes { };
    
    for (auto& val : adjMap)
    {
        if (val.first.back() == 'A')
        {
            startNodes.push_back(val.first);
        }
    }
    
    std::string currNode = "AAA";
    
    long steps { 0 };
    int directionsIdx { 0 };
    int dirLength { static_cast<int>(directions.size()) };
    
    std::vector<long long> pathLengths { };
    
    for (auto& currNode : startNodes)
    {
        while (currNode.back() != 'Z')
        {
            
            if (directions[directionsIdx % dirLength] == 'L')
            {
                currNode = adjMap[currNode].first;
            }
            else
            {
                currNode = adjMap[currNode].second;
            }
            
            steps += 1;
            directionsIdx += 1;
            
        }
        
        pathLengths.push_back(steps);
        steps = 0;
        directionsIdx = 0;
    }
    
    long long result = 1;
    for (auto& length : pathLengths) {
        result = lcm(result, length);
    }

    std::cout << result << '\n';

    return result;
    
}

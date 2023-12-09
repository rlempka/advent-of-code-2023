//
//  day5-part1.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/5/23.
//

#include "day5-part1.hpp"

bool rangeCheck(long target, long base, long range)
{
    // Subtract 1 because if we start at a number (say 50) and our range is 2
    // then we need to include 50 (e.g. the range would be 50, 51)
    if (target - base >= 0 && target - base < range)
    {
        return true;
    }
    
    return false;
}

long getLocation(long seedNum, std::vector<std::vector<std::vector<long>>>& rangeMaps)
{
    long target { seedNum };
    
    long destination;
    long source;
    long rangeLength;
    
    for (auto& rangeMap : rangeMaps)
    {
        for (auto& range : rangeMap)
        {
            if (rangeCheck(target, range[1], range[2]))
            {
                destination = range[0];
                source = range[1];
                rangeLength = range[2];
                target = destination + (target - source);
                break;
            }
        }
                
    }
    
    return target;
}

void createNewSeeds(std::vector<long>& seeds, std::vector<long>& newSeeds)
{
    
    for (int i { 0 }; i < seeds.size(); i += 2)
    {
        long start { seeds[i] };
        long range { seeds[i + 1] };
                
        for (int j { 0 }; j < range - 1; ++j)
        {
            newSeeds.push_back(start + j);
        }
    }
    
}

long lowestLocation()
{
    
    std::vector<std::string> lines;
    std::ifstream file("./day-5/day5input.txt");
    
    if (file.is_open()) {
        std::string line;
        
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
    }
    
    std::vector<long> seeds { };
    std::vector<std::vector<long>> seedToSoil { };
    std::vector<std::vector<long>> soilToFert { };
    std::vector<std::vector<long>> fertToWater { };
    std::vector<std::vector<long>> waterToLight { };
    std::vector<std::vector<long>> lightToTemp { };
    std::vector<std::vector<long>> tempToHum { };
    std::vector<std::vector<long>> humToLoc { };
    
    std::vector<std::vector<std::vector<long>>> rangeMaps { seedToSoil, soilToFert, fertToWater, waterToLight , lightToTemp, tempToHum, humToLoc };
    
    std::string token;
    
    std::istringstream iss(lines[0]);
    
    // Get rid of "seeds: "
    iss >> token;
    
    while (iss >> token)
    {
        seeds.push_back(std::stol(token));
    }
    
    std::vector<long> newSeeds { };
    
    createNewSeeds(seeds, newSeeds);
    
    
    int rangeMapsIdx { -1 };
    
    for (int i { 1 }; i < lines.size(); ++i)
    {
        
        if (lines[i].empty())
        {
            continue;
        }

        if (lines[i].back() == ':')
        {
            rangeMapsIdx += 1;
            continue;
        }
        
        std::istringstream iss(lines[i]);
        
        std::vector<long> threeTuple { };
        
        while (iss >> token)
        {
            threeTuple.push_back(std::stol(token));
        }
        
        rangeMaps[rangeMapsIdx].push_back(threeTuple);
    }
    
    // Helper code for printing out rangeMaps data structure
    /*
    for (auto& map : rangeMaps)
    {
        for (auto& vec : map)
        {
            for (int i { 0 }; i < vec.size(); ++i)
            {
                std::cout << vec[i] << " ";
            }
            std::cout << '\n';
        }
        
        std::cout << '\n';
        std::cout << '\n';
        std::cout << '\n';
    }
    */
    
    long minLoc { LONG_MAX };
    
    for (auto& seed : newSeeds)
    {
        minLoc = std::min(minLoc, getLocation(seed, rangeMaps));

    }
    
    
    return minLoc;
}

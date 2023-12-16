//
//  day15.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/16/23.
//

#include "day15.hpp"
#include "../helpers/file-helpers.hpp"

int hashAlgo(const std::string& stringToHash)
{
    int currResult { 0 };
    for (const auto& c : stringToHash)
    {
        currResult += c;
        currResult *= 17;
        currResult %= 256;
    }
    return currResult;
}

long long hashInputSeqSum(const std::vector<std::string>& inputSeq)
{
    long long totalSum { 0 };
    
    for (const auto& s : inputSeq)
    {
        totalSum += hashAlgo(s);
    }
    
    return totalSum;
}

long long day15Part1()
{
    std::vector<std::string> rawInputSeq { convertFileToLines("./day-15/day15input.txt") };
    
    std::vector<std::string> inputSeq { splitString(rawInputSeq[0], ',') };
    
    return hashInputSeqSum(inputSeq);
    
}

std::vector<std::string> splitString(std::string& input, char delimiter)
{
    std::vector<std::string> result { };
    std::istringstream iss(input);
    std::string token;
    
    while (std::getline(iss, token, delimiter))
    {
        result.push_back(token);
    }
    
    return result;
}

long long day15Part2()
{
    std::vector<std::list<std::pair<std::string, int>>> hashTable(256);
    
    std::vector<std::string> rawInputSeq { convertFileToLines("./day-15/day15input.txt") };
    
    std::vector<std::string> inputSeq { splitString(rawInputSeq[0], ',') };
    
    long long result { 0 };
    
    for (auto& step : inputSeq)
    {
        processStep(hashTable, step);
    }
    
    for (int i { 0 }; i < hashTable.size(); ++i)
    {
        int j { 0 };
        
        for (auto& p : hashTable[i])
        {
            result += ((i + 1) * (j + 1) * p.second);
            ++j;
        }
    }
    
    return result;
}

void processStep(std::vector<std::list<std::pair<std::string, int>>>& hashTable, std::string& step)
{
    std::vector<std::string> initSeq { splitString(step, '=') };
    
    char operationToPerform { '=' };
    
    if (initSeq.size() == 1)
    {
        initSeq = splitString(step, '-');
        
        operationToPerform = '-';
    }
    
    int bucket { hashAlgo(initSeq[0]) };
    
    if (operationToPerform == '=')
    {
        bool found = { false };
        
        for (auto it = hashTable[bucket].begin(); it != hashTable[bucket].end(); ++it)
        {
            if ((*it).first == initSeq[0])
            {
                *it = { initSeq[0], stoi(initSeq[1]) };
                found = true;
                break;
            }
        }
        
        if (!found)
        {
            hashTable[bucket].insert(hashTable[bucket].end(), { initSeq[0], stoi(initSeq[1]) });
        }
    }
    else
    {
        for (auto it = hashTable[bucket].begin(); it != hashTable[bucket].end(); ++it)
        {
            if ((*it).first == initSeq[0])
            {
                hashTable[bucket].erase(it);
                break;
            }
        }
    }
    
}

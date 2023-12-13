//
//  day12-part1.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/12/23.
//

#include "day12-part1.hpp"
#include "../helpers/file-helpers.hpp"


long long numberOfArrangements()
{
    
    std::vector<std::string> lines { convertFileToLines("./day-12/day12input.txt") };
    
    std::vector<std::pair<std::vector<char>, std::vector<int>>> springVec { };
    
    for (auto& line : lines)
    {
        std::istringstream iss(line);
        
        std::string seq;
        iss >> seq;
        
        std::vector<char> vecSeq { };
        
        for (auto& c : seq)
        {
            vecSeq.push_back(c);
        }
        
        
        std::string token;
        
        std::vector<int> vecConsec { };
        
        while (std::getline(iss, token, ','))
        {
            vecConsec.push_back(std::stoi(token));
        }
        
        springVec.push_back({ vecSeq, vecConsec });
    }

    
    
    /*
    std::cout << '\n';
    std::cout << '\n';

    std::cout << checkSeq(newSeq, consecList);
    
    std::cout << '\n';
    std::cout << '\n';
     */
    
    // 6919 too low
    
    long long arrangementSum { 0 };
   
    
    for (auto& p : springVec)
    {
        long long count { 0 };
        std::vector<char> newSeq = {};
        std::vector<int> listOfNums = p.second;
        std::vector<char> seq = p.first;
        backtrackArrangements(seq, listOfNums, 0, newSeq, count);
        arrangementSum += count;
    }
    
    return arrangementSum;
}

void backtrackArrangements(std::vector<char>& seq, std::vector<int>& consecList, int seqIdx, std::vector<char>& newSeq, long long& validSeqCount)
{
    if (newSeq.size() == seq.size())
    {
        /*
        for (char ch : newSeq) {
                std::cout << ch;
        }
        std::cout << std::endl;
        */
        
        if (validSeq(newSeq, consecList))
        {
            validSeqCount++;
        }
        
        return;
    }
    
    if (seq[seqIdx] == '?')
    {
        newSeq.push_back('#');
        backtrackArrangements(seq, consecList, seqIdx + 1, newSeq, validSeqCount);
        newSeq.pop_back();
        
        newSeq.push_back('.');
        backtrackArrangements(seq, consecList, seqIdx + 1, newSeq, validSeqCount);
        newSeq.pop_back();
    }
    else if (seq[seqIdx] == '#')
    {
        
        newSeq.push_back('#');
        backtrackArrangements(seq, consecList, seqIdx + 1, newSeq, validSeqCount);
        newSeq.pop_back();
    }
    else
    {
        newSeq.push_back('.');
        backtrackArrangements(seq, consecList, seqIdx + 1, newSeq, validSeqCount);
        newSeq.pop_back();
    }
    
}

bool validSeq(std::vector<char>& seqToCheck, std::vector<int> consecCounts)
{
    std::string charString(seqToCheck.begin(), seqToCheck.end());

    std::string delimiter = "\\.+";
    
    std::regex pattern(delimiter);
    std::sregex_token_iterator it(charString.begin(), charString.end(), pattern, -1);
    std::sregex_token_iterator end;

    std::vector<std::string> result {it, end};
    
    // For some reason the regex pattern is giving an empty string "" at beginning of every result
    // so need to remove
    result.erase(std::remove(result.begin(), result.end(), ""), result.end());

    if (result.size() != consecCounts.size())
    {
        return false;
    }

    for (int i { 0 }; i < result.size(); ++i)
    {
        if (result[i].size() != consecCounts[i])
        {
            return false;
        }
    }
    
    
    
    return true;
}

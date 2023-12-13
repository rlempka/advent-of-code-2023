//
//  day12-part2.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/13/23.
//

#include "day12-part2.hpp"
#include "../helpers/file-helpers.hpp"


long long numberOfArrangementsPart2()
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
        
        
        std::vector<char> vecSeqCopy = vecSeq;
        int additionalCopies { 4 };
        
        // Unfold the record
        // We need 5 copies
        // We already have 1 so add 4 more
        for (int i { 0 }; i < additionalCopies; ++i)
        {
            vecSeq.push_back('?');
            vecSeq.insert(vecSeq.end(), vecSeqCopy.begin(), vecSeqCopy.end());
            
        }
         
        
        // Add a '.' to the end of each sequence to make the recursive solution easier
        // This way every seq has at least a single '.' after it, including cases such as "?####",
        // which would now be "?###."
        vecSeq.push_back('.');
        
        std::string token;
        
        std::vector<int> vecConsec { };
        
        while (std::getline(iss, token, ','))
        {
            vecConsec.push_back(std::stoi(token));
        }
        
        
        std::vector<int> vecConsecCopy = vecConsec;
        
        for (int i { 0 }; i < additionalCopies; ++i)
        {
            vecConsec.insert(vecConsec.end(), vecConsecCopy.begin(), vecConsecCopy.end());
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
    long long intermediateRes { 0 };
        
    std::unordered_map<std::string, long long> memo { };
        
    for (auto& p : springVec)
    {
        intermediateRes = numArrangements(p.first, p.second, 0, 0, 0, memo);
        arrangementSum += intermediateRes;
        // There is some odd overlap occuring with my memoization between problems
        // clearing memo for now to get it working for each input
        memo.clear();
    }
    
    /*
    for (auto& m : memo)
    {
        std::cout << "Key: " << m.first << '\n';
        std::cout << "Val: " << m.second << '\n';
    }
    */
    
    return arrangementSum;
}

std::string createMemoKey(std::vector<char>& seq, std::vector<int>& groups, int seqIdx, int groupIdx, int groupSize)
{
    std::string seqStr { "" };
    
    if (seqIdx < seq.size())
    {
        seqStr = std::string(seq.begin() + seqIdx, seq.end());
    }
    
    std::string groupStr { "" };
    
    if (groupIdx < groups.size())
    {
        std::ostringstream groupsStream;
        std::copy(groups.begin() + groupIdx, groups.end(), std::ostream_iterator<int>(groupsStream, ","));
        groupStr = groupsStream.str();
    }
    
    
    return { seqStr + ", " + groupStr + " groupSize: " + std::to_string(groupSize) + " seqIdx: " + std::to_string(seqIdx) + " groupIdx: " + std::to_string(groupIdx)  };
}

long long numArrangements(std::vector<char>& seq, std::vector<int>& groups, int groupSize, int seqIdx, int groupIdx, std::unordered_map<std::string, long long>& memo)
{
    
    std::string memoKey = createMemoKey(seq, groups, seqIdx, groupIdx, groupSize);
    
    
    if (memo.find(memoKey) != memo.end())
    {
         return memo[memoKey];
    }
    
    if (seqIdx == seq.size())
    {
        if (groupIdx == groups.size() && groupSize == 0)
        {
            return 1;
        }
        
        return 0;
    }

    long long num = 0;
    
    std::vector<int> posSymbols = (seq[seqIdx] == '?') ? std::vector<int>{ '#', '.' } : std::vector<int>{ seq[seqIdx] };
    
    for (auto& symbol : posSymbols)
    {
        if (symbol == '#')
        {
            num += numArrangements(seq, groups, groupSize + 1, seqIdx + 1, groupIdx, memo);
        }
        else
        {
            
             if (groupSize != 0)
             {
                 if (groups[groupIdx] == groupSize)
                 {
                     num += numArrangements(seq, groups, 0, seqIdx + 1, groupIdx + 1, memo);
                 }
             }
            else
            {
                num += numArrangements(seq, groups, 0, seqIdx + 1, groupIdx, memo);
            }
        }
    }
    
    memo[memoKey] = num;
    
    return num;
}


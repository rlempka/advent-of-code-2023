//
//  day9-part1.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/9/23.
//

#include "day9-part1.hpp"
#include "../helpers/file-helpers.hpp"

bool allZeros(std::deque<long long> seq)
{
    for (const auto& val : seq)
    {
        if (val != 0)
        {
            return false;
        }
    }
    
    return true;
}

long long sumOfExtrapolatedValues()
{
    std::vector<std::string> lines { convertFileToLines("./day-9/day9input.txt") };
    
    std::vector<std::deque<long long>> seqs { };
    
    for (int i { 0 }; i < lines.size(); ++i)
    {
        std::istringstream iss(lines[i]);
        
        int token;
        std::deque<long long> seq { };
        
        while(iss >> token)
        {
            seq.push_back(token);
        }
        
        seqs.push_back(seq);
    }
    
    std::stack<std::deque<long long>> seqStack { };
    std::vector<long long> newSeqEnds { };
    
   
    
    for (auto& seq : seqs)
    {
        
        while (!allZeros(seq))
        {
            seqStack.push(seq);
                                    
            for (int i { static_cast<int>(seq.size()) - 1 }; i > 0; --i)
            {
                seq[i] = seq[i] - seq[i - 1];
            }
            
            seq.pop_front();
        }
                
        std::deque<long long> firstSeq { };
        std::deque<long long> secondSeq { };
        
        while (seqStack.size() > 1)
        {
            firstSeq = seqStack.top();
            
            /*
            for (auto& val : firstSeq)
            {
                std::cout << val << " ";
                

            }
            std::cout << '\n';
             */
            
            seqStack.pop();
            
            secondSeq = seqStack.top();
            
            
            secondSeq.push_front(secondSeq.front() - firstSeq.front());
            
            /*
            for (auto& val : secondSeq)
            {
                std::cout << val << " ";
                

            }
            std::cout << '\n';
             */
            
            seqStack.pop();
            seqStack.push(secondSeq);
        }
        /*
        std::cout << '\n';
        std::cout << '\n';
        std::cout << '\n';
         */
       
        while (!seqStack.empty())
        {
            seqStack.pop();
        }
        
        
        newSeqEnds.push_back(secondSeq.front());
        
    }
    
    
    long long nextValueSum { 0 };
    
    for (auto& num : newSeqEnds)
    {
        nextValueSum += num;
    }
        
    return nextValueSum;
}



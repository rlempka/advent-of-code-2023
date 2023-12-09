//
//  day7-part1.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/7/23.
//

#include "day7-part1.hpp"
#include "../helpers/file-helpers.hpp"


long totalWinnings()
{
    std::unordered_map<char, long> cardStrength {
        { 'A', 14 },
        { 'K', 13 },
        { 'Q', 12 },
        { 'J', 1 },
        { 'T', 10 },
        { '9', 9 },
        { '8', 8 },
        { '7', 7 },
        { '6', 6 },
        { '5', 5 },
        { '4', 4 },
        { '3', 3 },
        { '2', 2 }
    };
    
    std::unordered_map<char, long> cardCounts {
        { 'A', 0 },
        { 'K', 0 },
        { 'Q', 0 },
        { 'J', 0 },
        { 'T', 0 },
        { '9', 0 },
        { '8', 0 },
        { '7', 0 },
        { '6', 0 },
        { '5', 0 },
        { '4', 0 },
        { '3', 0 },
        { '2', 0 }
    };
    
    // These are all the hash keys for the typeMap
    // each representing a distinct hand type
    // { 5 }, { 4, 1 }, { 3, 2 }, { 2, 2, 1 }, { 2, 1, 1, 1 }
    // { 1, 1, 1, 1, 1 }
    
    // Hands will be converted from strings into vector<int> objects
    // using cardStrength map and then added to a min heap (priority queue) associated with that hand type
    // this way you can iterate through each hand type and pop from the min heap, the last value removed is max
    // and you are popping in ascending order
    
    // Thus if you start with the lowest card strength you can iterate from lowest to highest, removing each card from
    // each heap to get its order
    std::map<std::multiset<long>, std::priority_queue<std::vector<long>, std::vector<std::vector<long>>, std::greater<>>> typeMap { };
    
    // Ordered from lowest strength to highest
    std::vector<std::multiset<long>> cardStrengthKeys {
        { 1, 1, 1, 1, 1 },
        { 2, 1, 1, 1 },
        { 2, 2, 1 },
        { 3, 1, 1 },
        { 3, 2 },
        { 4, 1 },
        { 5 }
    };
    
    std::vector<std::string> lines { convertFileToLines("./day-7/day7input.txt")};
            
    std::string hand { };
    long bet { };
    
    
    for (auto& line : lines)
    {
        std::istringstream iss(line);
        iss >> hand;
        iss >> bet;
        
        // Store inside this vector the numeric values of the hand
        // At the end also store the bet amount
        std::vector<long> handValueVec { };
        
        int jokerCount { 0 };
        
        for (auto& c : hand)
        {
            if (c == 'J')
            {
                jokerCount += 1;
                handValueVec.push_back(cardStrength[c]);
                continue;
            }
            cardCounts[c] += 1;
            handValueVec.push_back(cardStrength[c]);
        }
        
        std::pair<char, long> maxElement { };
        
        if (jokerCount > 0)
        {
            if (jokerCount == 5) {
                cardCounts['A'] = jokerCount;
            }
            else
            {
                maxElement = *std::max_element(cardCounts.begin(), cardCounts.end(), CompareCounts());
                cardCounts[maxElement.first] += jokerCount;
            }
            
        }

        handValueVec.push_back(bet);
                
        std::multiset<long> countSet { };
        
        for (auto& count : cardCounts)
        {
            if (count.second > 0)
            {
                countSet.insert(count.second);
            }
        }
        
        cardCounts.clear();
        
        // Push the hand value vector which contains the numeric value of each card in order plus the bid amount at end
        // This also associates the handValueVec with the appropriate hand type since each countSet defines a specific
        // hand type
        
        /*
        if (jokerCount > 0)
        {
            std::cout << "Joker count: " << jokerCount << " ";
        }
        
        std::cout << "countSet: ";
        for (auto& i : countSet)
        {
            std::cout << i << " ";
        }
        std::cout << " ";
        
        std::cout << "handValueVec: ";
        for (auto& i : handValueVec)
        {
            std::cout << i << " ";
        }
        std::cout << '\n';
        
         */
                        
        // E.g. countSet could be { 4, 1 } and value vector could be [ 10, 10, 10, 8, 10, 457 ]
        typeMap[countSet].push(handValueVec);
    }
    
    long rank { 1 };
    long totalWinnings { 0 };
    
    for (auto& cardKey : cardStrengthKeys)
    {
        
        
        while (!typeMap[cardKey].empty())
        {
            
            long bidAmount = typeMap[cardKey].top().back();

            totalWinnings += (bidAmount * rank);
            typeMap[cardKey].pop();
                        
            rank++;
        }
        
    }
            
    return totalWinnings;
}




//
//  day4-part2.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/5/23.
//

#include "day4-part2.hpp"

int totalCards()
{
    
    std::vector<std::string> lines;
    std::ifstream file("./day-4/day4input.txt");
    
    if (file.is_open()) {
        std::string line;
        
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
    }
    
    std::vector<std::pair<std::set<int>, std::vector<int>>> cards(lines.size());
    
    std::string token;
    
    for (int i { 0 }; i < lines.size(); ++i)
    {
        std::istringstream iss(lines[i]);
        
        // Get rid of first 2 tokens
        // e.g. "Card" and "1:"
        iss >> token;
        iss >> token;
    
        // Get the first list of numbers which are the winning numbers
        std::getline(iss, token, '|');
        std::istringstream winningNumsIss(token);
        
        while (winningNumsIss >> token)
        {
            cards[i].first.insert(std::stoi(token));
        }
        
        // Get the remaining numbers
        std::getline(iss, token);
        std::istringstream elfNumsIss(token);
        
        while (elfNumsIss >> token)
        {
            cards[i].second.push_back(std::stoi(token));
        }
    }

    // Helper code for visualizing the cards data structure
    
    /*
    for (const auto& val : cards)
    {
        for (const auto& element : val.first)
        {
            std::cout << element << " ";
        }
        
        std::cout << " | ";
        
        for (const auto& element : val.second)
        {
            std::cout << element << " ";
        }
        
        std::cout << '\n';
        
    }
    */
    
    std::vector<int> totalCards(lines.size(), 1);
    int numCards { 0 };
    
    int cardIdx;
    
    for (int i { 0 }; i < cards.size(); ++i)
    {
        cardIdx = i;
        
        for (auto& elfNum : cards[i].second)
        {
            numCards = totalCards[i];
            
            if (cards[i].first.find(elfNum) != cards[i].first.end())
            {
                totalCards[cardIdx + 1] += (1 * numCards);
                cardIdx++;
            }
        }
        
    }
    
    int sum = std::accumulate(totalCards.begin(), totalCards.end(), 0);
    
    return sum;
}

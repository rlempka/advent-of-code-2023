//
//  day4-part1.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/5/23.
//

#include "day4-part1.hpp"

int totalPoints()
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
    
    int points { 0 };
    int total { 0 };
    bool first { true };
    
    for (auto& card : cards)
    {
        for (auto& elfNum : card.second)
        {
            if (card.first.find(elfNum) != card.first.end())
            {
                if (first)
                {
                    points += 1;
                    first = false;
                }
                else
                {
                    points *= 2;
                }
            }
        }
        
        total += points;
        points = 0;
        first = true;
    }
    
    return total;
}

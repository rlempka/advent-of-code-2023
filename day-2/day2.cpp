//
//  day2.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/4/23.
//

#include <stdio.h>
#include "day2.h"

int validGames()
{
    
    std::vector<std::string> lines;
    std::unordered_map<std::string, int> colorCounts { };
    int powSetSum { 0 };
    
    std::ifstream file("./day-2/day2input.txt");
    
    if (file.is_open()) {
        std::string line;
        
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
    }
    
    for (auto& line : lines)
    {
        
        std::istringstream iss(line);
        std::string token;
        
        // Skip "Game"
        iss >> token;
        // Skip "1: "
        iss >> token;
        
        std::string numbersOnly;
        for (char c : token) {
            if (std::isdigit(c)) {
                numbersOnly += c;
            }
        }
        
        // int result = std::stoi(numbersOnly);
        
        int count;
        std::string color;
                
        while (std::getline(iss, token, ';')) {
            
            std::istringstream gameIss(token);
                                    
            while (gameIss >> token) {
                
                count = std::stoi(token);
                
                gameIss >> token;

                if (token.back() == ',') {
                    token.pop_back();
                }
                
                color = token;
                
                colorCounts[color] = std::max(colorCounts[color], count);
                
                std::cout << "color: " << color << " count: " << count << '\n';
            }
            
        }
        
        int powSet { 1 };
        
        for (const auto& pair : colorCounts)
        {
            powSet *= pair.second;
        }
        
        powSetSum += powSet;
        
        colorCounts["red"] = 0;
        colorCounts["green"] = 0;
        colorCounts["blue"] = 0;
        
    }
    
    return powSetSum;
    
}

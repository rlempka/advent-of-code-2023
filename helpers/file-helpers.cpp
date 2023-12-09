//
//  file-helpers.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/8/23.
//

#include "file-helpers.hpp"

std::vector<std::string> convertFileToLines(std::string fileLoc)
{
    std::vector<std::string> lines;
    
    // Typically this format "./day-1/input.txt"
    std::ifstream file(fileLoc);
    
    if (file.is_open()) {
        std::string line;
        
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
    }
    
    return lines;
}

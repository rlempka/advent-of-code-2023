//
//  day18.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/19/23.
//

#include "day18.hpp"
#include "../helpers/file-helpers.hpp"

long long cubicMetersLavaPart1()
{
    std::vector<std::string> digPlan { convertFileToLines("./day-18/day18input.txt") };
    
    int maxRight {};
    int maxLeft {};
    int maxUp {};
    int maxDown {};
    
    int borderVolume { 0 };
    int totalVolume { 0 };
    
    for (const std::string& digInstruction : digPlan)
    {
        std::string direction;
        std::string steps;
    
        std::istringstream iss(digInstruction);
        
        iss >> direction;
        iss >> steps;
        
        if (direction == "R")
        {
            maxRight += stoi(steps);
        }
        else if (direction == "L")
        {
            maxLeft += stoi(steps);
        }
        else if (direction == "U")
        {
            maxUp += stoi(steps);
        }
        else
        {
            maxDown += stoi(steps);
        }
        
        borderVolume += stoi(steps);
    }
    
    // std::cout << "maxUp: " << maxUp << " " << "maxLeft: " << maxLeft << " " << "maxRight: " << maxRight << " " << "maxDown: " << maxDown;
    // std::cout << '\n';
    
    // Ensure there is enough up, down, left, right movement space
    std::vector<std::string> ground(1 + maxUp + maxDown, std::string(1 + maxLeft + maxRight, '.'));
    
    ground[maxUp][maxLeft] = '#';
    
    
    digBorder(ground, digPlan, maxUp, maxLeft);

    /*
    for (const std::string& row : ground)
    {
        for (int i { 0 }; i < row.size(); ++i)
        {
            std::cout << row[i] << " ";
        }
        std::cout << '\n';
    }
    */
    
    totalVolume += borderVolume;
    
    for (int i { 0 }; i < ground.size(); ++i)
    {
        for (int j { 0 }; j < ground[0].size(); ++j)
        {
            totalVolume += rayCastNorth(i, j, ground);
        }
    }
    
    return totalVolume;
}

long long cubicMetersLavaPart2()
{
    
    std::vector<std::string> digPlan { convertFileToLines("./day-18/day18input.txt") };
    
    std::string delimiter { "(" };
    std::string token { };
    
    std::vector<std::string> digPlanCorrected(digPlan.size());
    
    std::string processedToken;
    
    for (int i { 0 }; i < digPlan.size(); ++i)
    {
        processedToken = "";
        
        token = digPlan[i].substr(digPlan[i].find(delimiter));
        token = token.substr(2, 6);
                
        processedToken = (getDirection(std::stoi(token.substr(5))) + " " + std::to_string(std::stoi(token.substr(0, 5), nullptr, 16)));
        
        digPlanCorrected[i] = processedToken;
    }
    
    // We will combine the shoelace formula with Pick's theorem to arrive at an answer
    // Pick's theorem states the area of a simple polygon made up of lattice points can be found by the equation: A = i + (b/2) - 1
    // The shoelace formula is a method for finding the area of such polygons given the coordinates of its vertices: https://artofproblemsolving.com/wiki/index.php/Shoelace_Theorem
    // If we can get A, then we can find i by i = A - (b/2) + 1. We use the shoelace formula to get A, and we already know b
    
    std::vector<std::pair<long long, long long>> boundaryVertices { };
    
    // Start at 0, 0
    boundaryVertices.push_back({0, 0});
    std::pair<long long, long long> currPoint { 0, 0 };
    
    long long latticePointsOnBoundary { 0 };
    
    
    for (const auto& instruction : digPlanCorrected)
    {
        std::istringstream iss(instruction);
        
        std::string dir;
        iss >> dir;
        
        std::string steps;
        iss >> steps;
        
        if (dir == "U")
        {
            currPoint.second += stoll(steps);
        }
        else if (dir == "D")
        {
            currPoint.second -= stoll(steps);
        }
        else if (dir == "R")
        {
            currPoint.first += stoll(steps);
        }
        else
        {
            currPoint.first -= stoll(steps);
        }
        
        latticePointsOnBoundary += stoll(steps);
        
        boundaryVertices.push_back(currPoint);
    }
    
    for (auto& verts : boundaryVertices)
    {
        std::cout << "x: " << verts.first << " " << "y: " << verts.second << '\n';
    }
    
    std::cout << (latticePointsOnBoundary % 2) << '\n';
        
    // We return i, which is the number of interior points by Pick's theroem
    // i = A - (b/2) + 1
    // And then we add the boundary area as well which is simply b to get the total areas of boundary plus interior points
    return getArea(boundaryVertices) - ((latticePointsOnBoundary) / 2) + 1 + latticePointsOnBoundary;
}

// Get area using the shoelace method
long long getArea(std::vector<std::pair<long long, long long>> latticeCoords)
{
    long long shoelaceSum { 0 };
    
    for (int i { 0 }; i < latticeCoords.size() - 1; ++i)
    {
        shoelaceSum += ((latticeCoords[i].first * latticeCoords[i + 1].second) -
        (latticeCoords[i + 1].first * latticeCoords[i].second));
    }
    
    return abs(shoelaceSum / 2);
}


std::string getDirection(int dirNumber)
{
    if (dirNumber == 0)
    {
        return "R";
    }
    else if (dirNumber == 1)
    {
        return "D";
    }
    else if (dirNumber == 2)
    {
        return "L";
    }
    else
    {
        return "U";
    }
}

// Returns 1 is the character at row, col is '.' and intersects with '#' an odd number of times (this indicates the ground is within the border)
// Consecutive '#' are counted as a single intersection
int rayCastNorth(int row, int col, std::vector<std::string>& ground)
{
    // We already know the count of the border based on the input data
    if (ground[row][col] == '#')
    {
        return 0;
    }
    
    int intersectCount { 0 };
    
    // Move up 1 position to begin
    int i { row - 1 };
    int j { col };
    
    while (i >= 0)
    {
        if (ground[i][j] == '#')
        {
            std::pair<int, int> firstPointOfIntersection { i, j };
            std::pair<int, int> secondPointOfIntersection { -1, -1 };

            intersectCount += 1;
            --i;
            
            while (i > 0 && ground[i][j] == '#')
            {
                secondPointOfIntersection = {i, j};
                --i;
            }
            
            // If there was a second point of intersection
            if (secondPointOfIntersection.first != -1)
            {
                if (ground[firstPointOfIntersection.first][firstPointOfIntersection.second + 1]
                    == ground[secondPointOfIntersection.first][secondPointOfIntersection.second - 1])
                {
                    continue;
                }
                else
                {
                    intersectCount++;
                }
            }
        }
        else
        {
            --i;
        }
        
    }
    
    return (intersectCount % 2);
}

void digBorder(std::vector<std::string>& ground, std::vector<std::string>& digPlan, int startRow, int startCol)
{
    std::unordered_map<std::string, std::pair<int,int>> directionMap {
        { "R", { 0, 1 } },
        { "L", { 0, -1 } },
        { "U", { -1, 0 } },
        { "D", { 1, 0 } }
    };
    
    ground[startRow][startCol] = '#';
    
    std::pair<int, int> currPos { startRow, startCol };
    
    for (const std::string& digInstruction : digPlan)
    {
        std::string direction;
        std::string steps;
        std::istringstream iss(digInstruction);
        
        iss >> direction;
        iss >> steps;
        
        std::pair<int, int> dirCoords { directionMap[direction] };
        
        int rowDelta { dirCoords.first };
        int colDelta { dirCoords.second };
        
        int newRow { };
        int newCol { };
        
        for (int i { 0 }; i < stoi(steps); ++i)
        {
            newRow = (rowDelta + currPos.first);
            newCol = (colDelta + currPos.second);
            
            ground[newRow][newCol] = '#';
            
            currPos = { newRow, newCol };
        }

    }

}

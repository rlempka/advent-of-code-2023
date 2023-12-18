//
//  day17.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 12/17/23.
//

#include "day17.hpp"
#include "../helpers/file-helpers.hpp"


// coords for movements (up, down, left, right)
std::vector<std::pair<int, int>> movements { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int dijsktraBFSConstrained(const std::vector<std::string>& grid,
                                                     std::pair<int, int> start,
                                                     std::pair<int, int> end)
{
    
    // Keep distance estimates in an unordered map and index based on state
    // State is defined as a 5 tuple which is: i, j, directionX, directionY, consec moves
    // So (1, 1, 0, 1, 2) indicates we are at position (1,1) on the grid, moving right (0, 1) and have gone 2 consecutive
    // steps in the rightward direction
    std::map<std::tuple<int, int, int, int, int>, int> distances;
    
    std::set<std::tuple<int, int, int, int, int>> visited { };
    
    // Priority queue to store (distance, i, j, dirRow, dirCol, and consecMoves)
    std::priority_queue<std::tuple<int, int, int, int, int, int>,
                        std::vector<std::tuple<int, int, int, int, int, int>>,
                        std::greater<>> minHeap { };
    
    // Distance from start states to themselves is 0
    distances[{0, 0, 1, 0, 0}] = 0;
    distances[{0, 0, 0, 1, 0}] = 0;

    
    // Add 2 states to the minHeap to start, when we start we are moving either horizontally right (0, 1) or
    // or vertically down (1, 0)
    minHeap.push({0, start.first, start.second, 1, 0, 0});
    minHeap.push({0, start.first, start.second, 0, 1, 0});

    
    while (!minHeap.empty())
    {
        std::tuple<int, int, int, int, int, int> nextState { minHeap.top() };
        int heatLoss = std::get<0>(nextState);
        int currRow = std::get<1>(nextState);
        int currCol = std::get<2>(nextState);
        int dirRow = std::get<3>(nextState);
        int dirCol = std::get<4>(nextState);
        int consecMoves = std::get<5>(nextState);
              
        minHeap.pop();
        
        if (currRow == end.first && currCol == end.second)
        {
            return heatLoss;
        }
        
        // We've already seen this state, note that the state doesn't include the distance
        // if we have visited this state already we already have the minimum distance to this state
        if (visited.find({currRow, currCol, dirRow, dirCol, consecMoves}) != visited.end())
        {
            continue;
        }
        
        visited.insert({currRow, currCol, dirRow, dirCol, consecMoves});
        
        if (consecMoves < 3)
        {

            int newRow { currRow + dirRow };
            int newCol { currCol + dirCol };
            
            if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size())
            {
                int newDist = (grid[newRow][newCol] - '0') + heatLoss;

                if (!((distances.find({ newRow, newCol, dirRow, dirCol, consecMoves + 1 }) != distances.end())
                    && (distances[{ newRow, newCol, dirRow, dirCol, consecMoves + 1 }] < newDist)))
                {
                    minHeap.push({newDist, newRow, newCol, dirRow, dirCol, consecMoves + 1});
                }
            }
        }
                         
        for (const auto& move : movements)
        {
            // Have already moved conesecutively above, and can't move backwards
            if (!((move.first == dirRow && move.second == dirCol) ||
                (move.first == -dirRow && move.second == -dirCol)))
            {
                int newRow { currRow + move.first };
                int newCol { currCol + move.second };
                
                if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size())
                {
                    int newDist = (grid[newRow][newCol] - '0') + heatLoss;
        
                    if (!((distances.find({ newRow, newCol, dirRow, dirCol, 1 }) != distances.end())
                        && (distances[{ newRow, newCol, dirRow, dirCol, 1 }] < newDist)))
                    {
                        minHeap.push({newDist, newRow, newCol, move.first, move.second, 1});
                        
                    }
                }
            }
        }
    }
    // Couldn't reach the end node
    return -1;
}

int leastHeatLoss()
{
    std::vector<std::string> grid { convertFileToLines("./day-17/day17input.txt") };
    
    std::pair<int, int> start {0, 0};
    std::pair<int, int> end {static_cast<int>(grid.size()) - 1, static_cast<int>(grid[0].size()) - 1 };
    
    int shortestPathSum { dijsktraBFSConstrained(grid, start, end) };
    
    return shortestPathSum;
}

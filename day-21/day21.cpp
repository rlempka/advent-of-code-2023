//
//  day21.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 1/4/24.
//

#include "day21.hpp"
#include "../helpers/file-helpers.hpp"
#define F first
#define S second

long long gardenPlotsReachableOddEven(map<pair<ll, ll>, ll>& shortestPaths, set<pair<ll, ll>>& visited,
                                      vector<string>& elfMap, bool even)

{
    int remainder { 0 };
        
    if (!even)
    {
        remainder = 1;
    }

    ll gardenPlotsReachable { 0 };

    for (const auto& p : visited)
    {
        ll pathDist { shortestPaths[p] };
        
        if (pathDist % 2 == remainder && pathDist != -1)
        {
            gardenPlotsReachable++;
        }
    }
    
    return gardenPlotsReachable;
}

void BFSGardenShortestPathsInfinite(vector<string>& elfMap, map<pair<ll,ll>, ll>& shortestPaths, pair<int, int> startPos, set<pair<ll, ll>>& visited, ll availableSteps)
{
    ll m { static_cast<ll>(elfMap.size()) };
    ll n { static_cast<ll>(elfMap[0].size()) };
    

        
    vector<pair<ll, ll>> posSteps { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    
    // This queue stores the coordinate (row, col) and also available steps remaining
    queue<tuple<ll, ll, ll>> q { };
    
    pair<ll, ll> currNode { };
    pair<ll, ll> nextStep { };
    pair<ll, ll> nextStepModded { };

    
    q.push( { startPos.F, startPos.S, availableSteps } );
    shortestPaths[ {startPos.F, startPos.S} ] = 0;
    visited.insert( {startPos.F, startPos.S} );
    
        
    
    while (!q.empty())
    {
        currNode = { get<0>(q.front()), get<1>(q.front()) };
        
        ll stepsRemaining { get<2>(q.front()) };
        
        q.pop();
        
        if (stepsRemaining > 0)
        {
            stepsRemaining -= 1;
            
            for (const auto& step : posSteps)
            {
                
                nextStepModded = {((currNode.F + step.F) % m + m) % m, ((currNode.S + step.S) % n + n) % n};
                
                nextStep = { (currNode.F + step.F), (currNode.S + step.S) };
                
                if (visited.find({ nextStep.F, nextStep.S }) == visited.end())
                {
                    if (elfMap[nextStepModded.F][nextStepModded.S] == '#')
                    {
                        shortestPaths[{ nextStep.F, nextStep.S }] = -1;
                    }
                    else
                    {
                        shortestPaths[{ nextStep.F, nextStep.S }] = (shortestPaths[{ currNode.F, currNode.S }] + 1);
                        q.push({ nextStep.F, nextStep.S, stepsRemaining });
                    }
                    
                    visited.insert( { nextStep.F, nextStep.S } );
                }
               
            }
        }
                
    }
    
}

void BFSGardenShortestPaths(vector<string>& elfMap, vector<vector<ll>>& shortestPaths, pair<int, int> startPos, vector<vector<bool>>& visited)
{
        
    vector<pair<int, int>> posSteps { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    
    queue<pair<int, int>> q { };
    
    pair<int, int> currNode { };
    pair<int, int> nextStep { };
    
    q.push(startPos);
    shortestPaths[startPos.F][startPos.S] = 0;
    visited[startPos.F][startPos.S] = true;
    
        
    while (!q.empty())
    {
        
        currNode = q.front();
        q.pop();
                
        for (const auto& step : posSteps)
        {
            nextStep = {currNode.F + step.F, currNode.S + step.S};
            
            if (nextStep.F >= 0 && nextStep.F < elfMap.size() && nextStep.S >= 0 && nextStep.S < elfMap[0].size() && visited[nextStep.F][nextStep.S] == false)
            {
                if (elfMap[nextStep.F][nextStep.S] == '#')
                {
                    shortestPaths[nextStep.F][nextStep.S] = -1;
                }
                else
                {
                    shortestPaths[nextStep.F][nextStep.S] = (shortestPaths[currNode.F][currNode.S] + 1);
                    q.push(nextStep);
                }
                
                visited[nextStep.F][nextStep.S] = true;
            }
           
        }
    }
    
}

long long gardenPlotsReachableInfinitePart2()
{
    vector<string> elfMap { convertFileToLines("./day-21/day21input.txt") };
    
    pair<int, int> startPos { 0, 0 };
    
    for (int i { 0 }; i < elfMap.size(); ++i)
    {
        for (int j { 0 }; j < elfMap[i].size(); ++j)
        {
            if (elfMap[i][j] == 'S')
            {
                startPos = { i, j };
            }
        }
    }
    
    elfMap[startPos.first][startPos.second] = '.';

    
    ll gardenPlotsReachableF0 { 0 };
    ll gardenPlotsReachableF1 { 0 };
    ll gardenPlotsReachableF2 { 0 };
    

    map<pair<ll,ll>, ll> shortestPaths { };
    set<pair<ll, ll>> visited { };
    
    
    ll shortestPathToEdgeFromCenter { 65 };
    ll widthOfGrid { 131 };
    
    // Notice that all paths <= 65 in the input form a rhombus (diamond shape)
    // Therefore we have a quadratic function, and can calculate f(n) where n is the number of grid expansions
    // and f(n) = y is the max number of steps we can take in that expanded grid
    
    // f(0)
    BFSGardenShortestPathsInfinite(elfMap, shortestPaths, startPos, visited, shortestPathToEdgeFromCenter);
    gardenPlotsReachableF0 = gardenPlotsReachableOddEven(shortestPaths, visited, elfMap, false);
    shortestPaths.clear();
    visited.clear();
    
    // f(1)
    BFSGardenShortestPathsInfinite(elfMap, shortestPaths, startPos, visited, shortestPathToEdgeFromCenter + widthOfGrid);
    gardenPlotsReachableF1 = gardenPlotsReachableOddEven(shortestPaths, visited, elfMap, true);
    shortestPaths.clear();
    visited.clear();
    
    // f(2)
    BFSGardenShortestPathsInfinite(elfMap, shortestPaths, startPos, visited, shortestPathToEdgeFromCenter + 2*widthOfGrid);
    gardenPlotsReachableF2 = gardenPlotsReachableOddEven(shortestPaths, visited, elfMap, false);
    shortestPaths.clear();
    visited.clear();
    
    /*
    cout << "f(0) = " << gardenPlotsReachableF0 << '\n';
    cout << "f(1) = " << gardenPlotsReachableF1 << '\n';
    cout << "f(1) = " << gardenPlotsReachableF2 << '\n';
    */
    
    // Three points obtained:
    // f(0) = 3943
    // f(1) = 35126
    // f(2) = 97407
    // Need to find coefficients a, b, c for quadratic equation: f(x) = a*x^2 + b*x + c
    // f(0) = 3943 = c
    // f(1) = 35126 = a + b + c
    // f(2) = 97407 = a*4 + b*2 + c
    // f(1) - f(0) = 35126 - 3943 = 31183 = a + b
    // f(2) - f(1) = 97407 - 35126 = 62281 = 3*a + b
    // a = 31183 - b
    // 62281 = 3*(31183 - b) + b = 93549 - 3b + b = 93549 - 2b
    // b = 15634
    // 35126 = a + 15634 + 3943
    // a = 15549
    // c = 3943
    // Final quadratic equation f(x) = 15549*x^2 + 15634*x + 3943
    
    ll coefficientA { 15549 };
    ll coefficientB { 15634 };
    ll coefficientC { 3943 };
    
    
    ll numExpansionsRequired = { (26501365 - shortestPathToEdgeFromCenter) / widthOfGrid };
    
    return coefficientA*pow(numExpansionsRequired, 2) + coefficientB*numExpansionsRequired + coefficientC;

    
}

long long gardenPlotsReachable64StepsPart1()
{
    vector<string> elfMap { convertFileToLines("./day-21/day21input.txt") };
    
    pair<int, int> startPos { 0, 0 };
    
    for (int i { 0 }; i < elfMap.size(); ++i)
    {
        for (int j { 0 }; j < elfMap[i].size(); ++j)
        {
            if (elfMap[i][j] == 'S')
            {
                startPos = { i, j };
            }
        }
    }
    
    elfMap[startPos.first][startPos.second] = '.';
    
    vector<vector<ll>> shortestPaths(elfMap.size(), vector<ll>(elfMap[0].size()));
    vector<vector<bool>> visited(elfMap.size(), vector<bool>(elfMap[0].size()));
    
    BFSGardenShortestPaths(elfMap, shortestPaths, startPos, visited);
    
    ll gardenPlotsReachable { 0 };
        
    
    for (int i { 0 }; i < shortestPaths.size(); ++i)
    {
        for (int j { 0 }; j < shortestPaths[0].size(); ++j)
        {
            
            if (shortestPaths[i][j] % 2 == 0 && shortestPaths[i][j] <= 65
                && visited[i][j] == true)
            {
                gardenPlotsReachable++;
                cout << elfMap[i][j] << '\n';

            }
       
            
            
        }
    }
    
    
    /*
    
    for (int i { 0 }; i < shortestPaths.size(); ++i)
    {
        for (int j { 0 }; j < shortestPaths[0].size(); ++j)
        {
            if (shortestPaths[i][j] == (14 + 22))
            {
                elfMap[i][j] = 'X';
            }

        }
    }
    
     */
    
    /*
    for (int i { 0 }; i < elfMap.size(); ++i)
    {
        for (int j { 0 }; j < elfMap[0].size(); ++j)
        {
            cout << elfMap[i][j] << " ";
        }
        cout << '\n';

    }
     */
    
    
    return gardenPlotsReachable;
}

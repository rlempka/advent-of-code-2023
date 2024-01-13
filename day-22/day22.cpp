//
//  day22.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 1/11/24.
//

#include "day22.hpp"
#include "../helpers/file-helpers.hpp"

#define F first
#define S second

struct LabeledPoint
{
    ll x;
    ll y;
    ll z;
    
    ll label;
};

bool compareByFirstZ(const pair<LabeledPoint, LabeledPoint>& a, const pair<LabeledPoint, LabeledPoint>& b)
{
    return a.F.z > b.F.z;
};

struct CompareBySecondZ {
    bool operator()(const pair<LabeledPoint, LabeledPoint>& a, const pair<LabeledPoint, LabeledPoint>& b) const {
        return a.S.z < b.S.z;
    }
};

bool onSegment(LabeledPoint p, LabeledPoint q, LabeledPoint r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
    {
        return true;
    }
    
    return false;
}

// 0 --> p, q, r collinear
// 1 --> Clockwise
// 2 --> Counterclockwise

ll orientation(LabeledPoint p, LabeledPoint q, LabeledPoint r)
{
    ll val = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);
    
    if (val == 0) return 0;
    
    // val > 0 clockwise, otherwise counter clockwise
    return (val > 0) ? 1 : 2;
}

bool doIntersect(LabeledPoint p1, LabeledPoint q1, LabeledPoint p2, LabeledPoint q2)
{
    ll o1 = orientation(p1, q1, p2);
    ll o2 = orientation(p1, q1, q2);
    ll o3 = orientation(p2, q2, p1);
    ll o4 = orientation(p2, q2, q1);
    
    if (o1 != o2 && o3 != o4)
        return true;
    
    // Collinear cases
    
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    
    if (o3 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

tuple<ll, ll, ll, ll, ll, ll> getTupleFromPoints(LabeledPoint p1, LabeledPoint q1)
{
    return make_tuple(p1.x, p1.y, p1.z, q1.x, q1.y, q1.z);
}

ll sumOfBricksThatWouldFallPart2()
{
    ifstream fallingBrickSnapshot("./day-22/day22input.txt");
    
    vector<pair<LabeledPoint, LabeledPoint>> fallingBrickInitialPoints { };
    vector<pair<LabeledPoint, LabeledPoint>> settledBricks { };
    
    set<tuple<ll, ll, ll, ll, ll, ll>> alreadyCounted { };
    
    set<ll> brickToDisintegrateLabel { };
    
    string brick;
    ll brickLabel { 0 };
    
    ll cannotDisintegrate { 0 };
    
    while(getline(fallingBrickSnapshot, brick))
    {
        istringstream iss(brick);
        LabeledPoint p1, p2;
        
        char ignore;
        
        iss >> p1.x >> ignore >> p1.y >> ignore >> p1.z >> ignore;
        iss >> p2.x >> ignore >> p2.y >> ignore >> p2.z;
        
        p1.label = brickLabel;
        p2.label = brickLabel;
        
        brickLabel++;
        
        fallingBrickInitialPoints.push_back({p1, p2});

    }
    
    ll numBricks { static_cast<ll>(fallingBrickInitialPoints.size()) };
    
    sort(fallingBrickInitialPoints.begin(), fallingBrickInitialPoints.end(), compareByFirstZ);
    
    // Add the brick at the lowest point to the settled bricks and adjust the z value to be "settled" on the ground
    ll prevZ { fallingBrickInitialPoints[numBricks - 1].F.z };
    fallingBrickInitialPoints[numBricks - 1].F.z = 1;
    fallingBrickInitialPoints[numBricks - 1].S.z = fallingBrickInitialPoints[numBricks - 1].S.z - (prevZ - 1);
    
    settledBricks.push_back(fallingBrickInitialPoints[numBricks - 1]);
    
    // Iterate through the remaining falling bricks from lowest z value to highest
    for (int i { static_cast<int>(fallingBrickInitialPoints.size()) - 2 }; i >= 0; --i)
    {
        pair<LabeledPoint, LabeledPoint> currBrick { fallingBrickInitialPoints[i] };
        priority_queue<pair<LabeledPoint, LabeledPoint>, vector<pair<LabeledPoint, LabeledPoint>>, CompareBySecondZ> adjacentBricks { };
        
        for (const auto& settledBrick : settledBricks)
        {
            
            if (doIntersect(currBrick.F, currBrick.S, settledBrick.F, settledBrick.S))
            {
                adjacentBricks.push(settledBrick);
            }
            
        }
        
        if (adjacentBricks.size() == 1)
        {
            pair<LabeledPoint, LabeledPoint> neighborBelow { adjacentBricks.top() };
            ll prevZ { currBrick.F.z };
            currBrick.F.z = neighborBelow.S.z + 1;
            currBrick.S.z = currBrick.F.z + (currBrick.S.z - prevZ);
            
            if (alreadyCounted.find(getTupleFromPoints(neighborBelow.F, neighborBelow.S)) == alreadyCounted.end())
            {
                brickToDisintegrateLabel.insert(neighborBelow.F.label);
                cannotDisintegrate++;
                alreadyCounted.insert(getTupleFromPoints(neighborBelow.F, neighborBelow.S));
            }
        }
        else if (adjacentBricks.size() > 1)
        {
            pair<LabeledPoint, LabeledPoint> neighborBelowFirst { adjacentBricks.top() };
            adjacentBricks.pop();
            pair<LabeledPoint, LabeledPoint> neighborBelowSecond { adjacentBricks.top() };;
            adjacentBricks.pop();
            
            ll prevZ { currBrick.F.z };
            currBrick.F.z = neighborBelowFirst.S.z + 1;
            currBrick.S.z = currBrick.F.z + (currBrick.S.z - prevZ);
            
            if (neighborBelowFirst.S.z != neighborBelowSecond.S.z)
            {
                if (alreadyCounted.find(getTupleFromPoints(neighborBelowFirst.F, neighborBelowFirst.S)) == alreadyCounted.end())
                {
                    brickToDisintegrateLabel.insert(neighborBelowFirst.F.label);
                    cannotDisintegrate++;
                    alreadyCounted.insert(getTupleFromPoints(neighborBelowFirst.F, neighborBelowFirst.S));
                }
            }

        }
        else
        {
            ll prevZ { currBrick.F.z };
            currBrick.F.z = 1;
            currBrick.S.z = currBrick.F.z + (currBrick.S.z - prevZ);
        }
        
        settledBricks.push_back(currBrick);
    }
    
    
    // Iterate through the settled bricks, removing each brick that causes 1 or more bricks to fall
    // The removal of a brick is simulated by ignoring that bricks label, and counting all of the other
    // bricks that have a z-value that changes absent that brick
    sort(settledBricks.begin(), settledBricks.end(), compareByFirstZ);
    
    
    ll totalChangedZValues { 0 };
    
    for (auto& l : brickToDisintegrateLabel)
    {
        ll changedZValuesForLabel { 0 };
        
        vector<pair<LabeledPoint, LabeledPoint>> settledBricksCopy { settledBricks };
        
        for (int i { static_cast<int>(settledBricksCopy.size()) - 1 }; i >= 0; --i)
        {
            pair<LabeledPoint, LabeledPoint>& currBrick { settledBricksCopy[i] };

            if (currBrick.F.label == l)
            {
                continue;
            }
            
            priority_queue<pair<LabeledPoint, LabeledPoint>, vector<pair<LabeledPoint, LabeledPoint>>, CompareBySecondZ> adjacentBricks { };
            
            for (int j { i + 1 }; j < settledBricksCopy.size(); ++j)
            {
                
                if (settledBricksCopy[j].F.label != l &&
                    doIntersect(currBrick.F, currBrick.S, settledBricksCopy[j].F, settledBricksCopy[j].S))
                {
                    adjacentBricks.push(settledBricksCopy[j]);
                }
                
            }
            
            if (adjacentBricks.size() >= 1)
            {
                pair<LabeledPoint, LabeledPoint> neighborBelow { adjacentBricks.top() };
                ll prevZ { currBrick.F.z };
                currBrick.F.z = neighborBelow.S.z + 1;
                currBrick.S.z = currBrick.F.z + (currBrick.S.z - prevZ);
                
                
                if (currBrick.F.z != prevZ)
                {
                    changedZValuesForLabel++;

                }
               
            }
            else
            {
                ll prevZ { currBrick.F.z };
                currBrick.F.z = 1;
                currBrick.S.z = currBrick.F.z + (currBrick.S.z - prevZ);
                
                if (currBrick.F.z != prevZ)
                {
                    changedZValuesForLabel++;


                }
            }
            
        }
        
        totalChangedZValues += changedZValuesForLabel;
    }
    
    
    return totalChangedZValues;
}

ll safeToDisintegrateBrickCount()
{
    
    ifstream fallingBrickSnapshot("./day-22/day22input.txt");

    vector<pair<LabeledPoint, LabeledPoint>> fallingBrickInitialPoints { };
    
    vector<pair<LabeledPoint, LabeledPoint>> settledBricks { };
    
    set<tuple<ll, ll, ll, ll, ll, ll>> alreadyCounted { };
        
    string brick;
    
    while (getline(fallingBrickSnapshot, brick)) {
        
        istringstream iss(brick);
        LabeledPoint p1, p2;
        
        char ignore;

        iss >> p1.x >> ignore >> p1.y >> ignore >> p1.z >> ignore;
        iss >> p2.x >> ignore >> p2.y >> ignore >> p2.z;
        
        fallingBrickInitialPoints.push_back({p1, p2});
    }
    
    ll numBricks { static_cast<ll>(fallingBrickInitialPoints.size()) };
    
    sort(fallingBrickInitialPoints.begin(), fallingBrickInitialPoints.end(),  compareByFirstZ);
    
    // Add the brick at the lowest point to the settled bricks and adjust the z value to be "settled" on the ground
    ll prevZ { fallingBrickInitialPoints[numBricks - 1].F.z };
    fallingBrickInitialPoints[numBricks - 1].F.z = 1;
    fallingBrickInitialPoints[numBricks - 1].S.z = fallingBrickInitialPoints[numBricks - 1].S.z - (prevZ - 1);
    
    settledBricks.push_back(fallingBrickInitialPoints[numBricks - 1]);
    
    ll cannotDisintegrate { 0 };
    
    // Iterate through the remaining falling bricks from lowest z value to highest
    for (int i { static_cast<int>(fallingBrickInitialPoints.size()) - 2 }; i >= 0; --i)
    {
        pair<LabeledPoint, LabeledPoint> currBrick { fallingBrickInitialPoints[i] };
        priority_queue<pair<LabeledPoint, LabeledPoint>, vector<pair<LabeledPoint, LabeledPoint>>, CompareBySecondZ> adjacentBricks { };
        
        for (const auto& settledBrick : settledBricks)
        {
            
            if (doIntersect(currBrick.F, currBrick.S, settledBrick.F, settledBrick.S))
            {
                adjacentBricks.push(settledBrick);
            }
            
        }
        
        if (adjacentBricks.size() == 1)
        {
            pair<LabeledPoint, LabeledPoint> neighborBelow { adjacentBricks.top() };
            ll prevZ { currBrick.F.z };
            currBrick.F.z = neighborBelow.S.z + 1;
            currBrick.S.z = currBrick.F.z + (currBrick.S.z - prevZ);
            
            if (alreadyCounted.find(getTupleFromPoints(neighborBelow.F, neighborBelow.S)) == alreadyCounted.end())
            {
                cannotDisintegrate++;
                alreadyCounted.insert(getTupleFromPoints(neighborBelow.F, neighborBelow.S));
            }
        }
        else if (adjacentBricks.size() > 1)
        {
            pair<LabeledPoint, LabeledPoint> neighborBelowFirst { adjacentBricks.top() };
            adjacentBricks.pop();
            pair<LabeledPoint, LabeledPoint> neighborBelowSecond { adjacentBricks.top() };;
            adjacentBricks.pop();
            
            ll prevZ { currBrick.F.z };
            currBrick.F.z = neighborBelowFirst.S.z + 1;
            currBrick.S.z = currBrick.F.z + (currBrick.S.z - prevZ);
            
            if (neighborBelowFirst.S.z != neighborBelowSecond.S.z)
            {
                if (alreadyCounted.find(getTupleFromPoints(neighborBelowFirst.F, neighborBelowFirst.S)) == alreadyCounted.end())
                {
                    cannotDisintegrate++;
                    alreadyCounted.insert(getTupleFromPoints(neighborBelowFirst.F, neighborBelowFirst.S));
                }
            }

        }
        else
        {
            ll prevZ { currBrick.F.z };
            currBrick.F.z = 1;
            currBrick.S.z = currBrick.F.z + (currBrick.S.z - prevZ);
        }
        
        settledBricks.push_back(currBrick);
    }
    
    return numBricks - cannotDisintegrate;
}

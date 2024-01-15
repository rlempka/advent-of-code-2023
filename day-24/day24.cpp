//
//  day23.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 1/15/24.
//

#include "day24.hpp"
#include "../helpers/file-helpers.hpp"


#define F first
#define S second

typedef long long ll;
typedef long double ld;

// Taking ideas from here: https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect/565282#565282
// And adapting it for rays intersecting line segments https://stackoverflow.com/questions/14307158/how-do-you-check-for-intersection-between-a-line-segment-and-a-line-ray-emanatin

// For any ray inside of the bounding box or collinear to the bounding box, we can therefore define a line segment based on 2
// points, the point it enters the bounding box and exits the bounding box. For the collinear case, we select the 2 corner
// points as the line segment points

// Once we have all of our segments within the bounding box, we look at each pair of segments and determine if they intersect
// using a method similar to day 22. That is we look at the relationships of the orientation between the 4 points (2 points from each segment)
// And based on that relationship determine if they intersect

struct Point
{
    ld x;
    ld y;
    ld z;
    
    // Uncertain if label needed but adding in anticipation of part 2
    ld label;
};

typedef pair<Point, Point> seg;
typedef pair<Point, Point> ray;

// p is the start of the ray, and r is the velocity
// q is the start of the segment, and s is the start of the segment - end of segment
Point rayIntersectingSegment(Point p, Point r, Point q, Point s)
{
    // Ray is p to p + r and segment is q to q + s
    // p to p + r and q to q + s
    
    Point qLp { q.x - p.x, q.y - p.y };
    ld rXs { r.x*s.y - r.y*s.x };
    ld qLpXs { qLp.x*s.y - qLp.y*s.x };
    ld qLpXr { qLp.x*r.y - qLp.y*r.x };
    
    // t = (q − p) × s / (r × s)
    // u = (q − p) × r / (r × s)
    long double t { qLpXs / rXs };
    long double u { qLpXr / rXs };
    
    // Lines are collinear
    if (rXs == 0 && qLpXr == 0)
    {
        // All zeros indicate collinearity
        // due to our bounding box (0, 0) cannot be a valid point of
        // intersection so if we have exactly 1 intersection between
        // our ray and the bounding box, and the return value is all zeros
        // we intialize a segment equal to the bounding box edge
        return { 0, 0, 0, 0 };
    }
    else if (rXs == 0 && qLpXr != 0)
    {
        // Lines are parralel and do not intersect
        // Due to our bounding box {-1, -1}
        return { -1, -1, 0, 0 };
    }
    else if (rXs != 0 && t >= 0 && u >= 0 && u <= 1)
    {
        // If r × s ≠ 0 and 0 ≤ t ≤ 1 and 0 ≤ u ≤ 1, the two line segments meet at the point p + t r = q + u s
        return { (p.x + r.x*t), (p.y + r.y*t) };
    }
    else
    {
        // Segment and ray not parallel and no intersection
        return { -1, -1, 0, 0 };
    }
    
}

ll numIntersectionsTestAreaPart1()
{
    ifstream hailstoneTrajectories("./day-24/day24input.txt");
    
    ld testMin { 7 };
    ld testMax { 27 };
    
    seg bottomHoriztonalTestBoundary { {testMin, testMin}, {testMax, testMin} };
    seg topHoriztonalTestBoundary { {testMin, testMax}, {testMax, testMax} };
    seg leftVerticalTestBoundary { { testMin, testMin }, { testMin, testMax } };
    seg rightVerticalTestBoundary { { testMax, testMin }, { testMax, testMax } };
    
    // Stores the rays as start pos and velocity (2 points)
    vector<ray> rays { };
    vector<seg> boundaries { bottomHoriztonalTestBoundary, topHoriztonalTestBoundary, leftVerticalTestBoundary, rightVerticalTestBoundary  };
    
    // Used to store the segments we discover that the rays create inside of the boundary
    vector<seg> raySegsWithinBounds { };
    
    string traj;
    
    while (getline(hailstoneTrajectories, traj))
    {
        istringstream iss(traj);
        
        Point r1, v1;
        
        char ignore;
        
        iss >> r1.x >> ignore >> r1.y >> ignore >> r1.z >> ignore;
        iss >> v1.x >> ignore >> v1.y >> ignore >> v1.z;
        
        rays.push_back({r1, v1});
    }
    
    /*
    for (const auto& r : rays)
    {
        cout << "sx: " << r.F.x << " sy: " << r.F.y << " sz: " << r.F.z << '\n';
        cout << "vx: " << r.S.x << " vy: " << r.S.y << " vz: " << r.S.z << '\n';
    }
    */
    
    for (const auto& r : rays)
    {
        vector<Point> boundaryIntersections { };
        
        for (const auto& b : boundaries)
        {
            Point boundaryIntersect { rayIntersectingSegment(r.F, r.S, b.F, { b.S.x - b.F.x, b.S.y - b.F.y } ) };
            
            // Ray is collinear to a boundary
            if (boundaryIntersect.x == 0 && boundaryIntersect.y == 0)
            {
                boundaryIntersections.push_back(b.F);
                boundaryIntersections.push_back(b.S);
                break;
            }
            else if (boundaryIntersect.x != - 1 && boundaryIntersect.y != -1)
            {
                boundaryIntersections.push_back(boundaryIntersect);
            }
        }
        
        if (boundaryIntersections.size() > 2 || boundaryIntersections.size() == 1)
        {
            // This is actually correct since most of the points are inside the bounding box
            cout << '\n';
            cout << "Boundary intersections size: " << boundaryIntersections.size() << '\n';
            cout << "Error, size should be either 0 (no intersections found) or 2\n";
            cout << "x: " << boundaryIntersections[0].x << " y: " << boundaryIntersections[0].y << '\n';
            cout << '\n';
        }
        else if (boundaryIntersections.size() == 2)
        {
            raySegsWithinBounds.push_back( { boundaryIntersections[0], boundaryIntersections[1] } );
        }
        
        
    }
    
    
    for (const auto& r : raySegsWithinBounds)
    {
        cout << "sx: " << r.F.x << " sy: " << r.F.y << " sz: " << r.F.z << '\n';
        cout << "ex: " << r.S.x << " ey: " << r.S.y << " ez: " << r.S.z << '\n';
    }
    
    
    return 0;
}
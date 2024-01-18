//
//  day23.cpp
//  advent-of-code-2023
//
//  Created by Leonhard Euler on 1/15/24.
//

#include "day24.hpp"
#include "../helpers/file-helpers.hpp"
#include <Eigen/Dense>
#include <Eigen/Core>

#define F first
#define S second

typedef long long ll;
typedef long double ld;
typedef Eigen::Matrix<long double, 3, 1> Vector3ld;
typedef Eigen::Matrix<long double, Eigen::Dynamic, 1> VectorXld;
typedef Eigen::Matrix<long double, Eigen::Dynamic, Eigen::Dynamic> MatrixXld;

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

struct PointBig
{
    long double x;
    long double y;
    long double z;
    
    // Uncertain if label needed but adding in anticipation of part 2
    long double label;
};

typedef pair<Point, Point> ray;
typedef pair<PointBig, PointBig> rayLong;


// p is the start of the ray, and r is the velocity
// q is the start of the segment, and s is the start of the segment - end of segment
Point rayIntersectingRay(Point p, Point r, Point q, Point s)
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
    else if (rXs != 0 && t >= 0 && u >= 0)
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

Eigen::Matrix<long double, 3, 3> crossMatrix(Vector3ld v)
{
    Eigen::Matrix<long double, 3, 3> crossMatrix;
    
    // For info on converting (u x v) the cross product of u with v
    // into ux * v (the dot product of the cross matrix of u with v)
    // https://math.fandom.com/wiki/Cross_product
    crossMatrix << 0, -v[2], v[1],
                   v[2], 0, -v[0],
                  -v[1], v[0], 0;
    
    return crossMatrix;
    
}

// Credit for this solution: https://pastebin.com/NmR6ZDXL

ll xyzSumMagicRockInitialPositionPart2()
{
    ifstream hailstoneTrajectories("./day-24/day24input.txt");
    
    // Stores the rays as start pos and velocity (2 points)
    vector<rayLong> rays { };
    
    string traj;
    
    while (getline(hailstoneTrajectories, traj))
    {
        istringstream iss(traj);
        
        PointBig r1, v1;
        
        char ignore;
        
        iss >> r1.x >> ignore >> r1.y >> ignore >> r1.z >> ignore;
        iss >> v1.x >> ignore >> v1.y >> ignore >> v1.z;
        
        rays.push_back({r1, v1});
    }
        
    // What follows is outlined in this Reddit comment
    // https://www.reddit.com/r/adventofcode/comments/18pnycy/comment/kepu26z/?utm_source=share&utm_medium=web2x&context=3
    
    // To be clear we are exploiting the fact that for any hailstone i
    // of the total n hailstones
    // s0 + t[i]*r0 = p[i] + t[i]*v[i]
    // Where s0 is the 3d start position of the rock and r0 is the velocity of the rock
    // We can rearranged and use the fact that the cross product of a vector with itself is 0 to obtain
    // s0 - p[i] = t[i]*v[i] - t[i]*r0
    // s0 - p[i] = t[i]*(v[i] - r0)
    // s0 - p[i] = -t[i]*(r0 - v[i])
    // s0 - p[i] x (r0 - v[i]) = -t[i]*(r0 - v[i]) x (r0 - v[i])
    // (s0 - p[i]) x (r0 - v[i]) = 0
    // Expanding this out gives
    // (s0 x r0) - (s0 x v[i]) - (p[i] x r0) + (p[i] x v[i])
    // Since (s0 x r0) is common to every single hailstone, we can use it to
    // equate a pair of hailstones, and in the process eliminate
    // For example, if we have hailstone 0 and 1
    // - (s0 x v[0]) - (p[0] x r0) + (p[0] x v[0]) = (s0 x r0)
    // - (s0 x v[1]) - (p[1] x r0) + (p[1] x v[1]) = (s0 x r0)
    // - (s0 x v[0]) - (p[0] x r0) + (p[0] x v[0]) = - (s0 x v[1]) - (p[1] x r0) + (p[1] x v[1])
    // Now we can rearrange these terms to get the LHS in terms of s0 and r0 (what we are trying to solve for), this gives
    // - (s0 x v[0]) - (p[0] x r0) + (s0 x v[1]) + (p[1] x r0) = (p[1] x v[1]) - (p[0] x v[0])
    // Rearranging again and using the fact that (u x v) = - (v x u) so we can ensure r0 and s0 are on the right hands side of our cross product, so that we can use cross matrices, gives us
    // (v[0] x s0) - (v[1] x s0) - (p[0] x r0) + (p[1] x r0) = (p[1] x v[1]) - (p[0] x v[0])
    // We can then factor out s0 and r0 to give
    // ((v[0] - v[1]) x s0) - ((p[0] + p[1]) x r0) = (p[1] x v[1]) - (p[0] x v[0])
    // And use the property that (u x v) is the same as (U)*v where U is the cross product matrix of U and '*' is the dot product operator to get
    // (V[0] - V[1] - P[0] + P[1])*(s0 v0) where (s0 v0) indicates a six dimensional vector arranged vertically
    // Since this only gives us 3 equations, since the result of the cross product is 3 values
    // We need to also use another pair of hailstones, so we use 0 and 2, giving the final arrangement as
    // |V[0] - V[1] - P[0] + P[1]|             | (p[1] x v[1]) -  (p[0] x v[0])|
    // |V[0] - V[2] - P[0] + P[2]| * (s0 v0) = | (p[2] x v[2]) -  (p[0] x v[0]) |
    // Note the vertical bars indicate a broader 6, 6 matrix on the LHS and 6, 1 vector on the RHS, since the RHS is just the subtraction of 2 cross products stacked vertically
    
    // Now we have a 6 x 6 matrix, giving 6 equations with 6 unknowns
    // We can arrange the matrix accordingly as Mx = b and then perform x = M^(-1)b
    // (that is take the inverse of M and multiply it by b
    
    
    VectorXld result(6);
    
    Vector3ld p0 { rays[0].F.x, rays[0].F.y, rays[0].F.z };
    Vector3ld p1 { rays[1].F.x, rays[1].F.y, rays[1].F.z };
    Vector3ld p2 { rays[2].F.x, rays[2].F.y, rays[2].F.z };
    
    
    Vector3ld v0 { rays[0].S.x, rays[0].S.y, rays[0].S.z };
    Vector3ld v1 { rays[1].S.x, rays[1].S.y, rays[1].S.z };
    Vector3ld v2 { rays[2].S.x, rays[2].S.y, rays[2].S.z };

    
    // 618534564836945 <- too high
    // 618534564836936 <- too low
    // 618534564836937 (not right)
    // 618534564836938 (not right)
    // 618534564836939 (not right)
    // 618534564836940 (not right)
    // 618534564836941 (not right)
    // 618534564836942
    // 618534564836943
    // 618534564836944 (not right)
    // 618534564836936
    // 618534564836937
    
    
    
    MatrixXld M(6, 6);
    VectorXld RHS(6);
    
    M.block<3, 3>(0, 0) = crossMatrix(v0) - crossMatrix(v1);
    M.block<3, 3>(0, 3) = -crossMatrix(p0) + crossMatrix(p1);
    M.block<3, 3>(3, 0) = crossMatrix(v0) - crossMatrix(v2);
    M.block<3, 3>(3, 3) = -crossMatrix(p0) + crossMatrix(p2);
    
    RHS.segment<3>(0) =  -p0.cross(v0) + p1.cross(v1);
    RHS.segment<3>(3) =  -p0.cross(v0) + p2.cross(v2);
    
    result = M.inverse().cast<long double>()*RHS;
    
    long double sum = 0;
    for (int i = 0; i < 3; i++)
    {
        sum += result[i];
    }
    
   printf("Value of long double d = %Lf\n",sum);
    
    // Sum of x,y,z coordinates of initial position of rock that is thrown
    // Round to nearest integer since solution must be integer
    return static_cast<long long>(sum + 0.5);
};

ll numIntersectionsTestAreaPart1()
{
    ifstream hailstoneTrajectories("./day-24/day24input.txt");
    
    ld testMin { 200000000000000 };
    ld testMax { 400000000000000 };
    
    // Stores the rays as start pos and velocity (2 points)
    vector<ray> rays { };
    
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
    
    
    vector<Point> rayIntersections { };
    
    for (int i { 0 }; i < rays.size(); ++i)
    {
        for (int j { i + 1 }; j < rays.size(); ++j)
        {
            Point rayIntersectionPoint { rayIntersectingRay(rays[i].F, rays[i].S, rays[j].F, rays[j].S) };
            
            rayIntersections.push_back(rayIntersectionPoint);
            
        }
    }
        
        
    ll validIntersectCount { 0 };
    
    
    for (const auto& p : rayIntersections)
    {
        if (p.x >= testMin && p.x <= testMax && p.y >= testMin && p.y <= testMax)
        {
            validIntersectCount++;
        }
    }
    
    
    return validIntersectCount;
}

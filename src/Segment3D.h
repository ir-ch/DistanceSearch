#ifndef SEGMENT3D_H
#define SEGMENT3D_H

#include "Point3D.h"

class Segment3D
{
public:
    // Constructor
    Segment3D(Point3D aPointOne, Point3D aPointTwo);

    // Get first point
    Point3D &GetFirstPoint();

    // Get second point
    Point3D &GetSecondPoint();

    // Operator for checking equality of two segments
    bool operator==(const Segment3D &aSegment) const;

private:
    Point3D myFirstPoint;  // First point
    Point3D mySecondPoint; // Second point
};

#endif // SEGMENT3D_H

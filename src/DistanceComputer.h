#ifndef DISTANCECOMPUTER_H
#define DISTANCECOMPUTER_H

#include <vector>

#include "Segment3D.h"
#include "Vector3D.h"

using namespace std;

// Class for storing points of convex polygon
class DistanceComputer
{
public:
    // Constructor
    DistanceComputer();

    // Add node
    void AddSegment(const Segment3D &aSegment);

    // Get all nodes
    const vector<Segment3D> &GetSegments();

    void ComputeDistance();

    const double Result() const;

private:
    // Find vector from point of first line to point of second line
    Vector3D findM1M2Vector();

    // Find direction vectors for lines
    void findVectors();

    // Find length of segment
    double findSegmentLength(Point3D &aFPoint, Point3D &aSPoint);

private:
    double myDistance;
    vector<Vector3D> myVectors;
    vector<Segment3D> mySegments;
};

#endif // DISTANCECOMPUTER_H

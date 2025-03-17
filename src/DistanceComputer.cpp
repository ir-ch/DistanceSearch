#include "DistanceComputer.h"

#include <algorithm>
#include <cmath>
#include <iostream>

DistanceComputer::DistanceComputer()
    : myDistance(0.0)
{
}

void DistanceComputer::AddSegment(const Segment3D &aSegment)
{
    mySegments.push_back(aSegment);
}

const vector<Segment3D> &DistanceComputer::GetSegments()
{
    return mySegments;
}

void DistanceComputer::ComputeDistance()
{
    if (mySegments[0] == mySegments[1])
    {
        return;
    }

    findVectors();

    // Check relative position of lines
    // Calculate vector M1M2
    Vector3D aM1M2 = findM1M2Vector();
    // Find mixed product of the vectors
    double aMixedProduct = myVectors[0].GetX() * (myVectors[1].GetY() * aM1M2.GetZ() - myVectors[1].GetZ() * aM1M2.GetY()) -
                           myVectors[1].GetX() * (myVectors[0].GetY() * aM1M2.GetZ() - myVectors[0].GetZ() * aM1M2.GetY()) +
                           aM1M2.GetX() * (myVectors[0].GetY() * myVectors[1].GetZ() - myVectors[1].GetY() * myVectors[0].GetZ());

    if (aMixedProduct != 0)
    {
        // Case for skew lines
        double i = myVectors[0].GetY() * myVectors[1].GetZ() - myVectors[1].GetY() * myVectors[0].GetZ();
        double j = -1 * (myVectors[0].GetX() * myVectors[1].GetZ() - myVectors[1].GetX() * myVectors[0].GetZ());
        double k = myVectors[0].GetX() * myVectors[1].GetY() - myVectors[1].GetX() * myVectors[0].GetY();

        myDistance = fabs(aMixedProduct) / (sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2)));
    }
    else
    {
        // Check coplanarity of vectors
        double aLymbda1 = myVectors[0].GetX() / myVectors[1].GetX();
        double aLymbda2 = myVectors[0].GetY() / myVectors[1].GetY();
        double aLymbda3 = myVectors[0].GetZ() / myVectors[1].GetZ();
        if (aLymbda1 == aLymbda2 == aLymbda3)
        {
            double aX = (mySegments[0].GetFirstPoint().GetX() - mySegments[1].GetFirstPoint().GetX()) / myVectors[1].GetX();
            double anY = (mySegments[0].GetFirstPoint().GetY() - mySegments[1].GetFirstPoint().GetY()) / myVectors[1].GetY();
            double aZ = (mySegments[0].GetFirstPoint().GetZ() - mySegments[1].GetFirstPoint().GetZ()) / myVectors[1].GetZ();
            if (aX == anY && anY == aZ)
            {
                // Matching lines
                double aLengthAC = findSegmentLength(mySegments[1].GetFirstPoint(), mySegments[0].GetFirstPoint());
                double aLengthAD = findSegmentLength(mySegments[1].GetSecondPoint(), mySegments[0].GetFirstPoint());
                double aLengthBC = findSegmentLength(mySegments[1].GetFirstPoint(), mySegments[0].GetSecondPoint());
                double aLengthBD = findSegmentLength(mySegments[1].GetSecondPoint(), mySegments[0].GetSecondPoint());

                double aMinLen = min({aLengthAC, aLengthAD, aLengthBC, aLengthBD});
                double aMaxLen = max({aLengthAC, aLengthAD, aLengthBC, aLengthBD});

                double aLengthAB = findSegmentLength(mySegments[0].GetFirstPoint(), mySegments[0].GetSecondPoint());
                double aLengthCD = findSegmentLength(mySegments[1].GetFirstPoint(), mySegments[1].GetSecondPoint());

                if (aLengthAB + aLengthCD + aMinLen > aMaxLen)
                {
                    // Overlapping segments
                    myDistance = 0;
                }
                else
                {
                    myDistance = aMinLen;
                }
            }
            else
            {
                // Parallel lines
                Vector3D aM2M1Vec(mySegments[0].GetFirstPoint().GetX() - mySegments[1].GetFirstPoint().GetX(),
                                  mySegments[0].GetFirstPoint().GetY() - mySegments[1].GetFirstPoint().GetY(),
                                  mySegments[0].GetFirstPoint().GetZ() - mySegments[1].GetFirstPoint().GetZ());

                // Find cross product of vectors
                double i = myVectors[1].GetY() * aM2M1Vec.GetZ() - myVectors[1].GetZ() * aM2M1Vec.GetY();
                double j = -1 * (myVectors[1].GetX() * aM2M1Vec.GetZ() - myVectors[1].GetZ() * aM2M1Vec.GetX());
                double k = myVectors[1].GetX() * aM2M1Vec.GetY() - myVectors[1].GetY() * aM2M1Vec.GetX();

                myDistance = sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2)) /
                             sqrt(pow(myVectors[1].GetX(), 2) + pow(myVectors[1].GetY(), 2) + pow(myVectors[1].GetZ(), 2));
            }
        }
        else // Intersecting lines case
        {
            // Left side coefficients
            double aT1 = myVectors[0].GetX();
            double aT2 = myVectors[0].GetY();
            double aT3 = myVectors[0].GetZ();

            // Right side coefficients
            double aS1 = myVectors[1].GetX();
            double aS2 = myVectors[1].GetY();
            double aS3 = myVectors[1].GetZ();

            // Free coefficients for right side
            double aFreeX = mySegments[1].GetFirstPoint().GetX() - mySegments[0].GetFirstPoint().GetX();
            double aFreeY = mySegments[1].GetFirstPoint().GetY() - mySegments[0].GetFirstPoint().GetY();
            double aFreeZ = mySegments[1].GetFirstPoint().GetZ() - mySegments[0].GetFirstPoint().GetZ();

            // Express t coefficient from first equality
            double aNewS1 = aS1 / aT1;
            double aNewFreeX = aFreeX / aT1;
            // And use these values for next equality to find s parameter
            double aS = (aFreeY - aNewFreeX) / (aNewS1 - aS2);
            double aT = aS * aNewS1 + aNewFreeX;

            // Point of intersection
            Point3D aM(myVectors[0].GetX() * aT + mySegments[0].GetFirstPoint().GetX(),
                       myVectors[0].GetY() * aT + mySegments[0].GetFirstPoint().GetY(),
                       myVectors[0].GetZ() * aT + mySegments[0].GetFirstPoint().GetZ());

            double aLengthAB = findSegmentLength(mySegments[0].GetFirstPoint(), mySegments[0].GetSecondPoint());
            double aLengthCD = findSegmentLength(mySegments[1].GetFirstPoint(), mySegments[1].GetSecondPoint());

            double aLengthAM = findSegmentLength(mySegments[0].GetFirstPoint(), aM);
            double aLengthBM = findSegmentLength(mySegments[0].GetSecondPoint(), aM);
            double aLengthCM = findSegmentLength(mySegments[1].GetFirstPoint(), aM);
            double aLengthDM = findSegmentLength(mySegments[1].GetSecondPoint(), aM);

            if ((aLengthAM + aLengthBM) == aLengthAB && (aLengthCM + aLengthDM) == aLengthCD)
            {
                myDistance = 0;
            }
            else if ((aLengthAM + aLengthBM) == aLengthAB)
            {
                myDistance = min(aLengthCM, aLengthDM);
            }
            else if ((aLengthCM + aLengthDM) == aLengthCD)
            {
                myDistance = min(aLengthAM, aLengthBM);
            }
            else
            {
                double aLengthAC = findSegmentLength(mySegments[1].GetFirstPoint(), mySegments[0].GetFirstPoint());
                double aLengthAD = findSegmentLength(mySegments[1].GetSecondPoint(), mySegments[0].GetFirstPoint());
                double aLengthBC = findSegmentLength(mySegments[1].GetFirstPoint(), mySegments[0].GetSecondPoint());
                double aLengthBD = findSegmentLength(mySegments[1].GetSecondPoint(), mySegments[0].GetSecondPoint());

                myDistance = min({aLengthAC, aLengthAD, aLengthBC, aLengthBD});
            }
        }
    }
}

const double DistanceComputer::Result() const
{
    return myDistance;
}

Vector3D DistanceComputer::findM1M2Vector()
{
    return Vector3D(mySegments[1].GetFirstPoint().GetX() - mySegments[0].GetFirstPoint().GetX(),
                    mySegments[1].GetFirstPoint().GetY() - mySegments[0].GetFirstPoint().GetY(),
                    mySegments[1].GetFirstPoint().GetZ() - mySegments[0].GetFirstPoint().GetZ());
}

void DistanceComputer::findVectors()
{
    Vector3D aFirstVector(mySegments[0].GetSecondPoint().GetX() - mySegments[0].GetFirstPoint().GetX(),
                          mySegments[0].GetSecondPoint().GetY() - mySegments[0].GetFirstPoint().GetY(),
                          mySegments[0].GetSecondPoint().GetZ() - mySegments[0].GetFirstPoint().GetZ());

    Vector3D aSecondVector(mySegments[1].GetSecondPoint().GetX() - mySegments[1].GetFirstPoint().GetX(),
                           mySegments[1].GetSecondPoint().GetY() - mySegments[1].GetFirstPoint().GetY(),
                           mySegments[1].GetSecondPoint().GetZ() - mySegments[1].GetFirstPoint().GetZ());

    myVectors.push_back(aFirstVector);
    myVectors.push_back(aSecondVector);
}

double DistanceComputer::findSegmentLength(Point3D &aFPoint, Point3D &aSPoint)
{
    return sqrt(pow(aFPoint.GetX() - aSPoint.GetX(), 2) +
                pow(aFPoint.GetY() - aSPoint.GetY(), 2) +
                pow(aFPoint.GetZ() - aSPoint.GetZ(), 2));
}

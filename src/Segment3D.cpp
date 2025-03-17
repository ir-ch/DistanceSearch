#include "Segment3D.h"

Segment3D::Segment3D(Point3D aPointOne, Point3D aPointTwo)
    : myFirstPoint(aPointOne),
      mySecondPoint(aPointTwo)
{
}

Point3D &Segment3D::GetFirstPoint()
{
    return myFirstPoint;
}

Point3D &Segment3D::GetSecondPoint()
{
    return mySecondPoint;
}

bool Segment3D::operator==(const Segment3D &aSegment) const
{
    return (this->myFirstPoint == aSegment.myFirstPoint && this->mySecondPoint == aSegment.mySecondPoint) ||
           (this->myFirstPoint == aSegment.mySecondPoint && this->mySecondPoint == aSegment.myFirstPoint);
}

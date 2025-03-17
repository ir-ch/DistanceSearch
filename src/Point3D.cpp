#include <iostream>

#include "Point3D.h"

Point3D::Point3D()
    : my_x(0.0),
      my_y(0.0),
      my_z(0.0)
{
}

Point3D::Point3D(double aX, double anY, double aZ)
    : my_x(aX),
      my_y(anY),
      my_z(aZ)
{
}

const double Point3D::GetX()
{
    return my_x;
}

void Point3D::SetX(const double aX)
{
    my_x = aX;
}

const double Point3D::GetY()
{
    return my_y;
}

void Point3D::SetY(const double aY)
{
    my_y = aY;
}

const double Point3D::GetZ()
{
    return my_z;
}

void Point3D::SetZ(const double aZ)
{
    my_z = aZ;
}

bool Point3D::operator==(const Point3D &aPoint) const
{
    return this->my_x == aPoint.my_x && this->my_y == aPoint.my_y && this->my_z == aPoint.my_z;
}

#include "Vector3D.h"

Vector3D::Vector3D(double aX, double anY, double aZ)
    : my_x(aX),
      my_y(anY),
      my_z(aZ)
{
}

const double Vector3D::GetX()
{
    return my_x;
}

const double Vector3D::GetY()
{
    return my_y;
}

const double Vector3D::GetZ()
{
    return my_z;
}

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Point3D.h"

class Vector3D
{
public:
    Vector3D(double aX, double anY, double aZ);

    // Get X coordinate
    const double GetX();

    // Get Y coordinate
    const double GetY();

    // Get Z coordinate
    const double GetZ();

private:
    double my_x;
    double my_y;
    double my_z;
};

#endif // VECTOR3D_H

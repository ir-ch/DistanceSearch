#ifndef POINT3D_H
#define POINT3D_H

// Class for storing 3D coordinate
class Point3D
{
public:
    // Constructor
    Point3D();

    // Constructor with parameters
    Point3D(double aX, double anY, double aZ);

    // Get X coordinate
    const double GetX();

    // Set X coordinate
    void SetX(const double aX);

    // Get Y coordinate
    const double GetY();

    // Set Y coordinate
    void SetY(const double aY);

    // Get Z coordinate
    const double GetZ();

    // Set Z coordinate
    void SetZ(const double aZ);

    // Operator for checking equality of two points
    bool operator==(const Point3D &aPoint) const;

private:
    double my_x; // X coordinate
    double my_y; // Y coordinate
    double my_z; // Z coordinate
};

#endif // POINT3D_H

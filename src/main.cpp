#include <iostream>
#include <fstream>

#include "DistanceComputer.h"

using namespace std;

namespace Tests
{
    void Test_1()
    {
        // Intersecting lines
        DistanceComputer aComputer;
        Segment3D aFirstSegment(Point3D(3, -3, 2), Point3D(2, -2, 4));
        Segment3D aSecondSegment(Point3D(-1, 4, -26), Point3D(2, 0, -20));
        aComputer.AddSegment(aFirstSegment);
        aComputer.AddSegment(aSecondSegment);
        aComputer.ComputeDistance();
        cout << "Test case 1: ";
        if (aComputer.Result() - 22.226 < 0.01)
        {
            cout << "OK" << endl;
        }
        else
        {
            cout << "Fault" << endl;
        }
    }

    void Test_2()
    {
        // Skew lines
        DistanceComputer aComputer;
        Segment3D aFirstSegment(Point3D(2, -1, 0), Point3D(4, -4, -1));
        Segment3D aSecondSegment(Point3D(-1, 0, 1), Point3D(0, -2, 1));
        aComputer.AddSegment(aFirstSegment);
        aComputer.AddSegment(aSecondSegment);
        aComputer.ComputeDistance();
        cout << "Test case 2: ";
        if (aComputer.Result() - 1.63 < 0.01)
        {
            cout << "OK" << endl;
        }
        else
        {
            cout << "Fault" << endl;
        }
    }

    void Test_3()
    {
        // Equal segments
        DistanceComputer aComputer;
        Segment3D aFirstSegment(Point3D(2, 1, 0), Point3D(4, 0, -1));
        Segment3D aSecondSegment(Point3D(4, 0, -1), Point3D(2, 1, 0));
        aComputer.AddSegment(aFirstSegment);
        aComputer.AddSegment(aSecondSegment);
        aComputer.ComputeDistance();
        cout << "Test case 3: ";
        if (aComputer.Result() == 0.0)
        {
            cout << "OK" << endl;
        }
        else
        {
            cout << "Fault" << endl;
        }
    }

    void Test_4()
    {
        // Segments on parallel lines
        DistanceComputer aComputer;
        Segment3D aFirstSegment(Point3D(-4, -5, 6), Point3D(-6, -1, 12));
        Segment3D aSecondSegment(Point3D(0, 1, -3), Point3D(1, -1, -6));
        aComputer.AddSegment(aFirstSegment);
        aComputer.AddSegment(aSecondSegment);
        aComputer.ComputeDistance();
        cout << "Test case 4: ";
        if (aComputer.Result() - 11.53 < 0.01)
        {
            cout << "OK" << endl;
        }
        else
        {
            cout << "Fault" << endl;
        }
    }

    void Test_5()
    {
        // Overlapping segments on the same line
        DistanceComputer aComputer;
        Segment3D aFirstSegment(Point3D(1, 2, 3), Point3D(5, 6, 7));
        Segment3D aSecondSegment(Point3D(3, 4, 5), Point3D(7, 8, 9));
        aComputer.AddSegment(aFirstSegment);
        aComputer.AddSegment(aSecondSegment);
        aComputer.ComputeDistance();
        cout << "Test case 5: ";
        if (aComputer.Result() == 0.0)
        {
            cout << "OK" << endl;
        }
        else
        {
            cout << "Fault" << endl;
        }
    }

    void Test_6()
    {
        // Segments on the same line
        DistanceComputer aComputer;
        Segment3D aFirstSegment(Point3D(1, 2, 3), Point3D(5, 6, 7));
        Segment3D aSecondSegment(Point3D(9, 10, 11), Point3D(13, 14, 15));
        aComputer.AddSegment(aFirstSegment);
        aComputer.AddSegment(aSecondSegment);
        aComputer.ComputeDistance();
        cout << "Test case 6: ";
        if (aComputer.Result() - 6.92 < 0.01)
        {
            cout << "OK" << endl;
        }
        else
        {
            cout << "Fault" << endl;
        }
    }

    void Test()
    {
        Test_1();
        Test_2();
        Test_3();
        Test_4();
        Test_5();
        Test_6();
    }
}

int main(int anArgc, char *anArgv[])
{
    if (anArgc < 2)
    {
        return 1;
    }

    if (string(anArgv[1]) == "test")
    {
        Tests::Test();
        return 0;
    }

    DistanceComputer aComputer;
    ifstream aFStream(anArgv[1]);
    if (!aFStream.is_open())
    {
        cout << "Error: file was not opened." << endl;
        return 1;
    }

    string aLine;
    vector<Point3D> aPointVec;
    while (getline(aFStream, aLine))
    {
        double aX = 0, anY = 0, aZ = 0;
        int aCount = 0;
        int aPrevIter = 0;
        for (int anIter = 0; anIter != aLine.size(); ++anIter)
        {
            if (aLine[anIter] == ' ')
            {
                if (aCount == 0)
                {
                    aX = atof(aLine.substr(aPrevIter, anIter).c_str());
                }
                else if (aCount == 1)
                {
                    anY = atof(aLine.substr(aPrevIter, anIter).c_str());
                }
                ++aCount;
                aPrevIter = anIter;
            }
            if (anIter == aLine.size() - 1)
            {
                aZ = atof(aLine.substr(aPrevIter, anIter).c_str());
            }
        }
        aPointVec.push_back(Point3D(aX, anY, aZ));
        if (aPointVec.size() == 2)
        {
            aComputer.AddSegment(Segment3D(aPointVec[0], aPointVec[1]));
            aPointVec.clear();
        }
    }
    aFStream.close();

    if (aComputer.GetSegments().size() != 2)
    {
        cout << "Wrong data." << endl;
        return 1;
    }
    aComputer.ComputeDistance();
    cout << "Distance: " << aComputer.Result() << endl;

    return 0;
}

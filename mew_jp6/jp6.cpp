// jp.cpp 2013-10-31

#include <iostream>
#include <stdio.h>
#include <assert.h>

#include "jp_dem.h"

/////////////////////////////////////////////////////////////////////////////

static const double X_SCALE = 1.0;
static const double X_OFFSET = 0.0;

static const double Y_SCALE = 1.0;
static const double Y_OFFSET = 0.0;

static const double Z_SCALE = 1.5;
static const double Z_OFFSET = 1.0;

static const double TEXTURE_SCALE = 1.0 / (NED13_SIZE_X-1);
//static const double TEXTURE_SCALE = 1.0 / (NED13_SIZE_Y-1);

/////////////////////////////////////////////////////////////////////////////

class Point
{
public:
    Point( int x, int y )
    {
        _u = x * TEXTURE_SCALE;
        _v = y * TEXTURE_SCALE;

        //x = (NED13_SIZE_X-1 - x );
        y = (NED13_SIZE_Y-1 - y );
        const int i( y * NED13_SIZE_X + x );

        const double* p( &NED13_DATA[i*3] );
        _x = (p[0] - NED13_X_MIN) * X_SCALE + X_OFFSET;
        _y = (p[1] - NED13_Y_MIN) * Y_SCALE + Y_OFFSET;
        _z = (p[2] - NED13_Z_MIN) * Z_SCALE + Z_OFFSET;
    }

    void printXYZ() const
    {
        std::cout
            << "  " << _x
            << "  " << _y
            << "  " << _z
            << std::endl;
    }
    void printUV() const
    {
        std::cout
            << "  " << _u
            << "  " << _v
            << std::endl;
    }

protected:
    double _x, _y, _z;
    double _u, _v;

};


/////////////////////////////////////////////////////////////////////////////

static int writeOSG()
{
    assert(sizeof( NED13_DATA ) == (NED13_SIZE_X * NED13_SIZE_Y * 3 * sizeof(double)));

    std::cout
        << "PrimitiveSets " << (NED13_SIZE_Y-2)/2
        << "\n{"
        << std::endl;
    int start(0);
    int len( (NED13_SIZE_X/2) * 2 );
    for( int y(0); y < (NED13_SIZE_Y-2); y+=2 )
    {
        std::cout
            << "DrawArrays TRIANGLE_STRIP "
            << start
            << " " << len
            << std::endl;
	start += len;
    }
    std::cout << "}\n" << std::endl;

    std::cout
        << "VertexArray Vec3Array "
        << (NED13_SIZE_X * NED13_SIZE_Y * 2)/2
        << "\n{"
        << std::endl;
    for( int y(0); y < NED13_SIZE_Y-2; y+=2 )
    {
        for( int x(0); x < NED13_SIZE_X-1; x+=2 )
        {
            Point(x,y+2).printXYZ();
            Point(x,y).printXYZ();
        }
    }
    std::cout << "}\n" << std::endl;

    std::cout
        << "NormalBinding OVERALL\n"
        << "NormalArray Vec3Array 1\n"
        << "{\n"
        << "  0 0 1\n"
        << "}\n"
        << std::endl;

    std::cout
        << "ColorBinding OVERALL\n"
        << "ColorArray Vec4Array 1\n"
        << "{\n"
        << "  1 1 1 1\n"
        << "}\n"
        << std::endl;

    std::cout
        << "TexCoordArray 0 Vec2Array "
        << (NED13_SIZE_X * NED13_SIZE_Y * 2)/2
        << "\n{"
        << std::endl;
    for( int y(0); y < NED13_SIZE_Y-2; y+=2 )
    {
        for( int x(0); x < NED13_SIZE_X-1; x+=2 )
        {
            Point(x,y+2).printUV();
            Point(x,y).printUV();
        }
    }
    std::cout << "}\n" << std::endl;

    return 0;
}

/////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[] )
{
    return writeOSG();
}

//EOF

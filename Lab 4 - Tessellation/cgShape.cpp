//
//  cgShape
//
//  Routines for tessellating a number of basic shapes.
//
//  Students are to supply their implementations for the functions in
//  this file using the function "addTriangle()" to do the tessellation.
//
//  This code can be compiled as either C or C++.
//
//  Contributor:  YOUR_NAME_HERE
//

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <Windows.h>
#include <GL/gl.h>
#endif

#include "simpleShape.h"
#include <math.h>


///
// makeCube - Create a unit cube, centered at the origin, with a given number
// of subdivisions in each direction on each face.
//
// @param subdivision - number of equal subdivisons to be made in each
//        direction along each face
//
// Can only use calls to addTriangle()
///
void makeCube (int subdivisions)
{
    if( subdivisions < 1 )
        subdivisions = 1;

    // YOUR IMPLEMENTATION HERE
}


///
// makeCylinder - Create polygons for a cylinder with unit height, centered at
// the origin, with separate number of radial subdivisions and height
// subdivisions.
//
// @param radius - Radius of the base of the cylinder
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to addTriangle()
///
void makeCylinder (float radius, int radialDivisions, int heightDivisions)
{
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    // YOUR IMPLEMENTATION HERE

}


///
// makeCone - Create polygons for a cone with unit height, centered at the
// origin, with separate number of radial subdivisions and height
// subdivisions
//
// @param radius - Radius of the base of the cone
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to addTriangle()
///
void makeCone (float radius, int radialDivisions, int heightDivisions)
{
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    // YOUR IMPLEMENTATION HERE

}


///
// makeSphere - Create sphere of a given radius, centered at the origin,
// using spherical coordinates with separate number of thetha and
// phi subdivisions.
//
// @param radius - Radius of the sphere
// @param slides - number of subdivisions in the theta direction
// @param stacks - Number of subdivisions in the phi direction.
//
// Can only use calls to addTriangle
///
void makeSphere (float radius, int slices, int stacks)
{
    // IF USING RECURSIVE SUBDIVISION, MODIFY THIS TO USE
    // A MINIMUM OF 1 AND A MAXIMUM OF 5 FOR 'slices'

    if( slices < 3 )
        slices = 3;

    if( stacks < 3 )
        stacks = 3;

    // YOUR IMPLEMENTATION HERE
}

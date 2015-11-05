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

	float step = 1. / (float) subdivisions;
	
	/*
	for a given face, we consider the following points:
	(u0,v1) +---+ (u1,v1)
			|   |
	(u0,v0) +---+ (u1,v0)
	*/

	for (int i = 0; i < subdivisions; i++) {	
		float u0 = (float)i * step - .5;
		float u1 = (float)(i + 1) * step - .5;
		for (int j = 0; j < subdivisions; j++) {
			float v0 = (float)j * step - .5;
			float v1 = (float)(j + 1) * step - .5;
			// face (x,y,-.5) drawn clockwise
			addTriangle(u1, v0, -.5, u0, v0, -.5, u0, v1, -.5);
			addTriangle(u1, v0, -.5, u0, v1, -.5, u1, v1, -.5);
			// face (x,y,.5) drawn counterclockwise
			addTriangle(u0, v0, .5, u1, v0, .5, u0, v1, .5);
			addTriangle(u0, v1, .5, u1, v0, .5, u1, v1, .5);
			// face (-.5,y,z) drawn counterclockwise
			addTriangle(-.5, u0, v1, -.5, u1, v0, -.5, u0, v0);
			addTriangle(-.5, u1, v1, -.5, u1, v0, -.5, u0, v1);
			// face (.5,y,z) drawn clockwise
			addTriangle(.5, u1, v0, .5, u0, v1, .5, u0, v0);
			addTriangle(.5, u1, v0, .5, u1, v1, .5, u0, v1);
			// face (x,-.5,z) drawn clockwise
			addTriangle(u1, -.5, v0, u0, -.5, v1, u0, -.5, v0);
			addTriangle(u1, -.5, v0, u1, -.5, v1, u0, -.5, v1);
			// face (x,.5,z) drawn counterclockwise
			addTriangle(u0, .5, v1, u1, .5, v0, u0, .5, v0);
			addTriangle(u1, .5, v1, u1, .5, v0, u0, .5, v1);
		}
	}
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

	const float PI = 3.14159265358979f;
	float alpha = 0,
		y0 = -.5, y1,
		x0, z0, x1,	z1;
	for (int i = 0; i < radialDivisions; i++) {
		// we compute the coordinates of the triangle MON, 
		// where M(x0,+/-.5,z0), O(0,+/-.5,0) and N(x1,+/-.5,z1)
		x0 = radius * cosf((float)i * 2 * PI / (float)radialDivisions);
		z0 = radius * sinf((float)i * 2 * PI / (float)radialDivisions);
		x1 = radius * cosf((float)(i+1) * 2 * PI / (float)radialDivisions);
		z1 = radius * sinf((float)(i+1) * 2 * PI / (float)radialDivisions);

		// face (x,-.5,z) drawn clockwise
		addTriangle(0., -.5, 0., x0, -.5, z0, x1, -.5, z1);
		// face (x,5,z) drawn counterclockwise
		addTriangle(x1, .5, z1, x0, .5, z0, 0., .5, 0.);

		// draw the rectangles for the height
		for (int j = 0; j < heightDivisions; j++) {
			y0 = (float)(j) / (float)heightDivisions - .5;
			y1 = (float)(j + 1) / (float)heightDivisions -.5;
			addTriangle(x0, y1, z0, x1, y1, z1, x0, y0, z0);
			addTriangle(x1, y1, z1, x1, y0, z1, x0, y0, z0);
		}
	}
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

	const float PI = 3.14159265358979f;
	float alpha = 0,
		y0 = -.5, y1,
		x0, z0, x1, z1;
	for (int i = 0; i < radialDivisions; i++) {
		// we compute the coordinates of the triangle MON, 
		// where M(x0,+/-.5,z0), O(0,+/-.5,0) and N(x1,+/-.5,z1)
		x0 = radius * cosf((float)i * 2 * PI / (float)radialDivisions);
		z0 = radius * sinf((float)i * 2 * PI / (float)radialDivisions);
		x1 = radius * cosf((float)(i + 1) * 2 * PI / (float)radialDivisions);
		z1 = radius * sinf((float)(i + 1) * 2 * PI / (float)radialDivisions);

		// face (x,5,z) drawn counterclockwise
		addTriangle(x1, -.5, z1, x0, -.5, z0, 0., -.5, 0.);

		// draw the rectangles for the height
		for (int j = 0; j < heightDivisions; j++) {
			// if we are at the top of the cone, just draw a triangle
			if (j + 1 >= heightDivisions) {
				addTriangle(x0, -.5, z0, x1, -.5, z1, 0., .5, 0.);
			}
			// else we wanna draw parallelograms
			else {
				y0 = (float)(j) / (float)heightDivisions - .5;
				y1 = (float)(j + 1) / (float)heightDivisions - .5;
				addTriangle(x0, y0, z0, x1, y0, z1, x0, y1, z0);
				addTriangle(x1, y0, z1, x1, y1, z1, x0, y1, z0);
			}
		}
	}

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

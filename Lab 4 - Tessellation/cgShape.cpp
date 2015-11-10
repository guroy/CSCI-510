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
//  Contributor:  Guillaume Roy
//  Contributor:  Gurvan Lecuyer
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
#include "cgShape.h"


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

	for (int i = 0; i < radialDivisions; i++) {
		// we compute the coordinates of the triangle MON, 
		// where M(x0,+/-.5,z0), O(0,+/-.5,0) and N(x1,+/-.5,z1)
		float x0 = radius * cosf(i * 2 * PI / radialDivisions);
		float z0 = radius * sinf(i * 2 * PI / radialDivisions);
		float x1 = radius * cosf((i + 1) * 2 * PI / radialDivisions);
		float z1 = radius * sinf((i + 1) * 2 * PI / radialDivisions);

		// face (x,5,z) drawn counterclockwise
		addTriangle(x0, -0.5, z0, x1, -0.5, z1, 0.0, -0.5, 0.0);

		float y0 = -0.5;
		float cx0 = -x0 / heightDivisions;
		float cz0 = -z0 / heightDivisions;
		float cx1 = -x1 / heightDivisions;
		float cz1 = -z1 / heightDivisions;
		float y1 = 1.0 / heightDivisions;
		// draw the rectangles for the height
		for (int j = 0; j < heightDivisions - 1; j++) {
		// else we wanna draw trapezium			
			addTriangle(x0, y0, z0, x0+cx0, y0+y1, z0+cz0, x1, y0, z1);
			addTriangle(x0+cx0, y0+y1, z0+cz0, x1+cx1, y0+y1, z1+cz1, x1, y0, z1);

			x0 += cx0;
			z0 += cz0;
			x1 += cx1;
			z1 += cz1;
			y0 += y1;
		}

		// when we are at the top of the cone, just draw a triangle
		addTriangle(x0, y0, z0, 0.0, 0.5, 0.0, x1, y0, z1);
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
void makeSphere(float radius, int slices, int stacks)
{
	// IF USING RECURSIVE SUBDIVISION, MODIFY THIS TO USE
	// A MINIMUM OF 1 AND A MAXIMUM OF 5 FOR 'slices'

	if (slices < 1)
		slices = 1;
	if (slices > 5)
		slices = 5;

	if (stacks < 3)
		stacks = 3;

	//define the variabel "a" it's describe in the course
	float a = radius;
	//declaration of the 19 triangles of the icosahedron
	//Triangle0 = <V0,V1,V2>
	recursiveTriangle(0, a, -1, -a, 1, 0, a, 1, 0, slices, radius);
	//Triangle1 = <V3, V2, V1>
	recursiveTriangle(0, a, 1, a, 1, 0, -a, 1, 0, slices, radius);
	//Triangle2 = <V3, V4, V5>
	recursiveTriangle(0, a, 1, -1, 0, a, 0, -a, 1, slices, radius);
	//Triangle3 = <V3, V5, V6>
	recursiveTriangle(0, a, 1, 0, -a, 1, 1, 0, a, slices, radius);
	//Triangle4 = <V0, V7, V8>
	recursiveTriangle(0, a, -1, 1, 0, -a, 0, -a, -1, slices, radius);
	//Triangle5 = <V0, V8, V9>
	recursiveTriangle(0, a, -1, 0, -a, -1, -1, 0, -a, slices, radius);
	//Triangle6 = <V5, V10, V11>
	recursiveTriangle(0, -a, 1, -a, -1, 0, a, -1, 0, slices, radius);
	//Triangle7 = <V8, V11, V10>
	recursiveTriangle(0, -a, -1, a, -1, 0, -a, -1, 0, slices, radius);
	//Triangle8 = <V1, V9, V4>
	recursiveTriangle(-a, 1, 0, -1, 0, -a, -1, 0, a, slices, radius);
	//Triangle9 = <V10, V4, V9>
	recursiveTriangle(-a, -1, 0, -1, 0, a, -1, 0, -a, slices, radius);
	//Triangle10 = <V2, V6, V7>
	recursiveTriangle(a, 1, 0, 1, 0, a, 1, 0, -a, slices, radius);
	//Triangle11 = <V11, V7, V6>
	recursiveTriangle(a, -1, 0, 1, 0, -a, 1, 0, a, slices, radius);
	//Triangle12 = <V3, V1, V4>
	recursiveTriangle(0, a, 1, -a, 1, 0, -1, 0, a, slices, radius);
	//Triangle13 = <V3, V6, V2>
	recursiveTriangle(0, a, 1, 1, 0, a, a, 1, 0, slices, radius);
	//Triangle14 = <V0, V9, V1>
	recursiveTriangle(0, a, -1, -1, 0, -a, -a, 1, 0, slices, radius);
	//Triangle15 = <V0, V2, V7>
	recursiveTriangle(0, a, -1, a, 1, 0, 1, 0, -a, slices, radius);
	//Triangle16 = <V8, V10, V9>
	recursiveTriangle(0, -a, -1, -a, -1, 0, -1, 0, -a, slices, radius);
	//Triangle17 = <V8, V7, V11>
	recursiveTriangle(0, -a, -1, 1, 0, -a, a, -1, 0, slices, radius);
	//Triangle18 = <V5, V4, V10>
	recursiveTriangle(0, -a, 1, -1, 0, a, -a, -1, 0, slices, radius);
	//Triangle19 = <V5, V11, V6>
	recursiveTriangle(0, -a, 1, a, -1, 0, 1, 0, a, slices, radius);
}

void recursiveTriangle(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, int subdivision, float radius)
{
	if (subdivision == 1)
	{
		//Normalization of the point 0
		float norm0 = pow((pow(x0, 2) + pow(y0, 2) + pow(z0, 2)), 0.5f);
		x0 = (x0 / norm0) * radius;
		y0 = (y0 / norm0) * radius;
		z0 = (z0 / norm0) * radius;
		//Normalization of the point 1
		float norm1 = pow((pow(x1, 2) + pow(y1, 2) + pow(z1, 2)), 0.5f);
		x1 = (x1 / norm1) * radius;
		y1 = (y1 / norm1) * radius;
		z1 = (z1 / norm1) * radius;
		//Normalization of the point 2
		float norm2 = pow((pow(x2, 2) + pow(y2, 2) + pow(z2, 2)), 0.5f);
		x2 = (x2 / norm2) * radius;
		y2 = (y2 / norm2) * radius;
		z2 = (z2 / norm2) * radius;
		addTriangle(x0, y0, z0, x1, y1, z1, x2, y2, z2);
	}
	else
	{
		//Calculate the point on the middle of the edge point0 - point1
		float midx01 = (x0 + x1) / 2.;
		float midy01 = (y0 + y1) / 2.;
		float midz01 = (z0 + z1) / 2.;

		//Calculate the point on the middle of the edge point1 - point2
		float midx12 = (x1 + x2) / 2.;
		float midy12 = (y1 + y2) / 2.;
		float midz12 = (z1 + z2) / 2.;

		//Calculate the point on the middle of the edge point2 - point0
		float midx20 = (x0 + x2) / 2.;
		float midy20 = (y0 + y2) / 2.;
		float midz20 = (z0 + z2) / 2.;

		//Call 4 times (1 call per sub triangles created) the recursiveTriangle method with subdivision-1,
		recursiveTriangle(x0, y0, z0, midx01, midy01, midz01, midx20, midy20, midz20, (subdivision - 1), radius);
		recursiveTriangle(midx01, midy01, midz01, midx12, midy12, midz12, midx20, midy20, midz20, (subdivision - 1), radius);
		recursiveTriangle(midx01, midy01, midz01, x1, y1, z1, midx12, midy12, midz12, (subdivision - 1), radius);
		recursiveTriangle(midx20, midy20, midz20, midx12, midy12, midz12, x2, y2, z2, (subdivision - 1), radius);
	}
}

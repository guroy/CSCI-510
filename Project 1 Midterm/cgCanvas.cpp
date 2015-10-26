//
//  cgCanvas.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Guillaume Roy
//

#include "cgCanvas.h"
#include "Rasterizer.h"
#include "clipper.h"
#include "cmatrix"


// We may want use a typedef statement to simplify the declaration of matrix objects in the program. 
typedef techsoft::matrix<float> Matrix;

///
// Simple wrapper class for midterm assignment
//
// Only methods in the implementation file whose bodies
// contain the comment
//
//    // YOUR IMPLEMENTATION HERE
//
// are to be modified by students.
///

int cgCanvas::polyID = 0; // we set the polyID to zero first.

///
// Constructor
//
// @param w - width of canvas
// @param h - height of canvas
///

cgCanvas::cgCanvas(int w, int h) : simpleCanvas (w,h)
{
    // YOUR IMPLEMENTATION HERE if you need to modify the constructor
	clearTransform(); // by default we set the transformation matrix to ID
}

///
// addPoly - Add a polygon to the canvas.  This method does not draw
//           the polygon, but merely stores it for later drawing.
//           Drawing is initiated by the drawPoly() method.
//
//           Returns a unique integer id for the polygon.
//
// @param x - Array of x coords of the vertices of the polygon to be added
// @param y - Array of y coords of the vertices of the polygon to be added
// @param n - Number of verticies in polygon
//
// @return a unique integer identifier for the polygon
///

int cgCanvas::addPoly (const float x[], const float y[], int n)
{
    // YOUR IMPLEMENTATION HERE
	// sf::ConvexShape & sf::Vector2 are 2 objects of the SFML library
	sf::ConvexShape newPoly = sf::ConvexShape(n); // Create a Polygon
	for (int i = 0; i < n; i++) {
		newPoly.setPoint(i, sf::Vector2<float>(x[i], y[i])); // Set the vertices, vertex by vertex
	}

	polys.push_back(newPoly); // add the new polygon to the vector of polygons contained in simpleCanvas

    // REMEMBER TO RETURN A UNIQUE ID FOR THE POLYGON
	return polyID++;
}

///
// drawPoly - Draw the polygon with the given id.  The polygon should
//            be drawn after applying the current transformation to
//            the vertices of the polygon.
//
// @param polyID - the ID of the polygon to be drawn
///

void cgCanvas::drawPoly(int polyID)
{
	// YOUR IMPLEMENTATION HERE
	// We want to use the method void drawPolygon(int n, int x[], int y[], simpleCanvas &C);
	// contained in the Rasterizer class. So we need to create a rasterizer, and set n, x, y and C values.

	// set n
	int n = polys.at(polyID).getPointCount();


	// set inx[] and iny[] and apply transformation
	float *inx = new float[n],
		  *iny = new float[n];

	Matrix m;
	sf::Vector2<float> coord;

	for (int i = 0; i < n; i++) {
		coord = sf::Vector2<float>(polys.at(polyID).getPoint(i));
		// compute the coordinates of the point after the transformation
		m = Matrix(3, 1, { coord.x, coord.y, 1 });
		m = currentTransform * m;
		inx[i] = m[0][0];
		iny[i] = m[1][0];
	}

	// set in
	int in = polys.at(polyID).getPointCount();

	// set outx[] and outy[]
	float *outx = new float[in],
		  *outy = new float[in];

	clipper clip;
	// clip
	n = clip.clipPolygon(in, inx, iny, outx, outy, clipWindow[2], clipWindow[0], clipWindow[3], clipWindow[1]);

	delete[] inx, iny; // dynamic allocation

	// object that contain the drawPolygon
	Rasterizer rast = Rasterizer(n);

	int *x = new int[n],
		*y = new int[n];

	/*
	VXmin = x;
	VXmax = width;
	VYmin = y;
	VYmax = height;*/
	for (int i = 0; i < n; i++) {
		m = Matrix(3, 1, { outx[i], outy[i], 1 });
		// let's normalize !
		float x_normalized = ((m[0][0] - clipWindow[2]) / (clipWindow[3] - clipWindow[2])) * viewWindow[2] + viewWindow[0],
		y_normalized = ((m[1][0] - clipWindow[0]) / (clipWindow[1] - clipWindow[0])) * viewWindow[3] + viewWindow[1];
		x[i] = round( x_normalized);
		y[i] = round(y_normalized);
	}

	// draw
	rast.drawPolygon(n, x, y, *this);
	//drawOutline(n, x, y);

	delete [] x, y, outx, outy;
}

///
// clearTransform - Set the current transformation to the identity matrix.
///

void cgCanvas::clearTransform()
{
    // YOUR IMPLEMENTATION HERE
	// the identity
	const float ID[] = { 1, 0, 0,
						 0, 1, 0,
						 0, 0, 1 };

	currentTransform = Matrix(3, 3, ID);
}

///
// translate - Add a translation to the current transformation by
//             premultiplying the appropriate translation matrix to
//             the current transformation matrix.
//
// @param x - Amount of translation in x
// @param y - Amount of translation in y
///

void cgCanvas::translate (float x, float y)
{
    // YOUR IMPLEMENTATION HERE
	// the transformation matrix
	const float TR[] = { 1, 0, x,
						 0, 1, y,
						 0, 0, 1 };

	Matrix translateTransform = Matrix(3, 3, TR);

	// CM = T(x, y) * CM
	currentTransform = translateTransform * currentTransform;
}

///
// rotate - Add a rotation to the current transformation by premultiplying
//          the appropriate rotation matrix to the current transformation
//          matrix.
//
// @param degrees - Amount of rotation in degrees
///

void cgCanvas::rotate (float degrees)
{
    // YOUR IMPLEMENTATION HERE
	// the transformation matrix
	// transform degrees to radian
	float theta = degrees * 3.14159265358979f / 180;
	const float RO[] = { cos(theta), -sin(theta), 0,
						 sin(theta), cos(theta) , 0,
						 0         , 0          , 1 };

	Matrix rotateTransform = Matrix(3, 3, RO);

	// CM = R(theta) * CM
	currentTransform = rotateTransform * currentTransform;
}

///
// scale - Add a scale to the current transformation by premultiplying
//         the appropriate scaling matrix to the current transformation
//         matrix.
//
// @param x - Amount of scaling in x
// @param y - Amount of scaling in y
///

void cgCanvas::scale (float x, float y)
{
    // YOUR IMPLEMENTATION HERE
	// the transformation matrix
	const float SC[] = { x, 0, 0,
						 0, y, 0,
						 0, 0, 1 };

	Matrix scaleTransform = Matrix(3, 3, SC);

	// CM = S(x, y) * CM
	currentTransform = scaleTransform * currentTransform;
}

///
// setClipWindow - Define the clip window.
//
// @param bottom - y coord of bottom edge of clip window (in world coords)
// @param top - y coord of top edge of clip window (in world coords)
// @param left - x coord of left edge of clip window (in world coords)
// @param right - x coord of right edge of clip window (in world coords)
///

void cgCanvas::setClipWindow (float bottom, float top, float left, float right)
{
	clipWindow[0] = bottom;
	clipWindow[1] = top;
	clipWindow[2] = left;
	clipWindow[3] = right;
}

///
// setViewport - Define the viewport.
//
// @param xmin - x coord of lower left of view window (in screen coords)
// @param ymin - y coord of lower left of view window (in screen coords)
// @param width - width of view window (in world coords)
// @param height - width of view window (in world coords)
///

void cgCanvas::setViewport (int x, int y, int width, int height)
{
    // YOUR IMPLEMENTATION HERE
	viewWindow[0] = x;
	viewWindow[1] = y;
	viewWindow[2] = width;
	viewWindow[3] = height;
}

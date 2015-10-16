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

int cgCanvas::polyID = 0;

///
// Constructor
//
// @param w - width of canvas
// @param h - height of canvas
///

cgCanvas::cgCanvas(int w, int h) : simpleCanvas (w,h)
{
    // YOUR IMPLEMENTATION HERE if you need to modify the constructor
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
		newPoly.setPoint(i, sf::Vector2<float>(x[i], y[i])); // Set the vertices
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

void cgCanvas::drawPoly (int polyID)
{
    // YOUR IMPLEMENTATION HERE
	int n = polys.at(polyID).getPointCount();
	int *x = new int[n],
		*y = new int[n];

	sf::Vector2<int> tmpPoint;

	for (int i = 0; i < n; i++) {
		tmpPoint = sf::Vector2<int>(polys.at(polyID).getPoint(i));
		x[i] = tmpPoint.x;
		y[i] = tmpPoint.y;
	}

	Rasterizer rasterizer = Rasterizer(n);

	rasterizer.drawPolygon(n, x, y, *this);

	delete[] x, y;
}

///
// clearTransform - Set the current transformation to the identity matrix.
///

void cgCanvas::clearTransform()
{
    // YOUR IMPLEMENTATION HERE
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
    // YOUR IMPLEMENTATION HERE
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
}

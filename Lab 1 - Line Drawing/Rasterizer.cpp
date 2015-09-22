//
//  Rasterizer.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Guillaume Roy
//

#include "Rasterizer.h"
#include "simpleCanvas.h"
#include <float.h>

///
//
// Simple class that performs rasterization algorithms
//
///

///
// Constructor
//
// @param n number of scanlines
//
///

Rasterizer::Rasterizer (int n) : n_scanlines (n)
{
}

///
// Draw a line from (x0,y0) to (x1, y1) on the simpleCanvas C.
//
// Implementation should be using the Midpoint Method
//
// You are to add the implementation here using only calls
// to C.setPixel()
//
// @param x0 x coord of first endpoint
// @param y0 y coord of first endpoint
// @param x1 x coord of second endpoint
// @param y1 y coord of second endpoint
// @param C  The canvas on which to apply the draw command.
///

void Rasterizer::drawLine(int x0, int y0, int x1, int y1, simpleCanvas &C)
{
	// YOUR IMPLEMENTATION GOES HERE
	
	float deltaX = (float) (x1 - x0),
		  deltaY = (float) (y1 - y0);
	float m = (deltaX != 0) ? deltaY / deltaX : FLT_MAX, // FLT_MAX means we have a vertical line (prevent division by zero)
		  origin = y0 - m * x0;

	// the algorithm needs to work wether x0 < x1 or x1 < x0 and the same for y
	int signdX = deltaX > 0 ? 1 : -1,
		signdY = deltaY > 0 ? 1 : -1,
		corrY = signdY > 0 ? 0 : -1; // needed to correct some display issues

	int pxlX = x0, pxlY = y0; // the coordinates of the pixels we will color
	float x, y; // the "real" value of x and y in the line equation


	if (m == FLT_MAX) { // if we have a vertical line
		for (pxlY = y0; pxlY != y1; pxlY += signdY) {
			C.setPixel(pxlX, pxlY + corrY);
		}

	} else if (-1. <= m && m <= 1.) { // if we have a small slope
		for (pxlX = x0; pxlX != x1; pxlX += signdX) {
			y = m * pxlX + origin; // compute the "real" value of y, with coef and origin

			if (signdY * 2 * y > signdY * (2 * pxlY + 1)) { // if y needs to change, then do it
				pxlY += signdY;
			}

			C.setPixel(pxlX, pxlY);
		}
	}

	else { // if we have a big slope
		for (pxlY = y0; pxlY != y1; pxlY += signdY) {
			x = (pxlY - origin) / m; // compute the "real" value of x

			if (signdX * 2 * x > signdX * (2 * pxlX + signdX)) { // if x needs to change, then do it
				pxlX += signdX;
			}

			C.setPixel(pxlX, pxlY + corrY);
		}
	}
}
//
//  clipper.h
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//  
//  Contributor:  Guillaume Roy
//

#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include "simpleCanvas.h"

///
// Simple class that performs clipping
//
///

class clipper {
public:

    ///
    // Constructor
    ///
    clipper ();

    ///
    // clipPolygon
    //
    // Clip the polygon with vertex count in and vertices inx/iny
    // against the rectangular clipping region specified by lower-left corner
    // (x0,y0) and upper-right corner (x1,y1). The resulting vertices are
    // placed in outx/outy.
    //
    // The routine should return the vertex count of the polygon
    // resulting from the clipping.
    //
    // @param in the number of vertices in the polygon to be clipped
    // @param inx - x coords of vertices of polygon to be clipped.
    // @param iny - y coords of vertices of polygon to be clipped.
    // @param outx - x coords of vertices of polygon resulting after clipping.
    // @param outy - y coords of vertices of polygon resulting after clipping.
    // @param x0 - x coord of lower left of clipping rectangle.
    // @param y0 - y coord of lower left of clipping rectangle.
    // @param x1 - x coord of upper right of clipping rectangle.
    // @param y1 - y coord of upper right of clipping rectangle.
    //
    // @return number of vertices in the polygon resulting after clipping
    //
    ///

    int clipPolygon(int in, const float inx[], const float iny[],
                    float outx[], float outy[],
		    float x0, float y0, float x1, float y1);

	///
	// inside
	//
	// Tell if a given point is inside the boundaries
	//
	// @param _x the x coordinate of the point we test
	// @param _y the y coordinate of the point we test
	// @param x0 - x coord of lower left of clipping rectangle.
	// @param y0 - y coord of lower left of clipping rectangle.
	// @param x1 - x coord of upper right of clipping rectangle.
	// @param y1 - y coord of upper right of clipping rectangle.
	//
	// @return true if the point is inside the boundaries
	//
	///
	bool inside(float _x, float _y, float x0, float y0, float x1, float y1);

	///
	// output
	//
	// add a given point to the output list of vertices and increment the
	// number of points consequently
	//
	// @param _x the x coordinate of the point we want to add
	// @param _y the y coordinate of the point we want to add
	// @param out the number of vertices in outx and outy tables
	// @param outx - x coords of vertices of polygon resulting after clipping.
	// @param outy - y coords of vertices of polygon resulting after clipping.
	//
	///
	void output(float _x, float _y, int &out, float outx[], float outy[]);

	///
	// interesc
	//
	// Compute intersection of a line with a boundary
	// Will modify the values of _x and _y so that they
	// contain the coordinate of the intersection
	// we evaluate the intersection between SE and AB,
	// where AB is one of the 4 edges of the window
	//
	// @param sx the x coordinate of the start point of the line
	// @param sy the y coordinate of the start point of the line
	// @param ex the x coordinate of the end point of the line
	// @param ey the y coordinate of the end point of the line
	// @param x0 - x coord of lower left of clipping rectangle.
	// @param y0 - y coord of lower left of clipping rectangle.
	// @param x1 - x coord of upper right of clipping rectangle.
	// @param y1 - y coord of upper right of clipping rectangle.
	// @param _x the x coordinate of the intersection
	//
	///
	void intersect(float sx, float sy, float ex, float ey, float x0, float y0, float x1, float y1, float &_x, float &_y);

	///
	// SHPC
	//
	// Apply SHPC algorithm for one edge
	//
	// @param inx - x coords of vertices of polygon to be clipped.
	// @param iny - y coords of vertices of polygon to be clipped.
	// @param outx - x coords of vertices of polygon resulting after clipping.
	// @param outy - y coords of vertices of polygon resulting after clipping.
	// @param in the number of vertices in the polygon to be clipped
	// @param out the number of vertices of the output polygon
	// @param x0 - x coord of lower left of clipping rectangle.
	// @param y0 - y coord of lower left of clipping rectangle.
	// @param x1 - x coord of upper right of clipping rectangle.
	// @param y1 - y coord of upper right of clipping rectangle.
	//
	// @return number of vertices in the polygon resulting after clipping
	//
	///
	void SHPC(const float inx[], const float iny[],
		float outx[], float outy[], int in, int &out,
		float x0, float y0, float x1, float y1);
};

#endif

//
//  clipper.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//  
//  Contributor:  Guillaume Roy
//

#include "clipper.h"

///
// Simple class that performs clipping
//
///

///
// Constructor
///

clipper::clipper ()
{
}

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

int clipper::clipPolygon(int in, const float inx[], const float iny[],
                float outx[], float outy[],
		float x0, float y0, float x1, float y1)
{
	// YOUR IMPLEMENTATION GOES HERE
	int out = 0;// , out2 = 0, out3 = 0, out4 = 0;

	//float *outx2, *outy2, *outx3, *outy3, *outx4, *outy4;

	SHPC(inx, iny, outx, outy, in, out, x1, y1, x0, y1); // left
	//outx2 = new float[out]; outy2 = new float[out];
	//SHPC(outx, outy, outx2, outy2, out, out2, x0, y0, x1, y0); // bottom
	//outx3 = new float[out2]; outy3 = new float[out2];
	//SHPC(outx2, outy2, outx3, outy3, out2, out3, x1, y0, x1, y1); // right
	//outx4 = new float[out3]; outy4 = new float[out3]; 
	//SHPC(outx3, outy3, outx4, outy4, out3, out4, x1, y1, x0, y1); // top

	/*outx = outx4;
	outy = outy4;

	delete [] outx2, outy2, outx3, outy3;*/
	return out;
}

void clipper::SHPC(const float inx[], const float iny[],
	float outx[], float outy[], int in, int &out,
	float x0, float y0, float x1, float y1) {

	float px = inx[in - 1], py = iny[in - 1]; // last vertex is the initial “predecessor”

	float _x = px, _y = py;

	for (int j = 0; j < in; j++) {
		if (inside(inx[j], iny[j], x0, y0, x1, y1)) { // Cases 1 & 4
			if (inside(px, py, x0, y0, x1, y1)) { // Case 1
				output(inx[j], iny[j], out, outx, outy);
			}
			else { // Case 4
				intersect(px, py, inx[j], iny[j], x0, y0, x1, y1, _x, _y);
				output(_x, _y, out, outx, outy);
				output(inx[j], iny[j], out, outx, outy);
			}
		}
		else { // Cases 2 & 3
			if (inside(px, py, x0, y0, x1, y1)) { // Case 2
				intersect(px, py, inx[j], iny[j], x0, y0, x1, y1, _x, _y);
				output(_x, _y, out, outx, outy);
			} // Case 3 has no output 
		}

		px = inx[j];
		py = iny[j];

	} // for
}


// is point inside boundary?
bool clipper::inside(float _x, float _y, float x0, float y0, float x1, float y1) {
	if (y0 == y1) { // horizontal edge
		if (x0 < x1) return _y >= y0;
		if (x0 > x1) return _y <= y0;
	} else { // vertical edge
		if (y1 > y0) return _x <= x0;
		if (y0 > y1) return _x >= x0;
	}
	return false;
}


// put point into vector, update length
void clipper::output(float _x, float _y, int &out, float outx[], float outy[]) {
	outx[out] = _x;
	outy[out++] = _y;
}


// compute intersection point, put point into newpoint parameter
void clipper::intersect(float sx, float sy, float ex, float ey, float x0, float y0, float x1, float y1, float &_x, float &_y) {
	float m, B;

	if (x0 == x1) { // if it's a vertical edge
		m = (ey - sy) / (ex - sx);
		B = ey - m * ex;
		_x = x0;
		_y = m * _x + B;
	}
	else { // if it's a horizontal edge
		m = (ex - sx) / (ey - sy);
		B = ey - m * ex;
		_y = y0;
		_x = (_y - B) / m;
	}
}
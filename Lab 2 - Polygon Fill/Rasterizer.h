//
//  Rasterizer.h
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#ifndef _RASTERIZER_H
#define _RASTERIZER_H

class simpleCanvas;

///
//
// Simple class that performs rasterization algorithms
//
///

class Rasterizer {

public:
    ///
    // Constructor
    //
    // @param n - number of scanlines
    //
    ///
    Rasterizer (int n);

    ///
    // Draw a filled polygon in the simpleCanvas C.
    //
    // The polygon has n distinct vertices.  The coordinates of the vertices
    // making up the polygon are stored in the x and y arrays.  The ith
    // vertex will have coordinate (x[i],y[i]).
    //
    // You are to add the implementation here using only calls
    // to C.setPixel()
    ///
    void drawPolygon(int n, int x[], int y[], simpleCanvas &C);

	// we define a Bucket structure to store, 
	// for each edge, the following values
	typedef struct {
		int yMin, // The minimum y value of the two vertices
			yMax; // The maximum y value of the two vertices
		float xVal, // The x value associated with the minimum y value
			  inv_m; // 1/m, the inverse of the slope
	} Bucket ;
private:
    ///
    // number of scanlines
    ///
    int n_scanlines;
};


#endif

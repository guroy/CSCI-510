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

using namespace std;

///
//
// Simple class that performs rasterization algorithms
//
///

///
// Constructor
//
// @param n - number of scanlines
//
///

Rasterizer::Rasterizer (int n) : n_scanlines (n)
{
}

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

void Rasterizer::drawPolygon(int n, int x[], int y[], simpleCanvas &C)
{
    // YOUR IMPLEMENTATION GOES HERE
	int nbEdges = sizeof(x);


	/*
		Initializing All of the Edges
	*/
	
	// we define a Bucket structure to store, for each edge, the following values
	typedef struct {
		int yMin, // The minimum y value of the two vertices
			yMax, // The maximum y value of the two vertices
			xVal; // The x value associated with the minimum y value
		float inv_m; // 1/m, the inverse of the slope
	} Bucket ;
	
	// we allocate an Array that will contain all the Buckets of the polygon
	Bucket *globalEdgeTable = new Bucket[nbEdges - 1];

	// we count the number of horizontal lines we forget, as we don't need to store them
	int nbHorizontalLines = 0;

	for (int i = 0; i < nbEdges - 1; i++) {
		Bucket b;
		// let's initialize the current bucket
		b.yMin = min(y[i], y[i + 1]);
		b.yMax = max(y[i], y[i + 1]);
		b.xVal = b.yMin == y[i] ? x[i] : x[i + 1];
		b.inv_m = b.yMax - b.yMin != 0 ?
			abs(x[i] - x[i + 1]) / (b.yMax - b.yMin) : FLT_MAX;
		// we don't need to store horizontal lines. As we have the 
		if (b.inv_m != FLT_MAX)
			globalEdgeTable[i] = b;
		else
			nbHorizontalLines++;
	}

	// here is the number of buckets we truly keep after having removed the horizontal edges
	nbEdges -= nbHorizontalLines;
	

	/*
		Initializing the Global Edge Table
	*/

	Bucket b;

	// we need to sort the buckets...
	for (int i = 0; i < nbEdges - 1; i++) {
		for (int j = i; j < nbEdges - 1; j++) {
			// sort by yMin...
			if (globalEdgeTable[j].yMin <= globalEdgeTable[i].yMin) {
				// or by xVal if yMin is the same
				if (globalEdgeTable[j].yMin < globalEdgeTable[i].yMin || globalEdgeTable[j].xVal < globalEdgeTable[i].xVal) {
					b = globalEdgeTable[j];
					globalEdgeTable[j] = globalEdgeTable[i];
					globalEdgeTable[i] = b;
				}
			}
		}
	}


	/*
		Initializing parity
	*/

	free(globalEdgeTable);
}

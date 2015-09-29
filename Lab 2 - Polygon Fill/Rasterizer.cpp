//
//  Rasterizer.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Guillaume Roy
//
//  To do this exercise, I helped myself with the following website:
//  http://www.cs.rit.edu/~icss571/filling/index.html and adapted the
//  algorithm explained into it to C++ source code.
//

#include "Rasterizer.h"
#include "simpleCanvas.h"

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
	int xMax = *max_element(x, x + sizeof(x)); // define the right bound of the polygon

	/*
		Initializing All of the Edges
	*/
	
	// we define a Bucket structure to store, for each edge, the following values
	typedef struct {
		int yMin, // The minimum y value of the two vertices
			yMax; // The maximum y value of the two vertices
		float xVal, // The x value associated with the minimum y value
			  inv_m; // 1/m, the inverse of the slope
	} Bucket ;
	
	// we allocate an Array that will contain all the Buckets of the polygon
	vector<Bucket> globalEdgeTable;

	for (int i = 0; i < n - 1; i++) {
		Bucket b;
		// let's initialize the current bucket
		b.yMin = min(y[i], y[i + 1]);
		b.yMax = max(y[i], y[i + 1]);
		b.xVal = (float) (b.yMin == y[i] ? x[i] : x[i + 1]);
		b.inv_m = b.yMax - b.yMin != 0 ?
			(float ) (x[i] - x[i + 1]) / (float) (y[i] - y[i + 1]) : FLT_MAX;
		// we don't need to store horizontal lines. As we have the 
		if (b.inv_m != FLT_MAX)
			globalEdgeTable.push_back(b);
	}

	// here is the number of buckets we truly keep after having removed the horizontal edges
	n = globalEdgeTable.size();
	//

	/*
		Initializing the Global Edge Table
	*/

	Bucket b;

	// we need to sort the buckets. It's not the optimum way to do this,
	// but as the numbre of values is small, it does not matter 
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			// sort by yMin...
			if (globalEdgeTable.at(j).yMin <= globalEdgeTable.at(i).yMin) {
				// or by xVal if yMin is the same
				if (globalEdgeTable.at(j).yMin < globalEdgeTable.at(i).yMin || globalEdgeTable.at(j).xVal < globalEdgeTable.at(i).xVal) {
					b = globalEdgeTable.at(j);
					globalEdgeTable.at(j) = globalEdgeTable.at(i);
					globalEdgeTable.at(i) = b;
				}
			}
		}
	}


	/*
		Initializing parity
	*/

	// we create this enum to make the code more 'readable'
	enum {
		EVEN, ODD
	};

	int parity;


	/*
		Initializing the Scan-Line 
	*/

	int scanLine = globalEdgeTable.at(0).yMin;


	/*
		Initializing the Active Edge Table
	*/

	vector<Bucket> activeEdgeTable;

	int maxLine = globalEdgeTable.at(n-1).yMax;


	for (int line = scanLine; line < scanLine+4; line++) {
		parity = EVEN;
		// for each scanLine, we want to retrieve every bucket whose yMin = scanLine
		int i = 0;
		while (i < n) {
			b = globalEdgeTable.at(i);
			if (b.yMin == scanLine) {
				// Remove any edges from the global edge table for which the minimum y value
				// is equal to the scan-line and place them in the active edge table
				activeEdgeTable.push_back(b);
				globalEdgeTable.erase(globalEdgeTable.begin() + i);
				n--;
			}
			else if (b.yMax == scanLine) {
				//Remove any edges from the active edge table for which
				//the maximum y value is equal to the scan_line.
				activeEdgeTable.erase(activeEdgeTable.begin() + i);
			} else {
				i++;
			}
		}


		/*
			Filling the Polygon
		*/

		int nbActiveEdges = activeEdgeTable.size(),
			currentEdge = 0;

		for (int scanX = 0; scanX <= xMax; scanX++) {

			if (scanX == ((parity == ODD) ? ceil(activeEdgeTable.at(currentEdge).xVal) : round(activeEdgeTable.at(currentEdge).xVal))) {
				// We change parity
				parity = (parity == EVEN) ? ODD : EVEN;

				// We want to be sure that we try every edges. Even when multiple buckets have
				// the same xVal, which is why we use a while loop
				while (currentEdge < nbActiveEdges && scanX == ((parity == ODD) ? ceil(activeEdgeTable.at(currentEdge).xVal) : round(activeEdgeTable.at(currentEdge).xVal))) {
					// Update the x value for for each edge in the active 
					// edge table using the formula x1 = x0 + 1/m
					Bucket b = activeEdgeTable.at(currentEdge);
					Bucket bUpdated = { b.yMin, b.yMax, b.xVal + b.inv_m, b.inv_m };
					activeEdgeTable.at(currentEdge) = bUpdated;

					currentEdge++;
				}
			}
			// Draw all pixels from the x value of odd to the x value of even parity edge pairs
			if (parity == ODD) {
				C.setPixel(scanX, line);
			}
		}

		// Reorder the edges in the active edge table according to
		// increasing x value. This is done in case edges have crossed
		for (int i = 0; i < nbActiveEdges - 1; i++) {
			for (int j = i + 1; j < nbActiveEdges; j++) {
				if (activeEdgeTable.at(j).xVal < activeEdgeTable.at(i).xVal) {
					b = activeEdgeTable.at(j);
					activeEdgeTable.at(j) = activeEdgeTable.at(i);
					activeEdgeTable.at(i) = b;
				}
			}
		}
	}
}

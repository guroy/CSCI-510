//
//  clipper.h
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//  
//  Contributor:  YOUR_NAME_HERE
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

};

#endif

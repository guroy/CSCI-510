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
    // @param n number of scanlines
    //
    ///

    Rasterizer (int n);

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

    void drawLine (int x0, int y0, int x1, int y1, simpleCanvas &C);

private:

    ///
    // number of scanlines
    ///

    int n_scanlines;
};


#endif

//
//  cgCanvas.h
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Guillaume Roy
//

#ifndef _CGCANVAS_H_
#define _CGCANVAS_H_

#include "simpleCanvas.h"
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

class cgCanvas : public simpleCanvas {
	vector<sf::ConvexShape> polys;

public:
	static int polyID;

    ///
    // Constructor
    //
    // @param w - width of canvas
    // @param h - height of canvas
    ///

    cgCanvas(int w, int h);

    ///
    //
    // addPoly - Add a polygon to the canvas.  This method does not draw
    //           the polygon, but merely stores it for later drawing.
    //           Drawing is initiated by the drawPoly() method.
    //
    //           Returns a unique integer id for the polygon.
    //
    // @param x - Array of x coords of the vertices of the polygon to be added
    // @param y - Array of y coords of the vertices of the polygon to be added
    // @param n - Number of vertices in polygon
    //
    // @return a unique integer identifier for the polygon
    ///

    int addPoly (const float x[], const float y[], int n);

    ///
    //
    // drawPoly - Draw the polygon with the given id.  The polygon should
    //            be drawn after applying the current transformation to
    //            the vertices of the polygon.
    //
    // @param polyID - the ID of the polygon to be drawn
    ///

    void drawPoly (int polyID);

    ///
    //
    // clearTransform - Set the current transformation to the identity matrix.
    //
    ///

    void clearTransform();

    ///
    //
    // translate - Add a translation to the current transformation by
    //             premultiplying the appropriate translation matrix to
    //             the current transformation matrix.
    //
    // @param x - Amount of translation in x
    // @param y - Amount of translation in y
    //
    ///

    void translate (float x, float y);

    ///
    //
    // rotate - Add a rotation to the current transformation by premultiplying
    //          the appropriate rotation matrix to the current transformation
    //          matrix.
    //
    // @param degrees - Amount of rotation in degrees
    //
    ///

    void rotate (float degrees);

    ///
    //
    // scale - Add a scale to the current transformation by premultiplying
    //         the appropriate scaling matrix to the current transformation
    //         matrix.
    //
    // @param x - Amount of scaling in x
    // @param y - Amount of scaling in y
    //
    ///

    void scale (float x, float y);

    ///
    //
    // setClipWindow - Define the clip window.
    //
    // @param bottom - y coord of bottom edge of clip window (in world coords)
    // @param top - y coord of top edge of clip window (in world coords)
    // @param left - x coord of left edge of clip window (in world coords)
    // @param right - x coord of right edge of clip window (in world coords)
    //
    ///

    void setClipWindow (float bottom, float top, float left, float right);

    ///
    //
    // setViewport - Define the viewport.
    //
    // @param xmin - x coord of lower left of view window (in screen coords)
    // @param ymin - y coord of lower left of view window (in screen coords)
    // @param width - width of view window (in world coords)
    // @param height - width of view window (in world coords)
    //
    ///

    void setViewport (int x, int y, int width, int height);


};

#endif

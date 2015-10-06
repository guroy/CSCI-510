//
//  extendedCanvas.h
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//  
//  This file should not be modified by students.
//

#ifndef _EXTENDEDCANVAS_H_
#define _EXTENDEDCANVAS_H_

#include "simpleCanvas.h"

#include <vector>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Color.hpp>

using namespace std;

///
// This is a special subclass of simpleCanvas with functionality
// for testing out the clipping assignment.
//
// Note, this class should only be used for the clipping assignment
// and only for testing purposes!!!
///

class extendedCanvas : public simpleCanvas {

private:
    ///
    // SFML polygons
    ///
    vector<sf::ConvexShape> polys;

public:
    ///
    // Constructor
    //
    // @param w width of canvas
    // @param h height of canvas
    ///
    extendedCanvas(int w, int h);

    ///
    // draw yourself into a given renderWindow
    //
    // @param R - the window in which to draw.
    ///
    void draw (sf::RenderWindow &R);

    ///
    // prints a poly outline -- for cliptest assignment
    ///
    void printLoop (int n, const float x[], const float y[] );

    ///
    // draws a filled poly -- for cliptest assignment
    ///
    void printPoly (int n, const float x[], const float y[] );

};

#endif

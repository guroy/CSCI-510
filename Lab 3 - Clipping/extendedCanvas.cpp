//
//  extendedCanvas.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//  
//  This file should not be modified by students.
//

#include "extendedCanvas.h"
#include <SFML/Config.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

///
// This is a special subclass of simpleCanvas with functionality
// for testing out the clipping assignment.
//
// Note, this class should only be used for the clipping assignment
// and only for testing purposes!!!
///

///
// Constructor
//
// @param w width of canvas
// @param h height of canvas
///

extendedCanvas::extendedCanvas(int w, int h) : simpleCanvas(w,h)
{
}

///
// prints a poly outline -- for cliptest assignment
///

void extendedCanvas::printLoop (int n, const float x[], const float y[] )
{
    sf::ConvexShape P;
    P.setPointCount( n );
    P.setOutlineColor( myColor );
    P.setOutlineThickness( 1 );

    for( int i=0; i < n; i++ )
        P.setPoint( i, sf::Vector2f(x[i], height - y[i]) );

    polys.push_back (P);
}

///
// draws a filled poly -- for cliptest assignment
///

void extendedCanvas::printPoly (int n, const float x[], const float y[] )
{
    sf::ConvexShape P;
    P.setPointCount( n );
    P.setFillColor( myColor );
    P.setOutlineColor( myColor );
    P.setOutlineThickness( 1 );

    for (int i=0; i < n; i++)
        P.setPoint( i, sf::Vector2f(x[i], height - y[i]) );

    polys.push_back (P);
}



///
// draw yourself into a given renderWindow
//
// @param R - the window in which to draw.
///

void extendedCanvas::draw (sf::RenderWindow &R)
{
    // draw as usual
    simpleCanvas::draw (R);

    // draw your polys
    vector<sf::ConvexShape>::iterator it;
    for (it = polys.begin(); it != polys.end(); it++) {
        R.draw ((*it));
    }
}

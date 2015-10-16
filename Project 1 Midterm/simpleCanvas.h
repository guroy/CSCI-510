//
//  simpleCanvas.h
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  This file should not be modified by students.
//

#ifndef _SIMPLECANVAS_H_
#define _SIMPLECANVAS_H_

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

using namespace std;

///
// Simple canvas class that allows for pixel-by-pixel rendering.
//
///
class simpleCanvas {

private:

    ///
    // height and width of the canvas
    ///
    int width;
    int height;

    sf::Image myImage;
    sf::Color myColor;

    vector<sf::ConvexShape> polys;

public:

    ///
    // Constructor
    //
    // @param w width of canvas
    // @param h height of canvas
    ///

    simpleCanvas( int w, int h );

    ///
    // Clears the canvas using the current color.
    ///

    void clear();

    ///
    // Draw yourself into a given renderWindow.
    //
    // @param R - the window in which to draw.
    ///

    void draw( sf::RenderWindow &R );

    ///
    // Sets the current color.
    //
    // @param r - The red component of the new color (between 0-1)
    // @param g - The green component of the new color (between 0-1)
    // @param b - The blue component of the new color (between 0-1);
    ///

    void setColor( float r, float g, float b );

    ///
    // Use this drawOutline() method only if you were NOT able to
    // create a working drawPolygon() Rasterizer routine of your own.
    // This method will only draw the outline of the polygon.
    ///

    void drawOutline( int n, int x[], int y[] );

    ///
    // Writes a pixel using the passed in color.  Does not modify the
    // current color.
    //
    // @param x - The x coord of the pixel to be set
    // @param y - The y coord of the pixel to be set
    // @param r - The red component of the new color (between 0-1)
    // @param g - The green component of the new color (between 0-1)
    // @param b - The blue component of the new color (between 0-1)
    ///

    void setPixel( int x, int y, float r, float g, float b );

    ///
    // Writes a pixel using the current color.
    //
    // @param x - The x coord of the pixel to be set
    // @param y - The y coord of the pixel to be set
    ///

    void setPixel( int x, int y );

};


#endif

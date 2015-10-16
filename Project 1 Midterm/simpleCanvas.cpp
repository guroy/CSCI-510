//
//  simpleCanvas.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  This file should not be modified by students.
//

#include "simpleCanvas.h"
#include <SFML/Config.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>

using namespace std;

///
// Simple canvas class that allows for pixel-by-pixel rendering.
///

///
// Constructor
//
// @param w width of canvas
// @param h height of canvas
///

simpleCanvas::simpleCanvas(int w, int h) : myColor(0,0,0),
    width(w), height(h)
{
    myImage.create( w, h, myColor );
}

///
// Clears the canvas using the current color.
///

void simpleCanvas::clear()
{
    for( int i=0; i < width; i++ )
        for( int j=0; j < height; j++ ) {
            myImage.setPixel( i, j, myColor );
        }
    polys.clear();
}

///
// Draw yourself into a given renderWindow.
//
// @param R - the window in which to draw.
///

void simpleCanvas::draw( sf::RenderWindow &R )
{
    sf::Texture tex;

    bool temp;
    temp = tex.loadFromImage( myImage );

    sf::Sprite toDraw;
    toDraw.setTexture( tex );
    toDraw.setPosition( 0, 0 );

    // Add your image as a sprite
    R.draw( toDraw );

    // draw your polys
    vector<sf::ConvexShape>::iterator it;
    for( it = polys.begin(); it != polys.end(); it++ ) {
        R.draw( (*it) );
    }
}

///
// Use this drawOutline() method only if you were NOT able to
// create a working drawPolygon() Rasterizer routine of your own.
// This method will only draw the outline of the polygon.
///

void simpleCanvas::drawOutline( int n, int x[], int y[] )
{
    sf::ConvexShape P;
    P.setPointCount( n );
    P.setOutlineColor( myColor );
    P.setOutlineThickness( 1 );

    for( int i=0; i < n; i++ )
        P.setPoint( i, sf::Vector2f(x[i], height - y[i]) );

    polys.push_back( P );
}

///
// Sets the current color.
//
// @param r - The red component of the new color (between 0-1)
// @param g - The green component of the new color (between 0-1)
// @param b - The blue component of the new color (between 0-1);
///

void simpleCanvas::setColor( float r, float g, float b )
{
    unsigned char R = (unsigned char)(r * 255);
    unsigned char G = (unsigned char)(g * 255);
    unsigned char B = (unsigned char)(b * 255);
    myColor = sf::Color( R, G, B );
}

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

void simpleCanvas::setPixel( int x, int y, float r, float g, float b )
{
    unsigned char R = (unsigned char)(r * 255);
    unsigned char G = (unsigned char)(g * 255);
    unsigned char B = (unsigned char)(b * 255);
    myImage.setPixel( x, y, sf::Color (R, G, B) );
}

///
// Writes a pixel using the current color.
//
// @param x - The x coord of the pixel to be set
// @param y - The y coord of the pixel to be set
///

void simpleCanvas::setPixel( int x, int y )
{
    myImage.setPixel( x, (height - y - 1), myColor );
}

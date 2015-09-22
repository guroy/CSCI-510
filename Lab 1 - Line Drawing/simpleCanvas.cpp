//
//  simpleCanvas.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Modified and updated to SFML 2.1 by Vasudev Prasad Bethamcherla
//  on 08/19/2014
//

#include "simpleCanvas.h"
#include <SFML/Config.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

///
// Simple canvas class that allows for pixel-by-pixel rendering.
//
///

///
// Constructor
//
// @param w width of canvas
// @param h height of canvas
///

simpleCanvas::simpleCanvas(int w, int h) : myColor (0,0,0), 
    width (w), height (h)
{
     myImage.create( w, h, myColor );
}

///
// clears the canvas using the current color
///

void simpleCanvas::clear()
{
    for (int i=0; i < width; i++)
        for (int j=0; j < height; j++)
            myImage.setPixel (i, j, myColor);
}

///
// draw yourself into a given renderWindow
//
// @param R the window in which to draw.
///

void simpleCanvas::draw (sf::RenderWindow &R)
{
    // Creating myImage -> Texture -> Sprite
    sf::Texture tex;

    bool temp;
    temp = tex.loadFromImage( myImage );

    sf::Sprite toDraw;
    toDraw.setTexture( tex );

    // Add your image as a sprite
    R.draw( toDraw );
}


///
// Sets the current color
//
// @param r The red component of the new color (between 0-1)
// @param g The green component of the new color (between 0-1)
// @param b The blue component of the new color (between 0-1);
///

void simpleCanvas::setColor (float r, float g, float b)
{
    unsigned char R = (unsigned char)(r * 255);
    unsigned char G = (unsigned char)(g * 255);
    unsigned char B = (unsigned char)(b * 255);
    myColor = sf::Color (R, G, B);
}


///
// writes a pixel using the passed in color.  Does not modify the 
// current color
//
// @param x The x coord of the pixel to be set
// @param y The y coord of the pixel to be set
// @param r The red component of the new color (between 0-1)
// @param g The green component of the new color (between 0-1)
// @param b The blue component of the new color (between 0-1)
///

void simpleCanvas::setPixel (int x, int y, float r, float g, float b)
{
    unsigned char R = (unsigned char)(r * 255);
    unsigned char G = (unsigned char)(g * 255);
    unsigned char B = (unsigned char)(b * 255);
    myImage.setPixel (x, y, sf::Color (R, G, B));
}

///
// writes a pixel using the current color
//
// @param x The x coord of the pixel to be set
// @param y The y coord of the pixel to be set
///

void simpleCanvas::setPixel (int x, int y)
{
    myImage.setPixel (x, (height - y - 1), myColor);
}

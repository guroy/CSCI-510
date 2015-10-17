//
//  midtermMain.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  This file should not be modified by students.
//

#include <SFML/Graphics.hpp>
#include "cgCanvas.h"

///
// some globals since I didn't want to make a midtermMain class.
///

// Which image are we showing?
int displayNumber = 1;

// Polygon IDs for our objects
int triangle;
int square;
int octagon;
int star;
int R;
int I;
int T;
int H;

// Dimensions of the drawing window
int drawHeight = 500;
int drawWidth = 500;

///
// Draw plain old polygons.
///

void drawPolysNorm( cgCanvas &C )
{
    ///
    // Draw a dark blue/purple triangle
    ///
    C.clearTransform();
    C.setColor( 0.25f, 0.0f, 0.74f );
    C.drawPoly( triangle );

    ///
    // Draw a green square
    ///
    C.setColor( 0.0f, 0.91f, 0.08f );
    C.drawPoly( square );

    ///
    // Draw a pink otcagon
    ///
    C.setColor( 0.98f, 0.0f, 0.48f );
    C.drawPoly( octagon );

    ///
    // Draw a green star
    ///
    C.setColor( 0.68f, 0.0f, 0.75f );
    C.drawPoly( star );
}


///
// Draw the world transformed...used for transformation tests.
///

void drawPolysXform( cgCanvas &C ) {

    ///
    // Draw a dark blue/purple triangle rotated
    ///
    C.clearTransform();
    C.rotate( -25.0f );
    C.setColor( 0.25f, 0.0f, 0.74f );
    C.drawPoly( triangle );

    ///
    // Draw a green square translated
    ///
    C.clearTransform();
    C.translate( 80.0f, 75.0f );
    C.setColor( 0.0f, 0.91f, 0.08f );
    C.drawPoly( square );

    ///
    // Draw a pink octagon scaled
    ///
    C.clearTransform();
    C.scale( 0.75f, 0.5f );
    C.setColor( 0.98f, 0.0f, 0.48f );
    C.drawPoly( octagon );

    ///
    // Draw a green star translated, scaled, rotated, then scaled back
    ///
    C.clearTransform();
    C.translate( 50.0f, 50.0f );
    C.scale( 2.0f, 2.0f );
    C.rotate( -10.0f );
    C.translate( -50.0f, 50.0f );
    C.setColor( 0.68f, 0.0f, 0.75f );
    C.drawPoly( star );
}

///
// Draw the RIT letters.
///

void drawLetters( cgCanvas &C )
{
    ///
    // Draw with staggered translation
    ///

    C.clearTransform();
    C.translate(15.0f, 0.0f);
    C.drawPoly( R );

    C.clearTransform();
    C.translate(10.0f, 0.0f);
    C.drawPoly( I );

    C.clearTransform();
    C.translate(5.0f, 0.0f);
    C.drawPoly( T );

    C.clearTransform();
    C.translate(0.0f, 0.0f);
    C.setColor(0.0f, 0.0f, 0.0f);
    C.drawPoly( H );

}


///
// The display function.
///

void doDraw(cgCanvas &C)
{
    ///
    // set clear color to black
    ///
    C.setColor( 0.0f, 0.0f, 0.0f );
    C.clear();

    ///
    // plain old polygon test
    ///
    if( (displayNumber % 4) == 1 ) {

        // default clipping
        C.setClipWindow( 0.0f, 500.0f, 0.0f, 500.0f );

        // default viewport
        C.setViewport( 0, 0, drawWidth, drawHeight );

        // draw the polys
        drawPolysNorm(C);
    }
    else if( (displayNumber % 4) == 2 ) {

        // clipping test
        C.setClipWindow( 35.0f, 175.0f, 35.0f, 165.0f );

        // default viewport
        C.setViewport( 0, 0, drawWidth, drawHeight );

        // draw the polys
        drawPolysNorm(C);

    }
    else if( (displayNumber % 4) == 3 ) {

        // default clipping
        C.setClipWindow( 0.0f, 500.0f, 0.0f, 500.0f );

        // default viewport
        C.setViewport( 0, 0, drawWidth, drawHeight );

        // draw the tranformed polys
        drawPolysXform(C);
    }

    else { // displayNumber == 0

        // default clipping
        C.setClipWindow( 0.0f, 500.0f, 0.0f, 500.0f );

        // have some fun with the view port
        int wdiff = drawWidth / 3;
        int hdiff = drawHeight / 3;

	// will use xaspect and yaspect to
	// draw each row with a different ratio
	int xaspect = drawWidth / 3;
	int yaspect = drawHeight / 3;
        int x = 0;
        int y = 0;
        int i, j;

        for( i = 0; i < 3; i++ ) {
	    // adjust yaspect
	    yaspect = hdiff/(i+1);

	    for( j = 0; j < 3; j++ ) {
	        // let's play around with colors
		if( i == j ) // 1::1 ratios
		    C.setColor( 0.98f, 0.31f, 0.08f );
		else if( i < j ) // yaspect is smaller
		    C.setColor( 0.0f, 0.91f, 0.08f );
		else // i > j, xaspect larger
		    C.setColor( 0.98f, 0.0f, 0.48f );

		// adjust xaspect and shift to next column
		xaspect = wdiff/(j+1);
                C.setViewport( x, y, xaspect, yaspect );
                drawLetters( C );
                x += wdiff + 35;
	    }

	    // shift to next row, also add a little extra space
	    // due to aspect ratio stuff making lots of blank canvas
	    y += hdiff + 35;

	    // change y aspect ratio
	    xaspect = wdiff;

	    // reset to left side of canvas
	    x = 0;

        }
    }
}


///
// Callback for key presses.  Returns a flag indicating if the app should
// close as a result of this key press.
//
// SFML, in its infinite wisdom, doesn't actually give you the key that
// was pressed; instead, you get an sf::Keyboard::Key enumerated type
// value representing the key, with A == 0 and Z == 25.
///

bool keyTyped(enum sf::Keyboard::Key key)
{
    switch( key ) {
        case sf::Keyboard::Q:
		return true;			// quit

	case sf::Keyboard::P:
	case sf::Keyboard::Num1:
		displayNumber = 1;  break;	// polygon

	case sf::Keyboard::C:
	case sf::Keyboard::Num2:
		displayNumber = 2;  break;	// clip

	case sf::Keyboard::T:
	case sf::Keyboard::Num3:
		displayNumber = 3;  break;	// transform

	case sf::Keyboard::V:
	case sf::Keyboard::Num4:
		displayNumber = 0;  break;	// viewport

    }

    return false;
}


///
// Main program for the 2D pipeline assignment.
///

int main( int argc, char *argv[] )
{

    // define your canvas
    cgCanvas C(drawWidth, drawHeight);

    // load all of your polygons
    float x[12];
    float y[12];

    // triangle
    x[0] = 25.0f; y[0] = 125.0f;
    x[1] = 75.0f; y[1] = 125.0f;
    x[2] = 50.0f; y[2] = 175.0f;
    triangle = C.addPoly( x, y, 3 );

    // square
    x[0] = 125.0f; y[0] = 125.0f;
    x[1] = 175.0f; y[1] = 125.0f;
    x[2] = 175.0f; y[2] = 175.0f;
    x[3] = 125.0f; y[3] = 175.0f;
    square = C.addPoly( x, y, 4 );

    // octagon
    x[0] = 25.0f; y[0] = 25.0f;
    x[1] = 35.0f; y[1] = 15.0f;
    x[2] = 55.0f; y[2] = 15.0f;
    x[3] = 75.0f; y[3] = 25.0f;
    x[4] = 75.0f; y[4] = 55.0f;
    x[5] = 55.0f; y[5] = 75.0f;
    x[6] = 35.0f; y[6] = 75.0f;
    x[7] = 25.0f; y[7] = 55.0f;
    octagon = C.addPoly( x, y, 8 );

    // star
    x[0] = 150.0f; y[0] = 90.0f;
    x[1] = 140.0f; y[1] = 65.0f;
    x[2] = 110.0f; y[2] = 65.0f;
    x[3] = 140.0f; y[3] = 40.0f;
    x[4] = 110.0f; y[4] = 10.0f;
    x[5] = 150.0f; y[5] = 25.0f;
    x[6] = 190.0f; y[6] = 10.0f;
    x[7] = 160.0f; y[7] = 40.0f;
    x[8] = 190.0f; y[8] = 65.0f;
    x[9] = 160.0f; y[9] = 65.0f;
    star = C.addPoly( x, y, 10 );

    // R
    x[0] = 10.0f;  y[0] = 480.0f;
    x[1] = 140.0f; y[1] = 480.0f;
    x[2] = 175.0f; y[2] = 450.0f;
    x[3] = 175.0f; y[3] = 430.0f;
    x[4] = 140.0f; y[4] = 370.0f;
    x[5] = 90.0f;  y[5] = 370.0f;
    x[6] = 175.0f; y[6] = 140.0f;
    x[7] = 145.0f; y[7] = 140.0f;
    x[8] = 65.0f;  y[8] = 370.0f;
    x[9] = 35.0f;  y[9] = 370.0f;
    x[10] = 35.0f; y[10] = 140.0f;
    x[11] = 10.0f; y[11] = 140.0f;
    R = C.addPoly(x, y, 12);

    // I
    x[0] = 190.0f;  y[0] = 480.0f;
    x[1] = 340.0f;  y[1] = 480.0f;
    x[2] = 340.0f;  y[2] = 440.0f;
    x[3] = 280.0f;  y[3] = 440.0f;
    x[4] = 280.0f;  y[4] = 180.0f;
    x[5] = 340.0f;  y[5] = 180.0f;
    x[6] = 340.0f;  y[6] = 140.0f;
    x[7] = 190.0f;  y[7] = 140.0f;
    x[8] = 190.0f;  y[8] = 180.0f;
    x[9] = 250.0f;  y[9] = 180.0f;
    x[10] = 250.0f; y[10] = 440.0f;
    x[11] = 190.0f; y[11] = 440.0f;
    I = C.addPoly(x, y, 12);

    // T
    x[0] = 360.0f; y[0] = 480.0f;
    x[1] = 480.0f; y[1] = 480.0f;
    x[2] = 480.0f; y[2] = 440.0f;
    x[3] = 430.0f; y[3] = 440.0f;
    x[4] = 430.0f; y[4] = 140.0f;
    x[5] = 400.0f; y[5] = 140.0f;
    x[6] = 400.0f; y[6] = 440.0f;
    x[7] = 360.0f; y[7] = 440.0f;
    T = C.addPoly(x, y, 8);

    // H (hole in R)
    x[0] = 35.0f;  y[0] = 450.0f;
    x[1] = 110.0f; y[1] = 450.0f;
    x[2] = 130.0f; y[2] = 430.0f;
    x[3] = 110.0f; y[3] = 410.0f;
    x[4] = 35.0f;  y[4] = 410.0f;
    H = C.addPoly(x, y, 5);

    // create and run the app
    sf::RenderWindow App(sf::VideoMode(drawWidth, drawHeight), "CG Midterm");
    while( App.isOpen() )
    {
        // Process events
        sf::Event Event;
        while( App.pollEvent(Event) )
        {
            // Close window : exit
            if( Event.type == sf::Event::Closed )
                App.close();

            // Keypress
            if( Event.type == sf::Event::KeyPressed )
                if( keyTyped(Event.key.code) )
                    App.close();

            // Mouse click
            if( Event.type == sf::Event::MouseButtonPressed )
                displayNumber++;
        }

        // Clear screen
        App.clear();

        // draw on your canvas
        doDraw(C);

        // Draw your canvas to your window
        C.draw( App );

        App.display();
    }

    return 0;

}

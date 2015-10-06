//
//  clipTest.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  This file should not be modified by students.
//

#include <SFML/Graphics.hpp>
#include "extendedCanvas.h"
#include "clipper.h"

///
// Support function that draws clip regions as line loops
///

static void drawClipRegion( float llx, float lly, float urx, float ury,
        extendedCanvas *T ) {
    float x[4];
    float y[4];

    x[0] = llx; y[0] = lly;
    x[1] = urx; y[1] = lly;
    x[2] = urx; y[2] = ury;
    x[3] = llx; y[3] = ury;

    T->printLoop( 4, x, y );
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
        case sf::Keyboard::Q:  return true;                     // quit
    }

    return false;
}

///
//
// main program for clipping assignment
//
///

int main (int argc, char *argv[])
{
    extendedCanvas T(300, 300);
    clipper C;
    T.setColor (1.0, 1.0, 1.0);
    T.clear();

    float quad1x[4];
    float quad1y[4];
    quad1x[0] =  20; quad1x[1] =  20; quad1x[2] =  40; quad1x[3] =  40;
    quad1y[0] = 120; quad1y[1] = 140; quad1y[2] = 140; quad1y[3] = 120;

    float quad2x[4];
    float quad2y[4];
    quad2x[0] =  80; quad2x[1] =  80; quad2x[2] =  60; quad2x[3] =  60;
    quad2y[0] = 160; quad2y[1] = 200; quad2y[2] = 200; quad2y[3] = 160;

    float quad3x[4];
    float quad3y[4];
    quad3x[0] = 20; quad3x[1] = 50; quad3x[2] = 50; quad3x[3] = 20;
    quad3y[0] = 60; quad3y[1] = 60; quad3y[2] = 50; quad3y[3] = 50;

    float quad4x[4];
    float quad4y[4];
    quad4x[0] =  44; quad4x[1] =  60; quad4x[2] =  60; quad4x[3] =  44;
    quad4y[0] = 122; quad4y[1] = 122; quad4y[2] = 146; quad4y[3] = 146;

    float pent1x[5];
    float pent1y[5];
    pent1x[0] = 80; pent1x[1] = 90; pent1x[2] = 110; pent1x[3] = 100; pent1x[4] = 80;
    pent1y[0] = 20; pent1y[1] = 10; pent1y[2] = 20; pent1y[3] = 50; pent1y[4] = 40;

    float hept1x[7];
    float hept1y[7];
    hept1x[0] = 120; hept1x[1] = 140; hept1x[2] = 160; hept1x[3] = 160; hept1x[4] = 140; hept1x[5] = 120; hept1x[6] = 110;
    hept1y[0] = 70; hept1y[1] = 70; hept1y[2] = 80; hept1y[3] = 100; hept1y[4] = 110; hept1y[5] = 100; hept1y[6] = 90;

    float wx[50];
    float wy[50];
    int wl;

    ///
    // Draw the clipping regions
    ///
    T.setColor( 0.0f, 0.0f, 0.0f );
    drawClipRegion(  10, 110,  50, 150, &T );
    drawClipRegion(  30,  10,  70,  80, &T );
    drawClipRegion(  90,  34, 120,  60, &T );
    drawClipRegion(  90,  80, 130, 110, &T );

    ///
    // first polygon:  entirely within region
    ///

    wl = 0;
    wl = C.clipPolygon( 4, quad1x, quad1y, wx, wy, 10, 110, 50, 150 );
    T.setColor ( 1.0f, 0.0f, 0.0f );		// red
    T.printLoop( 4, quad1x, quad1y );
    T.printPoly( wl, wx, wy );

    ///
    // second polygon:  entirely outside region
    ///
    wl = 0;
    T.setColor ( 0.0f, 1.0f, 0.0f );	// green
    T.printLoop( 4, quad2x, quad2y );
    wl = C.clipPolygon( 4, quad2x, quad2y, wx, wy, 10, 110, 50, 150 );
    // shouldn't draw anything!
    if( wl > 0 ) {
        T.printPoly( wl, wx, wy );
    }

    ///
    // third polygon:  halfway outside on left
    ///

    wl = 0;
    wl = C.clipPolygon( 4, quad3x, quad3y, wx, wy, 30, 10, 70, 80 );
    T.setColor ( 0.0f, 0.0f, 1.0f );		// blue
    T.printLoop( 4, quad3x, quad3y );
    T.printPoly( wl, wx, wy );

    ///
    // fourth polygon:  part outside on right
    ///

    wl = 0;
    wl = C.clipPolygon( 4, quad4x, quad4y, wx, wy, 10, 110, 50, 150 );
    T.setColor ( 1.0f, 0.0f, 1.0f );		// magenta
    T.printLoop( 4, quad4x, quad4y );
    T.printPoly( wl, wx, wy );

    ///
    // fifth polygon:  outside on left and bottom
    ///

    wl = 0;
    wl = C.clipPolygon( 5, pent1x, pent1y, wx, wy, 90, 34, 120, 60 );
    T.setColor ( 1.0f, 0.5f, 1.0f );		// red-greenish-blue
    T.printLoop( 5, pent1x, pent1y );
    T.printPoly( wl, wx, wy );

    ///
    // sixth polygon:  outside on top, right, and bottom
    ///

    wl = 0;
    wl = C.clipPolygon( 7, hept1x, hept1y, wx, wy, 90, 80, 130, 110 );
    T.setColor ( 0.7f, 0.7f, 0.7f );		// gray
    T.printLoop( 7, hept1x, hept1y );
    T.printPoly( wl, wx, wy );

    sf::RenderWindow App(sf::VideoMode(300, 300), "Clipping Test");
    while (App.isOpen())
    {
        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                App.close();

            // Keypress
            if( Event.type == sf::Event::KeyPressed )
                if( keyTyped(Event.key.code) )
                    App.close();
        }

        // Clear screen
        App.clear();

        // Draw your canvas
        T.draw (App);

        App.display();
    }

    return 0;

}

//
//  tessMain
//
//  Main program for tessellation assignment.
//
//  This code can be compiled as either C or C++.
//
//  Students should not be modifying this file.
//
//  Updated 2014/10 by Vasudev Prasad Bethamcherla.
//

#ifdef __cplusplus
#include <cstdlib>
#include <iostream>
#else
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#endif

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <Windows.h>
#include <GL/gl.h>
#endif

#include "shaderSetup.h"
#include "simpleShape.h"
#include "cgShape.h"

#ifdef __cplusplus
using namespace std;
#endif

// The shapes that we can draw
#define CUBE 0
#define CYLINDER 1
#define CONE 2
#define SPHERE 3
int currentShape = CUBE;

// subdivision for tessellation
int division1 = 1;
int division2 = 1;

// are we animating?
bool animating = false;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// buffer information
bool bufferInit = false;
GLuint vbuffer, ebuffer;
GLuint program;

// shader arguments...rotation of object.
GLuint theta; // theta uniform location
float angles[3] = {30.0, 30.0, 0.0};
float angleInc = 5.0;

///
// create a new shape by tesselating one of
// the 4 basic objects
///
void createNewShape() {

    // clear your old shape
    clearShape();

    // create the new shape..
    switch( currentShape )
    {
        case CUBE:     makeCube( division1 ); break;
        case CYLINDER: makeCylinder( 0.5, division1, division2 ); break;
        case CONE:     makeCone( 0.5, division1, division2 ); break;
        case SPHERE:   makeSphere( 0.5, division1, division2 ); break;

    }

    // get and load the vertices for your shape
    int NumElements = nVertices() / 3;
    float *points = getVertices();
    int dataSize = nVertices() * 4 * sizeof (float);

    // get and load the element data
    GLushort *elements = getElements();
    int edataSize = nVertices() * sizeof (GLushort);

    // setup the vertex buffer
    if( bufferInit )
        glDeleteBuffers( 1, &vbuffer );
    glGenBuffers( 1, &vbuffer );
    glBindBuffer( GL_ARRAY_BUFFER, vbuffer );
    glBufferData( GL_ARRAY_BUFFER, dataSize, points, GL_STATIC_DRAW );

    // setup the element buffer
    if( bufferInit )
        glDeleteBuffers( 1, &ebuffer );
    glGenBuffers( 1, &ebuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, edataSize, elements,
                  GL_STATIC_DRAW );

    // buffers have been created now, and must
    // be deleted before new shapes are created
    bufferInit = true;
}

// OpenGL initialization
void init() {

    // Load shaders and use the resulting shader program
    program = shaderSetup( "shader.vert", "shader.frag" );
    if( !program ) {
#ifdef __cplusplus
        cerr << "Error setting up shaders - "
	     << errorString(shaderErrorCode) << endl;
#else
        fprintf( stderr, "Error setting up shaders - %s\n",
	    errorString(shaderErrorCode) );
#endif
        exit(1);
    }

    glEnable( GL_DEPTH_TEST );
    glEnable(GL_CULL_FACE);
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glCullFace( GL_BACK );
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // initally create a cube
    createNewShape();
}

#ifdef __cplusplus
extern "C" {
#endif

void display( void ) {

    // clear the frame buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // bind our vertex buffer
    glBindBuffer( GL_ARRAY_BUFFER, vbuffer );

    // bind our element array buffer
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer );

    // set up our attribute variables
    glUseProgram( program );
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(0) );

    // pass in our rotation as a uniform variable
    theta = glGetUniformLocation(program, "theta");
    glUniform3fv( theta, 1, angles );

    // draw our shape
    glDrawElements( GL_TRIANGLES, nVertices(),  GL_UNSIGNED_SHORT, (void *)0 );

    // swap the framebuffers
    glutSwapBuffers();
}

// Can cause gimbal lock which also happened on Apollo 11
// http://en.wikipedia.org/wiki/Gimbal_lock#Gimbal_lock_on_Apollo_11
// Solution? Use Quaternions (Taught in Comp. Animation: Algorithms)
//
// TIDBIT:
// Quaternion plaque on Brougham (Broom) Bridge, Dublin, which says:
// 
//    "Here as he walked by
//    on the 16th of October 1843
// 
//    Sir William Rowan Hamilton 
//    
//    in a flash of genius discovered
//    the fundamental formula for
//    quaternion multiplication
//    i^2 = j^2 = k^2 = ijk = -1
//    & cut it on a stone of this bridge"

void animate() {
    int i;
    static int level = 0;

    if( level >= 450 ) {
        level = 0;
	animating = false;
    }

    if( !animating ) {
        return;
    }

    if( level < 150 ) {
        angles[0] -= angleInc / 3;
    } else if( level < 300 ) {
        angles[1] -= angleInc / 3;
    } else {
        angles[2] -= angleInc / 3;
    }

    ++level;
    glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y ) {

    switch( key ) {

	// automated animation
        case 'a': animating = true; break;

	// incremental rotation along the axes
        case 'x': angles[0] -= angleInc; break;
        case 'y': angles[1] -= angleInc; break;
        case 'z': angles[2] -= angleInc; break;
        case 'X': angles[0] += angleInc; break;
        case 'Y': angles[1] += angleInc; break;
        case 'Z': angles[2] += angleInc; break;

	// shape selection
        case '1':  case 'c': currentShape = CUBE; createNewShape(); break;
        case '2':  case 'C': currentShape = CYLINDER; createNewShape(); break;
        case '3':  case 'n': currentShape = CONE; createNewShape(); break;
        case '4':  case 's': currentShape = SPHERE; createNewShape(); break;

	// tessellation factors
        case '+': division1++; createNewShape(); break;
        case '=': division2++; createNewShape(); break;
        case '-': if( division1 > 1 ) {
                    division1--;
                    createNewShape();
		  }
		  break;
        case '_': if( division2 > 1)  {
                    division2--;
                    if (currentShape != CUBE) createNewShape();
                  }
                  break;

	// termination
        case 033:  // Escape key
        case 'q': case 'Q':
            exit( 0 );
    }

    glutPostRedisplay();
}

#ifdef __cplusplus
}
#endif

int main( int argc, char **argv ) {

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "CG - Tessellation Assignment" );

#ifndef __APPLE__
    glewInit();
#endif

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutIdleFunc( animate );

    glutMainLoop();
    return 0;
}

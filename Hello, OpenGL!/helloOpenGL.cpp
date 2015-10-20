//
//  helloOpenGL
//
//  Main program for the "Hello, OpenGL" assignment.
//
// This code can be compiled as either C or C++.
//
//  Students should not be modifying this file.
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

#ifdef __cplusplus
using namespace std;
#endif

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// buffer information
bool bufferInit = false;
GLuint buffer, ebuffer;
GLuint program;

// geometry data
float datapoints[] = {  0.25, -0.75, 0.0, 1.0,
                        0.50, -0.75, 0.0, 1.0,
                        0.25,  0.15, 0.0, 1.0,

                        0.50, -0.75, 0.0, 1.0,
                        0.50,  0.15, 0.0, 1.0,
                        0.25,  0.15, 0.0, 1.0,

                        0.25,  0.25, 0.0, 1.0,
                        0.50,  0.25, 0.0, 1.0,
                        0.25,  0.50, 0.0, 1.0,

                        0.50,  0.25, 0.0, 1.0,
                        0.50,  0.50, 0.0, 1.0,
                        0.25,  0.50, 0.0, 1.0,

                       -0.25, -0.75, 0.0, 1.0,
                        0.00, -0.75, 0.0, 1.0,
                       -0.25,  0.75, 0.0, 1.0,

                        0.00, -0.75, 0.0, 1.0,
                        0.00,  0.75, 0.0, 1.0,
                       -0.25,  0.75, 0.0, 1.0,

                       -0.75, -0.75, 0.0, 1.0,
                       -0.50, -0.75, 0.0, 1.0,
                       -0.75,  0.75, 0.0, 1.0,

                       -0.50, -0.75, 0.0, 1.0,
                       -0.50,  0.75, 0.0, 1.0,
                       -0.75,  0.75, 0.0, 1.0,

                       -0.50, -0.12, 0.0, 1.0,
                       -0.25, -0.12, 0.0, 1.0,
                       -0.50,  0.12, 0.0, 1.0,

                       -0.25, -0.12, 0.0, 1.0,
                       -0.25,  0.12, 0.0, 1.0,
                       -0.50,  0.12, 0.0, 1.0,
};

GLushort elems[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
                    12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
                    24, 25, 26, 27, 28, 29};

int nverts = 30;


/**
 * creates the surprise scene
 */
void createScene()
{

    // get and load the verticies for your shape
    float *points = datapoints;
    int dataSize = nverts * 4 * sizeof (float);

    // get and load the element data
    GLushort *elements = elems;
    int edataSize = nverts * sizeof (GLushort);

    // setup the vertex buffer
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, dataSize, points, GL_STATIC_DRAW );
    bufferInit = true;

    // setup the element buffer
    glGenBuffers( 1, &ebuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, edataSize, elements, GL_STATIC_DRAW );
}


// OpenGL initialization
void init() {

    // Load shaders and use the resulting shader program
    program = shaderSetup( "shader.vert", "shader.frag" );
    if (!program) {
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
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
    glCullFace(GL_BACK);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // set up the initial scene
    createScene();
}

#ifdef __cplusplus
extern "C" {
#endif


void
display( void )
{
    // clear your frame buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // bind your vertex buffer
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // bind your element array buffer
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer );

    // set up your attribute variables
    glUseProgram( program );
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(0) );

    // draw your shape
    glDrawElements (GL_TRIANGLES, nverts,  GL_UNSIGNED_SHORT, (void *)0);

    // swap the buffers
    glutSwapBuffers();
}


void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
        case 033:  // Escape key
        case 'q': case 'Q':
            exit( 0 );
        break;
    }

    glutPostRedisplay();
}

#ifdef __cplusplus
}
#endif

int main (int argc, char **argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "Hello, OpenGL!" );

#ifndef __APPLE__
    glewInit();
#endif

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();
    return 0;
}


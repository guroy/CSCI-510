//
//  transMain
//
//  Main program for transformation assignment
//
//  This code can be compiled as either C or C++.
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
#ifdef WIN32
#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <Windows.h>
#endif
#endif

#include "shaderSetup.h"
#include "simpleShape.h"
#include "teapot.h"
#include "viewParams.h"

#ifdef __cplusplus
using namespace std;
#endif

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// vertex and element array IDs
// one for each object to be drawn
GLuint buffer[1];
GLuint ebuffer[1];
int NumElements;

int counter = 0;
bool cameraAdjust = false;
bool transformsOn = false;

// program IDs...for program and parameters
GLuint program;

bool bufferInit = false;
int numVerts[1];

// program control
int viewMode = 1;

void createShapes( void )
{
    // make the teapot
    clearShape();
    makeTeapot();

    // retrieve the teapot's vertices and connectivity info
    NumElements = nVertices() / 3;
    float *points = getVertices();
    int dataSize = nVertices() * 4 * sizeof (float);
    GLushort *elements = getElements();
    int edataSize = nVertices() * sizeof (GLushort);

    // generate the vertex buffer
    glGenBuffers( 1, &buffer[0] );
    glBindBuffer( GL_ARRAY_BUFFER, buffer[0] );
    glBufferData( GL_ARRAY_BUFFER, dataSize, points, GL_STATIC_DRAW );

    // generate the element array buffer
    glGenBuffers( 1, &ebuffer[0] );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer[0] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, edataSize,
        elements, GL_STATIC_DRAW );

    // store the vertex count
    numVerts[0] = nVertices();
}


// OpenGL initialization
void init()
{

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

    // Some openGL initialization...probably best to keep
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // create the geometry for your shapes.
    createShapes();
}


#ifdef __cplusplus
extern "C" {
#endif

void display( void )
{
    // clear and draw params..
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    // bind buffers
    glBindBuffer( GL_ARRAY_BUFFER, buffer[0] );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer[0] );

    // use program
    glUseProgram( program );

    // set up the vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    // set up viewing and projection parameters

    if( viewMode == 1 )
        setUpFrustum( program );
    else if( viewMode == 2 )
        setUpOrtho( program );

    // set up camera
    //
    // changing the camera sets eyepoint to (0,1.3,-0.5), lookat
    // to (0,-0.4,-1.0), and up to (0,1,0)

    if( cameraAdjust )
        setUpCamera( program, 0.0f, 1.3f, -0.5f,
            0.0f, -0.4f, -1.0f, 0.0f, 1.0f, 0.0f );
    else
        clearCamera( program );

    // set up transformations
    //
    // transformations are applied in this order (if you are having trouble
    // recreating the solution image, check your order of matrix
    // multiplication):
    //
    //    scale Y by 2
    //    rotate around Z by 335 degrees
    //    rotate around Y by 10 degrees
    //    translate in X by -0.2
    //    translate in Y by 0.2

    if( transformsOn )
        setUpTransforms( program, 1.0f, 2.0f, 1.0f,
            0.0f, 10.0f, 335.0f,
            -0.2f, 0.2f, 0.0f );
    else
        clearTransforms( program );

    // draw your shape
    glDrawElements( GL_TRIANGLES, numVerts[0], GL_UNSIGNED_SHORT, (void *)0 );

    // swap the buffers
    glutSwapBuffers();
}


void keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
        case '1':
            viewMode = 1;
            break;

        case '2':
            viewMode = 2;
            break;

        case 033:  // Escape key
        case 'q': case 'Q':
            exit( 0 );
            break;
    }

    glutPostRedisplay();
}

void mouse( int button, int state, int x, int y )
{
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
        counter++;

    switch( counter % 4 ) {
        case 0:
            // sets defaults
            cameraAdjust = false;
            transformsOn = false;
            break;
        case 1:
            // turn on transformations
            transformsOn = true;
            break;
        case 2:
            // turn camera adjust on, turn transformations off
            cameraAdjust = true;
            transformsOn = false;
            break;
        case 3:
            // turn transformations back on
            transformsOn = true;
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
    glutCreateWindow( "CG - 3D Transformations and Viewing" );

#ifndef __APPLE__
    glewInit();
#endif

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutMouseFunc( mouse );

    glutMainLoop();
    return 0;
}

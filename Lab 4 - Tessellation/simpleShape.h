//
//  simpleShape.h
//
//  Prototypes for routines for adding triangles to create a new mesh.
//
//  Students are not to modify this file.
//

#ifndef _SIMPLESHAPE_H_
#define _SIMPLESHAPE_H_

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

void clearShape( void );

void addTriangle( float x0, float y0, float z0,
                  float x1, float y1, float z1,
                  float x2, float y2, float z2 );

GLushort *getElements( void );

float *getVertices( void );

int nVertices( void );

#endif

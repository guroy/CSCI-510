//
//  cgShape.h
//
//  Prototypes for tessellation routines to be supplied by students.
//
//  Students should not modify this file.
//

#ifndef _CGSHAPE_H_
#define _CGSHAPE_H_

void makeCube( int subdivisions );
void makeCylinder( float radius, int radialDivisions, int heightDivisions );
void makeCone( float radius, int radialDivisions, int heightDivisions );
void recursiveTriangle(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, int subdivision, float radius);
void makeSphere(float radius, int slices, int stacks);

#endif

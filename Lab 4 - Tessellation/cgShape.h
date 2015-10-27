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
void makeSphere( float radius, int slices, int stacks );

#endif

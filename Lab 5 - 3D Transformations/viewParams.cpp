//
//  viewParams
//
//  Created by Joe Geigel on 1/23/13.
//
//  Contributor:  Guillaume Roy
//
//  This code can be compiled as either C or C++.
//

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#else
#ifdef WIN32
#include <windows.h>
#endif
#include <Windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif

#include "viewParams.h"

///
// This function sets up the view and projection parameter for a frustum
// projection of the scene. See the assignment description for the values
// for the projection parameters.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
//
///
void setUpFrustum (GLuint program)
{
    // Add your code here.
	// 1.0f means frustum 2.0f means orthographic
	glUniform1f(glGetUniformLocation(program, "choiceProjection"), 1.0f);
}


///
// This function sets up the view and projection parameter for an
// orthographic projection of the scene. See the assignment description
// for the values for the projection parameters.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
//
///
void setUpOrtho (GLuint program)
{
    // Add your code here.
	// 1.0f means frustum 2.0f means orthographic
	glUniform1f(glGetUniformLocation(program, "choiceProjection"), 2.0f);
}


///
// This function clears any transformations, setting the values to the
// defaults: no scaling (scale factor of 1), no rotation (degree of
// rotation = 0), and no translation (0 translation in each direction).
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
//
///
void clearTransforms(GLuint program)
{
	// Add your code here.
	GLfloat scale[] = { 1.0f, 1.0f, 1.0f },
		rotate[] = { 0.0f, 0.0f, 0.0f },
		translate[] = { 0.0f, 0.0f, 0.0f };

	// send all values of transformation to shader
	glUniform3fv(glGetUniformLocation(program, "sc"), 1, scale);
	glUniform3fv(glGetUniformLocation(program, "ro"), 1, rotate);
	glUniform3fv(glGetUniformLocation(program, "tr"), 1, translate);
}


///
// This function sets up the transformation parameters for the vertices
// of the teapot.  The order of application is specified in the driver
// program.
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param scaleX - amount of scaling along the x-axis
// @param scaleY - amount of scaling along the y-axis
// @param scaleZ - amount of scaling along the z-axis
// @param rotateX - angle of rotation around the x-axis, in degrees
// @param rotateY - angle of rotation around the y-axis, in degrees
// @param rotateZ - angle of rotation around the z-axis, in degrees
// @param translateX - amount of translation along the x axis
// @param translateY - amount of translation along the y axis
// @param translateZ - amount of translation along the z axis
///
void setUpTransforms( GLuint program,
    GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ,
    GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ,
    GLfloat translateX, GLfloat translateY, GLfloat translateZ )
{
    // Add your code here.
	GLfloat scale[] = { scaleX, scaleY, scaleZ },
		rotate[] = { rotateX, rotateY, rotateZ },
		translate[] = { translateX, translateY, translateZ };

	// send all values of transformation to shader
	glUniform3fv(glGetUniformLocation(program, "sc"), 1, scale);
	glUniform3fv(glGetUniformLocation(program, "ro"), 1, rotate);
	glUniform3fv(glGetUniformLocation(program, "tr"), 1, translate);
}


///
// This function clears any changes made to camera parameters, setting the
// values to the defaults: eyepoint (0.0,0.0,0.0), lookat (0,0,0.0,-1.0),
// and up vector (0.0,1.0,0.0).
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void clearCamera( GLuint program )
{
    // Add your code here.
	GLfloat eye[] = { 0.0f, 0.0f, 0.0f },
		lookat[] = { 0.0f, 0.0f, -1.0f },
		up[] = { 0.0f, 1.0f, 0.0f };

	// send all values of transformation to shader
	glUniform3fv(glGetUniformLocation(program, "ey"), 1, eye);
	glUniform3fv(glGetUniformLocation(program, "la"), 1, lookat);
	glUniform3fv(glGetUniformLocation(program, "up"), 1, up);
}

///
// This function sets up the camera parameters controlling the viewing
// transformation.
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param eyeX - x coordinate of the camera location
// @param eyeY - y coordinate of the camera location
// @param eyeZ - z coordinate of the camera location
// @param lookatX - x coordinate of the lookat point
// @param lookatY - y coordinate of the lookat point
// @param lookatZ - z coordinate of the lookat point
// @param upX - x coordinate of the up vector
// @param upY - y coordinate of the up vector
// @param upZ - z coordinate of the up vector
///
void setUpCamera( GLuint program,
    GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ,
    GLfloat lookatX, GLfloat lookatY, GLfloat lookatZ,
    GLfloat upX, GLfloat upY, GLfloat upZ )
{
    // Add your code here.
	GLfloat eye[] = { eyeX, eyeY, eyeZ },
		lookat[] = { lookatX, lookatY, lookatZ },
		up[] = { upX, upY, upZ };

	// send all values of transformation to shader
	glUniform3fv(glGetUniformLocation(program, "ey"), 1, eye);
	glUniform3fv(glGetUniformLocation(program, "la"), 1, lookat);
	glUniform3fv(glGetUniformLocation(program, "up"), 1, up);
}

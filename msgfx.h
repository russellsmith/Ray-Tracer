/*
 * Copyright (c) 2005-2010 Michael Shafae.
 * All rights reserved.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $Id$
 *
 *
 */

#ifndef _MSGFX_H_
#define _MSGFX_H_

#include <cstdio>
#include <cstdlib>

#ifdef __APPLE__
/* Apple's weird location of their OpenGL & GLUT implementation */
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#elif WIN32
#include <GL/glut.h>
#else
/* Unix, Linux, and BSD */
#include <GL/glut.h>
#endif


/*
 * Handy OpenGL debugging macros
 */

#ifndef NDEBUG

#define msglPrintMatrix16fv( matrix ) { \
  int __glPrintMatrixIndex = 0; \
    for( __glPrintMatrixIndex = 0; __glPrintMatrixIndex < 4; __glPrintMatrixIndex++ ){ \
      fprintf( stderr, "%.2f %.2f %.2f %.2f\n", matrix[__glPrintMatrixIndex + 0], matrix[__glPrintMatrixIndex + 4], matrix[__glPrintMatrixIndex + 8], matrix[__glPrintMatrixIndex + 12] ); \
    } \
}

#define msglError( ) _msglError( stderr, __FILE__, __LINE__ )

#define msglAssert( ) assert( glGetError( ) == GL_NO_ERROR )

// Various macros to catch myself from making a stupid mistake.
#define msglEnd( ) glEnd( ); msglError( )

#define msglEnable( x ) assert( glIsEnabled((x)) != GL_TRUE ); glEnable((x))

#define msglDisable( x ) assert( glIsEnabled((x)) == GL_TRUE ); glDisable((x));

#define msglEnableClientState( x ) assert( glIsEnabled((x)) != GL_TRUE ); glEnableClientState((x))

#define msglDisableClientState( x ) assert( glIsEnabled((x)) == GL_TRUE ); glDisableClientState((x));

#else

#define msglPrintMatrix16fv( matrix )

#define msglError( )

#define msglAssert( )

#define msglEnd( ) glEnd( )

#define msglEnable( x ) glEnable( x )

#define msglDisable( x ) glDisable( x )

#define msglEnableClientState( x ) glEnableClientState((x))

#define msglDisableClientState( x ) glDisableClientState((x))

#endif


enum{X = 0, Y, Z, W};

enum{R = 0, G, B, A};

// Used to define how many decimal places to print in most classes
#define IOS_FP_PRECISION 5

void _msglError( FILE *out, const char *filename, int line );

// Old junk that needs to be cleaned up
/*void msGfxTriangle( float red, float green, float blue );

void msGfxUnitAxis( void );

void msGfxDrawCube( GLfloat fSize );

void msGfxPrintVector( FILE *s, const float *v, int size );

int msGfxExtensionSupported( const char *extension );

void msGfxPrintOpenGLState( FILE *fh );*/

#endif

/*
 * Copyright (c) 2005-2009 Michael Shafae
 * All rights reserved.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $Id$
 *
 *
 * Macros for some simple math and such
 *
 */

#ifndef _MSGFX_MATH_H_
#define _MSGFX_MATH_H_

#ifdef _WIN32
#include <float.h>
#define isnan( x ) _isnan( x )
#endif

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

#define DEG2RAD( theta ) ((theta) * (M_PI/180.0))

#define RAD2DEG( theta ) ((theta) * (180.0/M_PI))

#ifndef SQR
#define SQR( x ) ((x) * (x))
#endif

#ifndef ABS
#define ABS( x ) ((x) < (0) ? (-x) : (x))
#endif

#ifndef MAX
#define MAX( a, b ) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN( a, b ) ((a) < (b) ? (a) : (b))
#endif

// A reasonable FP tolerance
#define FP_EPSILON 1e-9
#define ALMOST_ZERO 1e-9

#define FP_EQUAL(a, b, delta) ( ((a) == (b)) || \
                              ((a)-(delta) < (b) && \
                              (a)+(delta) > (b)) )

#define FP_LT(a, b, delta)  (fabs((a) - (b)) < (delta))

#define FP_GT(a, b, delta)  (fabs((a) - (b)) > (delta))


//double remainderd( double x, double y );
//double remainderf( float x, float y );

//void normal(float n[3], float p[3], float q[3], float r[3]);
//void normalize(float n[3]);
//void normal(float n[3], int p[3], int q[3], int r[3]);
//void vecProd(float n[3], float u[3], float v[3]);
//float dotProd(float a[3], float b[3]);

#endif

/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 484
 * September 28, 2010
 *
 * Reads a PLY format model file and returns an indexed triangle face list.
 *
 */

#include "FaceList.h"

#ifndef _PLYMODEL_H_
#define _PLYMODEL_H_

FaceList* readPlyModel( const char* filename );

#endif
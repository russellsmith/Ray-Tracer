/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 484
 * September 28, 2010
 *
 * Indexed triangle face list data structure. Uses a 2D array of
 * floats for storage.
 */


#ifndef _FACELIST_H_
#define _FACELIST_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include "Vector3.h"

#ifndef MIN
#define MIN( x, y ) ((x) <= (y) ? (x) :  (y))
#endif
#ifndef MAX
#define MAX( x, y ) ((x) >= (y) ? (x) :  (y))
#endif
#ifndef ABS
#define ABS( x )    ((x) >= 0.0 ? (x) : -(x))
#endif


class FaceList{

private:
  // Model's file name
  std::string _filename;
  unsigned int _vertexCount;
  unsigned int _faceCount;

public:
  /*
   * Adjust the types of the following pointers
   * according to the name of your Vector class.
   */
  // Array of vertices (decimal number type)
  float **vertices;
  // Array of faces (indices into the array of vertices)
  int **faces;
  // Array of face normals (decimal number type)
  float **faceNormals;
  // Array of vertex normals (decimal number type)
  float **vertexNormals;

  FaceList( const char *filename, unsigned int vertexCount, unsigned int  faceCount ) : _filename( filename ), _vertexCount( vertexCount ), _faceCount( faceCount )
  {
    unsigned int i;
    if( !(vertices = (float**)calloc( _vertexCount, sizeof(float*))) ){
      std::cerr << "Didn't allocated memory for vertex array." << std::endl;
    }
    for( i = 0; i < _vertexCount; i++ ){
      if( !(vertices[i] = (float*)calloc( 4, sizeof(float) )) ){
        std::cerr << "Couldn't allocate memory for the vertices at location " << i << std::endl;
      }
    }
    
    if( !(faces = (int**)calloc( _faceCount, sizeof(int*))) ){
      std::cerr << "Didn't allocated memory for face array." << std::endl;
    }
    for( i = 0; i < _faceCount; i++ ){
      if( !(faces[i] = (int*)calloc( 3, sizeof(int) )) ){
        std::cerr << "Couldn't allocate memory for the vertices at location " << i << std::endl;
      }
    }
    
    if( !(faceNormals = (float**)calloc( _faceCount, sizeof(float*))) ){
      std::cerr << "Didn't allocated memory for vertex array." << std::endl;
    }
    for( i = 0; i < _faceCount; i++ ){
      if( !(faceNormals[i] = (float*)calloc( 3, sizeof(float) )) ){
        std::cerr << "Couldn't allocate memory for the vertices at location " << i << std::endl;
      }
    }

    if( !(vertexNormals = (float**)calloc( _vertexCount, sizeof(float*))) ){
      std::cerr << "Didn't allocated memory for vertex array." << std::endl;
    }
    for( i = 0; i < _vertexCount; i++ ){
      if( !(vertexNormals[i] = (float*)calloc( 3, sizeof(float) )) ){
        std::cerr << "Couldn't allocate memory for the vertices at location " << i << std::endl;
      }
    }
    
  };
  
  ~FaceList( ){
   	for( unsigned int i = 0; i < _vertexCount; i++ ){
   		free( vertices[i] );
      free( vertexNormals[i] );
   	}
    for( unsigned int i = 0; i < _faceCount; i++ ){
      free( faces[i] );
      free( faceNormals[i] );
    }
   	free( vertices );
    free( faces );
    free( faceNormals );
    free( vertexNormals );
  };

  unsigned int vertexCount( ){
    return _vertexCount;
  }

  unsigned int faceCount( ){
    return _faceCount;
  }
  
  std::string filename( ){
    return _filename;
  }
  
  void computeFaceNormals( ){
    // do something...
	  msgfx::Vector3f vec1, vec2, normal;
	  for(unsigned int i = 0; i < _faceCount; ++i)
	  {
		  vec1.x(vertices[faces[i][0]][0] - vertices[faces[i][1]][0]);
		  vec1.y(vertices[faces[i][0]][1] - vertices[faces[i][1]][1]);
		  vec1.z(vertices[faces[i][0]][2] - vertices[faces[i][1]][2]);
		  vec2.x(vertices[faces[i][2]][0] - vertices[faces[i][1]][0]);
		  vec2.y(vertices[faces[i][2]][1] - vertices[faces[i][1]][1]);
		  vec2.z(vertices[faces[i][2]][2] - vertices[faces[i][1]][2]);

		  vec1.normalize();
		  vec2.normalize();

		  normal = msgfx::cross(vec2, vec1);

		  faceNormals[i][0] = normal.x();
		  faceNormals[i][1] = normal.y();
		  faceNormals[i][2] = normal.z();		  
	  }
  }
  
  void computeVertexNormals( ){
    // do something...
	  unsigned int i, j;
	  double magnitude;

	  for(i = 0; i < _vertexCount; ++i)
	  {
		  vertexNormals[i][0] = 0.0;
		  vertexNormals[i][1] = 0.0;
		  vertexNormals[i][2] = 0.0;
	  }

	  for(i = 0; i < _faceCount; ++i)
	  {
		  for(j = 0; j < 3; ++j)
		  {
			  vertexNormals[faces[i][j]][0] += faceNormals[i][0];
			  vertexNormals[faces[i][j]][1] += faceNormals[i][1];
			  vertexNormals[faces[i][j]][2] += faceNormals[i][2];
		  }
	  }

	  for(i = 0; i < _vertexCount; ++i)
	  {
		  // Normalize vertex normals
		  magnitude = sqrt(vertexNormals[i][0] * vertexNormals[i][0] + vertexNormals[i][1] * vertexNormals[i][1]
			+ vertexNormals[i][2] * vertexNormals[i][2]);
			vertexNormals[i][0] /= magnitude;
			vertexNormals[i][1] /= magnitude;
			vertexNormals[i][2] /= magnitude;
	  }

	  
  }
};

#endif
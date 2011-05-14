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


#ifndef _MSGFX_VECTOR3_H_
#define _MSGFX_VECTOR3_H_

#include <iostream>
#include <ostream>
#include <vector>
#include "msgfx.h"


namespace msgfx{

template <class T>
class Vector3{
public:
  const static unsigned int dimension = 3;

private:

  T components[dimension];

  
public:

  // Constructor
  Vector3( const Vector3<T>& v );
  explicit Vector3( const Vector3<T>* v );
  //explicit Vector3( const HomogeneousVector3<T>& v );
  //explicit Vector3( const HomogeneousVector3<T>* v );
  explicit Vector3( );
  explicit Vector3( const T& x, const T& y, const T& z );
  explicit Vector3( const T *array, size_t size );
  explicit Vector3( const std::vector<T>& v );

  // Deconstructor
  // - none

  // Operators
  Vector3<T>& operator =( const Vector3<T> &src );
  bool operator ==( const Vector3<T>& src ) const;
  bool operator !=( const Vector3<T>& src ) const;
  bool operator <( const Vector3<T>& src ) const;
  const Vector3<T>& operator +=( const Vector3<T> &v );
  const Vector3<T>& operator +=( const T scalar );
  const Vector3<T>& operator -=( const Vector3<T> &v );
  const Vector3<T>& operator -=( const T scalar );
  const Vector3<T>& operator *=( const T scalar );
  const Vector3<T>& operator /=( const T scalar );

  Vector3<T> operator +( const Vector3<T> &v ) const;
  Vector3<T> operator -( const Vector3<T> &v ) const;
  Vector3<T> operator -( ) const;
  Vector3<T> operator *( const T scalar) const;
  Vector3<T> operator /( const T scalar ) const;

  const T operator []( const int index ) const;
  T& operator []( const int index );
  T* c_array( );
  const T* constPtr( ) const;

  Vector3<T>& set( const T& x, const T& y, const T& z );
  Vector3<T>& set( const T *data, size_t size );
  
  const T& x( ) const;
  const T& y( ) const;
  const T& z( ) const;

  void x( const T& a );
  void y( const T& b );
  void z( const T& c );

  static unsigned int dimensions( ){
    return( dimension );
  }

  // Math
  void normalize( );
  void setLength( T length );
  int sign( const Vector3<T>& v ) const;
  double length( ) const;
  T squaredLength( ) const;
  double angle( const Vector3<T>& v ) const;
  double cosTheta( const Vector3<T> &v ) const;
  double distanceFrom( const Vector3<T>& v ) const;
  double squaredDistanceFrom( const Vector3<T>& v ) const;
  double infiniteDistanceFrom(const Vector3<T>& v) const;
  double manhattanDistanceFrom(const Vector3<T>& v) const;
  double distanceToPlane(const Vector3<T>& point, const Vector3<T>& normal) const;
	void rotateX( const double angle );
  void rotateY( const double angle );
  void rotateZ( const double angle );
  T dot( const Vector3<T> &v ) const;
  Vector3<T> cross( const Vector3<T> &v1, const Vector3<T> &v2 ) const;

  // I/O
  void write( std::ostream &out ) const;
  void write_row( std::ostream &out) const;
};

// Given three points of a triangle, give the unit normal
template <class T>
Vector3<T> normal( Vector3<T> &a, Vector3<T> &b, Vector3<T> &c ){
  // Assuming right hand rule
  Vector3<T> p = b - a;
  Vector3<T> q = c - a;
  Vector3<T> n = cross( p, q );
  n.normalize( );
  return( n );
}

template <class T>
Vector3<T> cross( const Vector3<T> &u, const Vector3<T> &v ){
  return( Vector3<T>( ((u[Y] * v[Z]) -
                       (u[Z] * v[Y])),
                      ((u[Z] * v[X]) -
                       (u[X] * v[Z])),
                      ((u[X] * v[Y]) -
                       (u[Y] * v[X])) ) );
}

// Basic I/O
template <class T>
std::ostream& operator <<( std::ostream &out, const Vector3<T> &v ){
  v.write( out );
  return( out );
}

//typedef Vector3<char> Vector3b;
//typedef Vector3<short> Vector3s;
//typedef Vector3<int> Vector3i;
//typedef Vector3<long> Vector3l;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

} // end namespace msgfx

#endif

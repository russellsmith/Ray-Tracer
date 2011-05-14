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

#include <cmath>
#include <iomanip>
#include <cassert>
#include "Vector3.h"
#include "Math.h"

namespace msgfx {

// Constructors
template <class T>
Vector3<T>::Vector3( const Vector3<T>& v ){
  for( unsigned int i = 0; i < dimension; i++ ){
    components[i] = v.components[i];
  }
}

template <class T>
Vector3<T>::Vector3( const Vector3<T>* v ){
  for( unsigned int i = 0; i < dimension; i++ ){
    components[i] = v->components[i];
  }
}

/*
template <class T>
Vector3<T>::Vector3( const HomogeneousVector3<T>& v ){
  HomogeneousVector3<T> u( v );
  u.homogenize( );
  for( unsigned int i = 0; i < dimension; i++ ){
    components[i] = u.components[i];
  }
}

template <class T>
Vector3<T>::Vector3( const HomogeneousVector3<T>* v ){
  HomogeneousVector3<T> u( v );
  u.homogenize( );
  for( unsigned int i = 0; i < dimension; i++ ){
    components[i] = u->components[i];
  }
}
*/

template <class T>
Vector3<T>::Vector3( ){
  for( unsigned int i = 0; i < dimension; i++ ){
    components[i] = static_cast<T>(0);
  }
}

template <class T>
Vector3<T>::Vector3( const T& x, const T& y, const T& z ){
  components[X] = x;
  components[Y] = y;
  components[Z] = z;
}

template <class T>
Vector3<T>::Vector3( const T *array, size_t size ){
  for( unsigned int i = 0; i < size; i++ ){
    components[i] = array[i];
  }
  for( unsigned int i = size; i < dimension; i++ ){
    components[i] = static_cast<T>(0);
  }
}

/*
template <class T>
Vector3<T>::Vector3( const Vector3<T>* v ){
  for( unsigned int i = 0; i < v->dimensions( ); i++ ){
    components[i] = (*v)[i];
  }
  components[W] = static_cast<T>(1);
}
*/

template <class T>
Vector3<T>::Vector3( const std::vector<T>& v ){
  assert( v.size( ) <= dimension );
  for( unsigned int i = 0; i < v.size( ); i++ ){
    components[i] = v[i];
  }
  if( v.size( ) < dimension ){
    // pack with zeros
    for( unsigned int i = v.size( ); i < dimension; i++ ){
      components[i] = static_cast<T>(0);
    }
  }
}

// Assignment operators
template <class T>
Vector3<T>& Vector3<T>::operator =( const Vector3<T> &src ){
  for( unsigned int i = 0; i < dimension; i++ ){
    components[i] = src[i];
  }
  return( *this );
}

template <class T>
bool Vector3<T>::operator ==( const Vector3<T>& src ) const{
  bool rv = true;
  for( unsigned int i = 0; i < dimension; i++ ){
		if( ABS(components[i] - src.components[i]) > ALMOST_ZERO ){
			rv = false;
		}
	}
  return( rv );
}

template <class T>
bool Vector3<T>::operator !=( const Vector3<T>& src ) const{
  return( ! (*this == src) );
}

template <class T>
bool Vector3<T>::operator <( const Vector3<T>& src ) const{
  bool rv = false;
  for (unsigned i = 0; i < dimension; i++){
    if (components[i] < src.components[i])
      rv = true;
    if (components[i] > src.components[i])
      rv = false;
	}
  return( rv );
}


// Arithmetic operators
template <class T>
const Vector3<T>& Vector3<T>::operator +=( const Vector3<T> &v ){
  for( unsigned int i = 0; i < dimension; i++ ){
    components[i] += v.components[i];
  }
  return( *this );
}

template <class T>
const Vector3<T>& Vector3<T>::operator +=( const T scalar ){
  for( unsigned int i = 0; i < dimension; i++ ){
    components[i] += scalar;
  }
  return( *this );
}


template <class T>
const Vector3<T>& Vector3<T>::operator -=( const Vector3<T> &v ){
  for( unsigned int i = 0; i < dimension; i++ ){
    components[i] -= v.components[i];
  }
  return( *this );
}

template <class T>
const Vector3<T>& Vector3<T>::operator -=( const T scalar ){
  for( unsigned int i = 0; i < dimension; i++ ){
    components[i] -= scalar;
  }
  return( *this );
}

template <class T>
const Vector3<T>& Vector3<T>::operator *=( const T scalar ){
  for( unsigned int i = 0; i < dimension; i++ ){
    components[i] *= scalar;
  }
  return( *this );
}

template <class T>
const Vector3<T>& Vector3<T>::operator /=( const T scalar ){
  for( unsigned int i = 0; i < dimension; i++ ){
    components[i] /= scalar;
  }
  return( *this );
}

// Access operator
template <class T>
const T Vector3<T>::operator []( const int i ) const {
  switch( i ){
    case 0:
      return( components[X] );
    break;
    case 1:
      return( components[Y] );
    break;
    case 2:
      return( components[Z] );
    break;
    default:
      throw( "Index out of range" );
    break;
  };
}

template <class T>
T& Vector3<T>::operator []( const int i ){
  switch( i ){
    case 0:
      return( components[X] );
    break;
    case 1:
      return( components[Y] );
    break;
    case 2:
      return( components[Z] );
    break;
    default:
      throw( "Index out of range" );
    break;
  };
}

template <class T>
T* Vector3<T>::c_array( ){
  return( components );
}

template <class T>
const T* Vector3<T>::constPtr( ) const {
  return( components );
}

template <class T>
Vector3<T>& Vector3<T>::set( const T& x, const T& y, const T& z ){
  components[X] = x;
  components[Y] = y;
  components[Z] = z;
  return(*this);
}

template <class T>
Vector3<T>& Vector3<T>::set( const T *data, size_t size ){
  for( unsigned int i = 0; i < size; i++ ){
    components[i] = data[i];
  }
  for( unsigned int i = size; i < dimension; i++ ){
    components[i] = static_cast<T>(0);
  }
  return(*this);
}

template <class T>
const T& Vector3<T>::x( ) const {
  return( components[X] );
}

template <class T>
const T& Vector3<T>::y( ) const {
  return( components[Y] );
}

template <class T>
const T& Vector3<T>::z( ) const {
  return( components[Z] );
}

template <class T>
void Vector3<T>::x( const T& a ){
  components[X] = a;
}

template <class T>
void Vector3<T>::y( const T& b ){
  components[Y] = b;
}

template <class T>
void Vector3<T>::z( const T& c ){
  components[Z] = c;
}


// Vector Math
template <class T>
void Vector3<T>::normalize( ){
  double magnitude = length( );
  if( !FP_EQUAL(magnitude, 0.0, FP_EPSILON) ){
    *this /= (T)magnitude;
  }
}

template <class T>
void Vector3<T>::setLength( T len ){
  double magnitude = length( );
  *this *= len/magnitude;
}

template <class T>
int Vector3<T>::sign( const Vector3<T>& v ) const{
  int rv = 1;
  if( dot(v) < 0){
    rv = -1;
  }
  return( rv );
}

template <class T>
double Vector3<T>::length( ) const {
  return( std::sqrt( (double)squaredLength( ) ) );
}

template <class T>
T Vector3<T>::squaredLength( ) const {
  T accumulate = (T)0;
  for( unsigned int i = 0; i < dimension; i++ ){
    accumulate += SQR( components[i] );
  }
  return( (T)accumulate );
}


template <class T>
double Vector3<T>::angle( const Vector3<T> &v ) const {
  double ct = cosTheta( v );
  double ang = std::acos( ct );
  assert( !isnan(ang) );
  return( ang );
}

template <class T>
double Vector3<T>::cosTheta( const Vector3<T> &v ) const{
  double cosTheta = dot(v);
  assert( !isnan(cosTheta) );
  if( cosTheta > 1.0 ){
    cosTheta = 1.0;
  }else if( cosTheta < -1.0 ){
    cosTheta = -1.0;
  }
  return( cosTheta );
}

template <class T>
double Vector3<T>::distanceFrom( const Vector3<T> &v ) const{
  Vector3<T> a = *this - v;
  return( a.length( ) );
}

template <class T>
double Vector3<T>::squaredDistanceFrom( const Vector3<T> &v ) const{
  Vector3<T> a = *this - v;
  return( a.squaredLength( ) );
}

template <class T>
double Vector3<T>::infiniteDistanceFrom( const Vector3<T> &v ) const{
  double soFar(0);
	for( unsigned int i = 0; i < dimension; i++ ){
    double diff = ABS(components[i] - v.components[i]);
		if( diff > soFar ){
      soFar = diff; 
		}
	}
  return( soFar );
}

template <class T>
double Vector3<T>::manhattanDistanceFrom( const Vector3<T>& v ) const{
  T sum(0);
	for( unsigned int i = 0; i < dimension; i++ ){
    sum += ABS(components[i] - v.components[i]);
  }
  return( sum );
}

template <class T>
double Vector3<T>::distanceToPlane( const Vector3<T>& point, const Vector3<T>& normal ) const{
  assert( fabs((double)(normal.squaredLength() - 1)) < ALMOST_ZERO );
  return( normal.dot((point - *this)) );
}

/*template <class T>
const bool Vector3<T>::isOrthogonalTo( const Vector3<T> &v ){
  // two vectors are orthogonal if A dot B == 0
  bool rv = true;
  if( dot(v) != (T)0 ){
    rv = false;
  }
  return( rv );
}*/

template <class T>
void Vector3<T>::rotateX( const double angle ){
	double y = components[1];
	double z = components[2];
	double cosine = cos(angle);
	double sine = sin(angle);

	components[1] = static_cast<T>(y*cosine - z*sine);
	components[2] = static_cast<T>(y*sine + z*cosine);
}


// Rotates a vector around the Y axis
template <class T>
void Vector3<T>::rotateY( const double angle ){
  double x = components[0];
  double z = components[2];
  double cosine = cos(angle);
  double sine = sin(angle);

  components[2] = static_cast<T>(z*cosine - x*sine);
  components[0] = static_cast<T>(z*sine + x*cosine);
}

// Rotates a vector around the Z axis
template <class T>
void Vector3<T>::rotateZ( const double angle ){
  double x = components[0];
  double y = components[1];
  double cosine = cos(angle);
  double sine = sin(angle);

  components[0] = static_cast<T>(x*cosine - y*sine);
  components[1] = static_cast<T>(x*sine + y*cosine);
}

template <class T>
T Vector3<T>::dot( const Vector3<T> &v ) const{
  T accumulate = (T)0;
  for( unsigned int i = 0; i < dimension; i++ ){
    accumulate += components[i] * v.components[i];
  }
  return( accumulate );
}

template <class T>
Vector3<T> Vector3<T>::cross( const Vector3<T> &v1, const Vector3<T> &v2 ) const
{
	Vector3<T> result;
	result.x(v1.y() * v2.z() - v1.z() * v2.y());
	result.y(v1.z() * v2.x() - v1.x() * v2.z());
	result.z(v1.x() * v2.y() - v1.y() * v2.x());

	return result;
}


// IO
template <class T>
void Vector3<T>::write( std::ostream &out) const {
  out.setf( std::ios::fixed );
  out << std::setprecision(IOS_FP_PRECISION)
      << "(" << components[X] << std::endl
      << " " << components[Y] << std::endl
      << " " << components[Z] << ")" << std::endl;
  out.unsetf( std::ios::fixed );
}

template <class T>
void Vector3<T>::write_row( std::ostream &out) const {
  out.setf( std::ios::fixed );
  out << std::setprecision(IOS_FP_PRECISION)
      << "(" << components[X] << ", "
             << components[Y] << ", "
             << components[Z] << ")" << std::endl;
  out.unsetf( std::ios::fixed );
}

template <class T>
Vector3<T> Vector3<T>::operator +( const Vector3<T> &v ) const{
  Vector3<T> c = Vector3<T>( components[X] + v.components[X],
                            components[Y] + v.components[Y],
                            components[Z] + v.components[Z] );
  return( c );
}

template <class T>
Vector3<T> Vector3<T>::operator -( const Vector3<T> &v ) const{
  Vector3<T> c = Vector3<T>( components[X] - v.components[X],
                            components[Y] - v.components[Y],
                            components[Z] - v.components[Z] );
  return( c );
}

template <class T>
Vector3<T> Vector3<T>::operator -( ) const{
  return( Vector3<T>( -components[X],
                      -components[Y],
                      -components[Z] ) );
}

template <class T>
Vector3<T> Vector3<T>::operator *( const T scalar) const{
  return( Vector3<T>( components[X] * scalar,
                      components[Y] * scalar,
                      components[Z] * scalar ) );
}

template <class T>
Vector3<T> Vector3<T>::operator /( const T scalar ) const{
  return( Vector3<T>( components[X] / scalar,
                      components[Y] / scalar,
                      components[Z] / scalar ) );
}

template class Vector3<char>;
template class Vector3<short>;
template class Vector3<int>;
template class Vector3<long>;
template class Vector3<float>;
template class Vector3<double>;

} // end namespace msgfx

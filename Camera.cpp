/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */
#include "Camera.h"
#include <cmath>
#define EPSILON 0.000001

// Calculates Orthogonal Bases
void Camera::CalculateOrthoNormalBases()
{
	msgfx::Vector3f arbitrary(0.0f, 1.f, 0.f),
		result;
	_w = -_direction;
	_w.normalize();
	
	// Check to see if arbitrary and direction vectors are parallel
	float dotProduct = arbitrary.dot(_w);
	if(fabs(dotProduct) < EPSILON)
	{
		// arbitrary vector and direction vector are parallel : use a different arbitrary vector
		arbitrary.set(1.f, 0.f, 0.f);
	}
	
	_u = cross(arbitrary, _w);
	_v = cross(_w, _u);	
}

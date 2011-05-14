/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */

#include "Sphere.h"
#include <cmath>
#include <cassert>
#define EPSILON 0.0000001

Sphere::Sphere(float cx, float cy, float cz, float r)
	: center(cx, cy, cz),
	radius(r)
{

}

Sphere::~Sphere()
{
	// Nothing to free
}

msgfx::Vector3f& Sphere::Center()
{
	return center;
}
float& Sphere::Radius()
{
	return radius;
}

void Sphere::write(std::ostream &out) const
{
	out << "Sphere:" << std::endl;
	out << "Center: [" << center.x() << ", " << center.y() << ", " << center.z() << "]" << std::endl;
	out << "Radius: " << radius;
}

bool Sphere::intersects(Ray &r, Hit &h)
{
	msgfx::Vector3f direction = r.Direction(),
		start = r.Start(),
		radialDistFromStart = start - center;

	float a = direction.dot(direction);
	float b = 2.f * direction.dot(radialDistFromStart);
	float c = radialDistFromStart.dot(radialDistFromStart) - radius * radius;

	float discriminant = b * b - 4.f * a * c;

	// If negative no collision occurs
	if(discriminant < 0.f)
		return false;
	
	float e = sqrt(discriminant);
	float denom = 2*a;
	float t = (-b - e) / denom;

	if(t > EPSILON)
	{
		h.Depth() = t;
		h.Position() = start + direction * t;
		h.Normal() = h.Position() - center;
		h.Normal().normalize();
		return true;
	}

	t = (-b + e) / denom;
	h.Depth() = t;
	h.Position() = start + direction * t;
	h.Normal() = h.Position() - center;
	h.Normal().normalize();
	

	return true;
}

/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */

#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "Object3D.h"
#include "Vector3.h"

class Sphere : public Object3D
{
public:
	Sphere(float cx, float cy, float cz, float r);
	~Sphere();
	msgfx::Vector3f& Center();
	float& Radius();
	virtual void write(std::ostream &out) const;
	virtual bool intersects(Ray &r, Hit &h);
protected:
	msgfx::Vector3f center;
	float radius;
};

#endif
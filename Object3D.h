/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_
#include <ostream>
#include "Ray.h"
#include "Hit.h"

class Object3D
{
public:
	virtual void write(std::ostream &out) const = 0;
	virtual bool intersects(Ray &r, Hit &h) = 0;
	const int& MaterialIndex() { return materialIndex; };
	void MaterialIndex(int mIndex) { materialIndex = mIndex; };
protected:
	int materialIndex;
};

std::ostream& operator <<( std::ostream &out, const Object3D *o);

#endif
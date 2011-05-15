/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */

#ifndef _GROUP_H_
#define _GROUP_H_
#include <vector>
#include "Object3D.h"
#include "Sphere.h"

class Group{
public:
	Group( );
	~Group( );
	void AddObject(Object3D* o);
	const std::vector<Object3D*>& Objects();
	void write(std::ostream &out) const;
private:
	std::vector<Object3D*> vecObjects;
};

std::ostream& operator <<( std::ostream &out, const Group *g);
#endif
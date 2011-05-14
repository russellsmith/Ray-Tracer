/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */

#include "Group.h"

Group::Group()
{
}

Group::~Group()
{
	// Free Object3D objects
	std::vector<Object3D*>::iterator vecIt;
	for(vecIt = vecObjects.begin(); vecIt != vecObjects.end(); ++vecIt)
	{
		delete *vecIt;
	}
}

void Group::AddObject(Object3D* o)
{
	vecObjects.push_back(o);
}

void Group::write(std::ostream &out) const
{
	std::vector<Object3D*>::const_iterator vecIt;
	for(vecIt = vecObjects.begin(); vecIt != vecObjects.end(); ++vecIt)
	{
		out << *vecIt << std::endl;
	}
}

std::ostream& operator <<( std::ostream &out, const Object3D *o)
{
	o->write(out);
	return out;
}

const std::vector<Object3D*>& Group::Objects()
{
	return vecObjects;
}
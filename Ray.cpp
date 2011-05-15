/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */
#include "Ray.h"

Ray::Ray() :
	start(0.f, 0.f, 0.f),
	end(0.f, 0.f, 0.f),
	depth(0)
{

}

Ray::Ray(msgfx::Vector3f startPoint, msgfx::Vector3f endPoint) :
	start(startPoint),
	end(endPoint),
	depth(0)
{

}
Ray::~Ray( )
{
	// Nothing to free
}
const msgfx::Vector3f& Ray::Start()
{
	return start;
}
const msgfx::Vector3f& Ray::End()
{
	return end;
}

msgfx::Vector3f Ray::Direction()
{
	msgfx::Vector3f dir(end - start);
	dir.normalize();
	return dir;
}

void Ray::Start(msgfx::Vector3f startPoint)
{
	start = startPoint;
}
void Ray::End(msgfx::Vector3f endPoint)
{
	end = endPoint;
}
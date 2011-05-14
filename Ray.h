/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */
#include "Vector3.h"
#ifndef _RAY_H_
#define _RAY_H_

class Ray{
public:
	Ray();
	Ray(msgfx::Vector3f startPoint, msgfx::Vector3f endPoint);
	~Ray( );
	const msgfx::Vector3f& Start();
	const msgfx::Vector3f& End();
	void Start(msgfx::Vector3f startPoint);
	void End(msgfx::Vector3f endPoint);
	msgfx::Vector3f Direction();
private:
	msgfx::Vector3f start, end;
};
#endif
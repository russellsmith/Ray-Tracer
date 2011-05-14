/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */
#include "Vector3.h"
#ifndef _HIT_H_
#define _HIT_H_

class Hit{
public:
	Hit( );
	~Hit( );
	float& Depth();
	msgfx::Vector3f& Position();
	msgfx::Vector3f& Normal();
private:
	float depth;
	msgfx::Vector3f position;
	msgfx::Vector3f normal;
};
#endif
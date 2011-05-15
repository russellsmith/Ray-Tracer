/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */

#ifndef _HIT_H_
#define _HIT_H_
#include "Vector3.h"
#include "Ray.h"
//#include "Scene.h"
class Scene;

class Hit{
public:
	Hit( );
	~Hit( );
	float& Depth();
	msgfx::Vector3f& Position();
	msgfx::Vector3f& Normal();
	float depth;
	msgfx::Vector3f position;
	msgfx::Vector3f normal;
	Ray ray;
	Scene* scenePtr;
	int materialIndex;
	int recursionDepth;
};
#endif
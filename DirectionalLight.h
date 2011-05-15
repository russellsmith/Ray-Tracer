/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * April 9, 2011
 */


#ifndef _DIRECTIONALLIGHT_H_
#define _DIRECTIONALLIGHT_H_
#include "Light.h"
#include "Vector3.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	~DirectionalLight();
	void Angle(float angle);
	const float& Angle();
	void Direction(const float& x, const float& y, const float& z);
	void Direction(const msgfx::Vector3f& dir);
	msgfx::Vector3f& Direction();
private:
	msgfx::Vector3f direction;
	float angle;
};
#endif
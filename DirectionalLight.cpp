/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * April 9, 2011
 */
#include "DirectionalLight.h"	
DirectionalLight::DirectionalLight()
{
	Light();
	lightType = Directional;
}
DirectionalLight::~DirectionalLight()
{
	// Default angle
	angle = 30.f;
}
void DirectionalLight::Angle(float angle)
{
	this->angle = angle;
}
const float& DirectionalLight::Angle()
{
	return angle;
}
void DirectionalLight::Direction(const float& x, const float& y, const float& z)
{
	direction.set(x, y, z);
	direction.normalize();
}
void DirectionalLight::Direction(const msgfx::Vector3f& dir)
{
	direction = dir;
	direction.normalize();
}
msgfx::Vector3f& DirectionalLight::Direction()
{
	return direction;
}
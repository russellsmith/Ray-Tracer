#include "Vector3.h"
#include "RGBColor.h"
#ifndef _LIGHT_H_
#define _LIGHT_H_
enum LightTypes
{
	Point = 1,
	Directional = 2
};
class Light
{
public:
	Light();
	~Light();
	const msgfx::Vector3f& Position();
	void Position(const msgfx::Vector3f& _position);
	void Position(const float& x, const float& y, const float& z);
	const RGBColor& Attenuation();
	const LightTypes& LightType();
	void LightType(LightTypes type);
	void Attenuation(const RGBColor& c);
	void Attenuation(const float& r, const float& g, const float& b);
	const RGBColor& Color();
	void Color(const RGBColor& c);
	void Color(const float& r, const float& g, const float& b);
protected:
	RGBColor attenuation;
	RGBColor color;
	msgfx::Vector3f position;
	LightTypes lightType;
};
#endif
#include "Light.h"
#include "RGBColor.h"

Light::Light() {
	color.r = 0.f;
	color.g = 0.f;
	color.b = 0.f;

	attenuation.r = 1.f;
	attenuation.g = 1.f;
	attenuation.b = 1.f;

	position.x(0.f);
	position.y(0.f);
	position.z(0.f);

	lightType = Point;
}

Light::~Light()
{

}

const msgfx::Vector3f& Light::Position()
{
	return position;
}

void Light::Position(const msgfx::Vector3f& _position)
{
	position = _position;
}

void Light::Position(const float& x, const float& y, const float& z)
{
	position.x(x);
	position.y(y);
	position.z(z);
}

const RGBColor& Light::Attenuation()
{
	return attenuation;
}

void Light::Attenuation(const RGBColor& c)
{
	attenuation = c;
}

void Light::Attenuation(const float& r, const float& g, const float& b)
{
	attenuation.r = r;
	attenuation.g = g;
	attenuation.b = b;
}

const RGBColor& Light::Color()
{
	return color;
}

void Light::Color(const RGBColor& c)
{
	color = c;
}

void Light::Color(const float& r, const float& g, const float& b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

const LightTypes& Light::LightType()
{
	return lightType;
}

void Light::LightType(LightTypes type)
{
	lightType = type;
}
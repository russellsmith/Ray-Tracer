#include "RGBColor.h"
#include <algorithm>

RGBColor::RGBColor() : r(0.f), g(0.f), b(0.f)
{
}
RGBColor::RGBColor(float c) : r(c), g(c), b(c)
{
}
RGBColor::RGBColor(float red, float green, float blue) : r(red), g(green), b(blue)
{
}
RGBColor::RGBColor(const RGBColor& c) : r(c.r), b(c.b), g(c.g)
{
	
}
RGBColor::~RGBColor()
{
	// Nothing to do
}

RGBColor RGBColor::operator+(const RGBColor& c) const
{
	RGBColor tmp(r + c.r, g + c.g, b + c.b);
	return tmp;
}
RGBColor RGBColor::operator-(const RGBColor& c) const
{
	RGBColor tmp(r - c.r, g - c.g, b - c.b);
	return tmp;
}

RGBColor RGBColor::operator*(const float& f) const
{
	RGBColor tmp(r * f, g * f, b * f);
	return tmp;
}
RGBColor RGBColor::operator*(const RGBColor& c) const{
	RGBColor tmp(r * c.r, g * c.g, b * c.b);
	return tmp;
}

void RGBColor::Clamp()
{
	MaxToOne();
	/*if(r > 1.f)
		r = 1.f;
	else if(r < 0.f)
		r = 0.f;
	if(g > 1.f)
		g = 1.f;
	else if(g < 0.f)
		g = 0.f;
	if(b > 1.f)
		b = 1.f;
	else if(b < 0.f)
		b = 0.f;*/
}

void RGBColor::MaxToOne(){
	float maxValue = std::max(r, std::max(g, b));

	if(maxValue > 1.0)
	{
		r /= maxValue;
		g /= maxValue;
		b /= maxValue;
	}
}
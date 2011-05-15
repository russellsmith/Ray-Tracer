#ifndef _RGBCOLOR_H_
#define _RGBCOLOR_H_

class RGBColor
{
public:
	float r, g, b;
public:
	RGBColor();
	RGBColor(float c);
	RGBColor(float red, float green, float blue);
	RGBColor(const RGBColor& c);
	~RGBColor();

	RGBColor operator+(const RGBColor& c) const;
	RGBColor operator-(const RGBColor& c) const;
	RGBColor operator*(const float& f) const;
	RGBColor operator*(const RGBColor& c) const;
	void Clamp();

private:
	void MaxToOne();
};

#endif
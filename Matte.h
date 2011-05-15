#ifndef _MATTE_H_
#define _MATTE_H_
#include "RGBColor.h"
#include "Lambertian.h"
#include "Material.h"

class Matte : public Material
{
public:
	Matte();
	~Matte();
	void SetKA(const float ka);
	void SetKD(const float kd);
	void SetCD(const RGBColor& c);
	virtual RGBColor shade(Hit& h);
protected:
	Lambertian* _ambientBRDF;
	Lambertian* _diffuseBRDF;
};
#endif
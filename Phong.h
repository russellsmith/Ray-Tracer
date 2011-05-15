#ifndef _PHONG_H_
#define _PHONG_H_
#include "Material.h"
class Lambertian;
class GlossySpecular;

class Phong : public Material
{
public:
	Phong();
	~Phong();
	void SetKA(const float ka);
	void SetKD(const float kd);
	void SetCD(const RGBColor& c);
	void SetKS(const float ks);
	void SetCS(const RGBColor& c);
	void SetExponent(const float exp);
	virtual RGBColor shade(Hit& h);

protected:
	Lambertian* _ambientBRDF;
	Lambertian* _diffuseBRDF;
	GlossySpecular* _specularBRDF;
};


#endif
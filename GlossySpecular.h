#ifndef _GLOSSYSPECULAR_H_
#define _GLOSSYSPECULAR_H_
#include "BRDF.h"

class GlossySpecular : public BRDF
{
public:
	GlossySpecular();
	~GlossySpecular();
	void SetKS(float ks);
	void SetCS(RGBColor cs);
	void SetExponent(float exp);
	float GetExponent();
	float GetKS();
	RGBColor GetCS();
	virtual RGBColor f(const Hit& h, const msgfx::Vector3f& wi, const msgfx::Vector3f& wo) const;
	virtual RGBColor sample_f(const Hit& h, msgfx::Vector3f& wi, const msgfx::Vector3f& wo, float& pdf) const;
	virtual RGBColor sample_f(const Hit& h, msgfx::Vector3f& wi, const msgfx::Vector3f& wo) const;
	virtual RGBColor rho(const Hit& h, const msgfx::Vector3f& wo) const;
protected:
	float _ks; // specular reflection coefficient
	RGBColor _cs; // reflective color
	float _exp;

};

#endif
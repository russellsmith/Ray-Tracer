#ifndef _PERFECTSPECULAR_H_
#define _PERFECTSPECULAR_H_
#include "BRDF.h"

class PerfectSpecular : public BRDF{
public:
	PerfectSpecular();
	~PerfectSpecular();
	void SetKR(float kr);
	void SetCR(RGBColor cr);
	float GetKR();
	RGBColor GetCR();
	virtual RGBColor f(const Hit& h, const msgfx::Vector3f& wi, const msgfx::Vector3f& wo) const;
	virtual RGBColor sample_f(const Hit& h, msgfx::Vector3f& wi, const msgfx::Vector3f& wo, float& pdf) const;
	virtual RGBColor rho(const Hit& h, const msgfx::Vector3f& wo) const;
protected:
	float _kr; // specular reflection coefficient
	RGBColor _cr; // reflective color

};

#endif
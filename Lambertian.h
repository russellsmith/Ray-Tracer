#ifndef _LAMBERTIAN_H_
#define _LAMBERTIAN_H_
#include "BRDF.h"
#include "RGBColor.h"

class Lambertian: public BRDF{
public:
	Lambertian();
	~Lambertian();
	void SetKD(float kd);
	void SetCD(RGBColor cd);
	float GetKD();
	RGBColor GetCD();
	virtual RGBColor f(const Hit& h, const msgfx::Vector3f& wi, const msgfx::Vector3f& wo) const;
	virtual RGBColor sample_f(const Hit& h, msgfx::Vector3f& wi, const msgfx::Vector3f& wo, float& pdf) const;
	virtual RGBColor sample_f(const Hit& h, msgfx::Vector3f& wi, const msgfx::Vector3f& wo) const;
	virtual RGBColor rho(const Hit& h, const msgfx::Vector3f& wo) const;
protected:
	float _kd; // diffuse reflection coefficient
	RGBColor _cd; // diffuse color

};

#endif
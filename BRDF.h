#ifndef _BRDF_H_
#define _BRDF_H_
#include "Vector3.h"
#include "RGBColor.h"
#include "Hit.h"
#include "Sampler.h"
class BRDF
{
public:
	BRDF();
	~BRDF();
	virtual RGBColor f(const Hit& h, const msgfx::Vector3f& wi, const msgfx::Vector3f& wo) const = 0;
	virtual RGBColor sample_f(const Hit& h, msgfx::Vector3f& wi, const msgfx::Vector3f& wo) const = 0;
	virtual RGBColor sample_f(const Hit& h, msgfx::Vector3f& wi, const msgfx::Vector3f& wo, float& pdf) const = 0;
	virtual RGBColor rho(const Hit& h, const msgfx::Vector3f& wo) const = 0;

protected:
	Sampler* _sampler;
};
#endif
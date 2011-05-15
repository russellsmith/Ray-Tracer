#include "Lambertian.h"
#include "Constants.h"
#include "Point3D.h"

Lambertian::Lambertian(){
	_sampler = NULL;
}
Lambertian::~Lambertian(){
	if(_sampler != NULL)
	{
		delete _sampler;
		_sampler = NULL;
	}
}
void Lambertian::SetKD(float kd){
	_kd = kd;
}
void Lambertian::SetCD(RGBColor cd){
	_cd = cd;
}
float Lambertian::GetKD(){
	return _kd;
}
RGBColor Lambertian::GetCD(){
	return _cd;
}
RGBColor Lambertian::f(const Hit& h, const msgfx::Vector3f& wi, const msgfx::Vector3f& wo) const {
	return (_cd * _kd * invPI);
}
RGBColor Lambertian::sample_f(const Hit& h, msgfx::Vector3f& wi, const msgfx::Vector3f& wo, float& pdf) const {
	// Construct orthonormal basis with respect to hit location
	msgfx::Vector3f w = h.normal;
	msgfx::Vector3f v = cross(msgfx::Vector3f(0.001, 1.0, -0.0021), w);
	v.normalize();
	msgfx::Vector3f u = cross(v, w);

	Point3D sampledPoint = _sampler->sample_hemisphere();
	wi = u * sampledPoint.x + v * sampledPoint.y + w * sampledPoint.z;
	wi.normalize();

	// calculate probability density function
	pdf = h.normal.dot(wi) * invPI; 

	return (_cd * _kd * invPI);
}
RGBColor Lambertian::sample_f(const Hit& h, msgfx::Vector3f& wi, const msgfx::Vector3f& wo) const{
	return black;
}

RGBColor Lambertian::rho(const Hit& h, const msgfx::Vector3f& wo) const {
	return (_cd * _kd);
}
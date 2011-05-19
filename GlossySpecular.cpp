#include "GlossySpecular.h"
#include "Vector3.h"
#include "MultiJittered.h"

GlossySpecular::GlossySpecular() : _exp(100){
	_sampler = new MultiJittered(40);
}
GlossySpecular::~GlossySpecular(){
	if(_sampler != NULL)
	{
		delete _sampler;
		_sampler = NULL;
	}
}
void GlossySpecular::SetKS(float ks){
	_ks = ks;
}
void GlossySpecular::SetCS(RGBColor cs){
	_cs = cs;
}
void GlossySpecular::SetExponent(float exp){
	_exp = exp;
}
float GlossySpecular::GetExponent(){
	return _exp;
}
float GlossySpecular::GetKS(){
	return _ks;
}
RGBColor GlossySpecular::GetCS(){
	return _cs;
}
RGBColor GlossySpecular::f(const Hit& h, const msgfx::Vector3f& wi, const msgfx::Vector3f& wo) const{
	RGBColor L = black;
	float ndotwi = h.normal.dot(wi);

	// Calculate reflection vector
	msgfx::Vector3f r(-wi + h.normal * 2.0 * ndotwi);
	float rdotwo = r.dot(wo);

	if(rdotwo > 0.0)
		L = _cs * _ks * pow(rdotwo, _exp);
	return L;
}
RGBColor GlossySpecular::sample_f(const Hit& h, msgfx::Vector3f& wi, const msgfx::Vector3f& wo, float& pdf) const{
	float ndotwo = h.normal.dot(wo);

	// Direction of mirror reflection
	msgfx::Vector3f r(-wo + h.normal * 2.0 * ndotwo);

	// Calculate orthonormal basis
	msgfx::Vector3f w = r;
	msgfx::Vector3f v = cross(msgfx::Vector3f(0.001, 1.0, -0.0021), w);
	v.normalize();
	msgfx::Vector3f u = cross(v, w);

	Point3D sp = _sampler->sample_hemisphere();

	// Calculate reflected ray direction
	wi = u * sp.x + v * sp.y + w * sp.z;

	if(h.normal.dot(wi) < 0.0)
		// Reflected ray is below surface
		wi = - u * sp.x - v * sp.y + w * sp.z;
	wi.normalize();
	float phong_lobe = pow(r.dot(wi), _exp);
	pdf = phong_lobe * (h.normal.dot(wi));

	return (_cs * _ks * phong_lobe);
}
RGBColor GlossySpecular::sample_f(const Hit& h, msgfx::Vector3f& wi, const msgfx::Vector3f& wo) const{
	return black;
}

RGBColor GlossySpecular::rho(const Hit& h, const msgfx::Vector3f& wo) const{
	return black;
}
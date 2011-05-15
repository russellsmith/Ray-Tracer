#include "PerfectSpecular.h"
#include "Constants.h"

PerfectSpecular::PerfectSpecular(){

}
PerfectSpecular::~PerfectSpecular(){

}
void PerfectSpecular::SetKR(float kr){
	_kr = kr;
}
void PerfectSpecular::SetCR(RGBColor cr){
	_cr = cr;
}
float PerfectSpecular::GetKR(){
	return _kr;
}
RGBColor PerfectSpecular::GetCR(){
	return _cr;
}
RGBColor PerfectSpecular::f(const Hit& h, const msgfx::Vector3f& wi, const msgfx::Vector3f& wo) const{
	return black;
}
RGBColor PerfectSpecular::sample_f(const Hit& h, msgfx::Vector3f& wi, const msgfx::Vector3f& wo, float& pdf) const{
	float ndotwo = h.normal.dot(wo);
	wi = -wo + h.normal * 2.0f * ndotwo;


	return (_cr * (_kr / h.normal.dot(wi)));
}
RGBColor PerfectSpecular::rho(const Hit& h, const msgfx::Vector3f& wo) const{
	return black;
}
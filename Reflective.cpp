#include "Reflective.h"
#include "PerfectSpecular.h"
#include "Scene.h"

Reflective::Reflective() : Phong(),
	_reflectiveBRDF(new PerfectSpecular)
{

}
Reflective::~Reflective(){
	delete _reflectiveBRDF;
}
void Reflective::SetKR(const float kr){
	_reflectiveBRDF->SetKR(kr);
}
void Reflective::SetCR(const RGBColor& c){
	_reflectiveBRDF->SetCR(c);
}

RGBColor Reflective::shade(Hit& h){
	
	RGBColor L = Phong::shade(h); // Direct illumination
	Hit h1;
	h1.scenePtr = h.scenePtr;
	h1.recursionDepth = h.recursionDepth;

	msgfx::Vector3f wo = - h.ray.Direction();
	wo.normalize();
	msgfx::Vector3f wi;

	RGBColor fr = _reflectiveBRDF->sample_f(h, wi, wo);
	Ray reflectedRay(h.Position(), h.Position() + wi);

	L = L + fr * h.scenePtr->traceRay(reflectedRay, h.recursionDepth + 1, h1) * h.normal.dot(wi);

	return L;
}
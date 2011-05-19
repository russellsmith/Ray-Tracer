#include "Matte.h"
#include "Vector3.h"
#include "Scene.h"

Matte::Matte() : Material(),
_ambientBRDF(new Lambertian),
_diffuseBRDF(new Lambertian)
{}
Matte::~Matte(){
	delete _ambientBRDF;
	delete _diffuseBRDF;
}
void Matte::SetKA(const float ka){
	_ambientBRDF->SetKD(ka);
}
void Matte::SetKD(const float kd){
	_diffuseBRDF->SetKD(kd);
}
void Matte::SetCD(const RGBColor& c){
	_diffuseBRDF->SetCD(c);
	_ambientBRDF->SetCD(c);
}
RGBColor Matte::shade(Hit& h){
	msgfx::Vector3f wo = -h.ray.Direction();
	RGBColor L = _ambientBRDF->rho(h, wo) * h.scenePtr->ambientLight;
	int numLights = h.scenePtr->myNumberOfLights;
	msgfx::Vector3f wi;

	for(int i = 0; i < numLights; ++i)
	{
		wi = h.scenePtr->myLights[i]->Position() - h.Position();
		float d = wi.length();
		wi.normalize();
		float ndotwi = h.normal.dot(wi);

		if(ndotwi > 0.0){
			// Calculate attenuation factor
			if(h.scenePtr->isPointVisibleToLight(h.Position(), h.scenePtr->myLights[i]))
			{
				float attenuation = 1 / (d*d*h.scenePtr->myLights[i]->Attenuation().r + d*h.scenePtr->myLights[i]->Attenuation().g + h.scenePtr->myLights[i]->Attenuation().b);
				L = L + _diffuseBRDF->f(h, wo, wi) * h.scenePtr->myLights[i]->Color() * ndotwi * attenuation;
			}
		}
			
	}
	
	return L;
}
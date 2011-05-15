#include "Phong.h"
#include "Lambertian.h"
#include "GlossySpecular.h"
#include "Scene.h"

Phong::Phong() : Material(),
	_ambientBRDF(new Lambertian),
	_diffuseBRDF(new Lambertian),
	_specularBRDF(new GlossySpecular)
{
	SetCS(white);
	SetKS(0.01f);
}
Phong::~Phong(){

}
void Phong::SetKA(const float ka){
	_ambientBRDF->SetKD(ka);
}
void Phong::SetKD(const float kd){
	_diffuseBRDF->SetKD(kd);
}
void Phong::SetCD(const RGBColor& c){
	_ambientBRDF->SetCD(c);
	_diffuseBRDF->SetCD(c);
}
void Phong::SetKS(const float ks){
	_specularBRDF->SetKS(ks);
}
void Phong::SetCS(const RGBColor& c){
	_specularBRDF->SetCS(c);
}

void Phong::SetExponent(const float exp){
	_specularBRDF->SetExponent(exp);
}

RGBColor Phong::shade(Hit& h){
	msgfx::Vector3f wo = - h.ray.Direction();
	RGBColor L = _ambientBRDF->rho(h, wo) * h.scenePtr->ambientLight;

	int numLights = h.scenePtr->myNumberOfLights;
	msgfx::Vector3f wi;

	for(int i = 0; i < numLights; ++i)
	{
		wi = h.scenePtr->myLights[i]->Position() - h.Position();
		float ndotwi = h.normal.dot(wi);

		if(ndotwi > 0.0)
		{
			// Calculate attenuation factor
			float d = wi.length();
			float attenuation = 1 / (d*d*h.scenePtr->myLights[i]->Attenuation().r + d*h.scenePtr->myLights[i]->Attenuation().g + h.scenePtr->myLights[i]->Attenuation().b);
			L = L + (_diffuseBRDF->f(h, wi, wo) + _specularBRDF->f(h, wi, wo)) * h.scenePtr->myLights[i]->Color() * ndotwi * attenuation;
		}
	}
	L = L * (1.f / numLights);
	return L;
}
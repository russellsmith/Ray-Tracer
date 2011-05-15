#ifndef _REFLECTIVE_H_
#define _REFLECTIVE_H_
#include "Phong.h"
class PerfectSpecular;

class Reflective : public Phong 
{
public:
	Reflective();
	~Reflective();
	void SetKR(const float kr);
	void SetCR(const RGBColor& c);

	virtual RGBColor shade(Hit& h);
private:
	PerfectSpecular* _reflectiveBRDF;
};

#endif
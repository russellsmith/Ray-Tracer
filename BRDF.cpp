#include "BRDF.h"

BRDF::BRDF(){
	_sampler = NULL;
}
BRDF::~BRDF(){
	if(_sampler == NULL)
	{
		delete _sampler;
		_sampler = NULL;
	}
}
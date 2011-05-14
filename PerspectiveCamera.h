/*
 * PerspectiveCamera.h
 *
 *  Created on: Mar 9, 2011
 *      Author: russell
 */

#ifndef PERSPECTIVECAMERA_H_
#define PERSPECTIVECAMERA_H_
#include "Camera.h"
class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera();
	~PerspectiveCamera();
	virtual void write(std::ostream &out) const;
	virtual void ComputeRay(const int& column, const int& row, Ray& r);
	const float& Distance();
	void Distance(const float& distance);
private:
	float _d;
};


#endif /* PERSPECTIVECAMERA_H_ */

#include "Vector3.h"
#include "Camera.h"
#include "Math.h"
#ifndef _ORTHOCAM_H_
#define _ORTHOCAM_H_
#define MAX_DEPTH 25.0
class Ray;
class OrthographicCamera : public Camera
{
public:
	OrthographicCamera();
	~OrthographicCamera();
	virtual void ComputeRay(const int& column, const int& row, Ray& r);
	void Width(const float& w) { _width = w; printf("%f", _width);};
	void Height(const float& h) { _height = h; printf("%f", _height);};
	const float Width() {return _width; };
	const float Height() {return _height; };
	virtual void write(std::ostream &out) const;
private:
	float _width, _height;
};
#endif

/*
 * PerspectiveCamera.cpp
 *
 *  Created on: Mar 9, 2011
 *      Author: russell
 */
#include "PerspectiveCamera.h"
#include "Vector3.h"
#include "ViewPlane.h"
#include "Ray.h"
#include "Point2D.h"

PerspectiveCamera::PerspectiveCamera() : _d(1.f) {

}
PerspectiveCamera::~PerspectiveCamera() {

}
void PerspectiveCamera::write(std::ostream &out) const {
	out << "Camera Position: [" << _position.x() << ", " << _position.y() << ", " << _position.z() << "]" << std::endl;
	out << "Camera Up Vec: [" << _up.x() << ", " << _up.y() << ", " << _up.z() << "]" << std::endl;
	out << "Camera Dir Vec: [" << _direction.x() << ", " << _direction.y() << ", " << _direction.z() << "]" << std::endl;
	out << "Camera distance: " << _d << std::endl;
}
void PerspectiveCamera::ComputeRay(const int& column, const int& row, Ray& r) {
	static msgfx::Vector3f topLeftPosition = _position + _up * _viewPlane.VerticalResolution() * 0.5f - Right() * _viewPlane.HorizontalResolution() * 0.5f
		- _up * _viewPlane.PixelSize() * 0.5f + Right() * _viewPlane.PixelSize() * 0.5f;
	Point2D sp = _sampler->sample_unit_square();
	r.Start(topLeftPosition - _up * (row + sp.x) * _viewPlane.PixelSize() + Right() * _viewPlane.PixelSize() * (column + sp.y));
	r.Start(_direction * _d + r.Start());
	r.End( (r.Start() + (r.Start() - _position)));
}

const float& PerspectiveCamera::Distance() {
	return _d;
}
void PerspectiveCamera::Distance(const float& distance) {
	_d = distance;
}

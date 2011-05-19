/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */

#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Vector3.h"
#include "Math.h"
#include "ViewPlane.h"
#include "MultiJittered.h"
class Ray;
class Camera{
public:
	Camera( ) {
		_position.set(0.f, 0.f, 0.f);
		_up.set(0.f, 0.f, 0.f);
		_direction.set(0.f, 0.f, 0.f);
		_sampler = new MultiJittered(_viewPlane.num_samples);
	}
	~Camera( ) {
		delete _sampler;
	}
	void Position(const float& x, const float& y, const float& z) {
		_position.set(x, y, z);
	}
	void Up(const float& x, const float& y, const float& z) {
		_up.set(x, y, z);
		_up.normalize();
	}
	void Direction(const float& x, const float& y, const float& z) {
		_direction.set(x, y, z);
		_direction.normalize();
	}
	const msgfx::Vector3f& Position(){ return _position; }
	const msgfx::Vector3f& Up() { return _up; }
	const msgfx::Vector3f& Direction() { return _direction; }
	msgfx::Vector3f Right() 
	{
		_up.normalize();
		_direction.normalize();
	
		return cross(_direction, _up);
	}
	const ViewPlane& viewPlane() { return _viewPlane; }
	void viewPlane(const ViewPlane& viewPlane) { _viewPlane = viewPlane; }
	void CalculateOrthoNormalBases();
	virtual void write(std::ostream &out) const = 0; /*{
		out << "Camera Position: [" << _position.x() << ", " << _position.y() << ", " << _position.z() << "]" << std::endl;
		out << "Camera Up Vec: [" << _up.x() << ", " << _up.y() << ", " << _up.z() << "]" << std::endl;
		out << "Camera Dir Vec: [" << _direction.x() << ", " << _direction.y() << ", " << _direction.z() << "]" << std::endl;
		out << "Camera Dimension: " << _width << "x" << _height;
	}*/
	virtual void ComputeRay(const int& column, const int& row, Ray& r) = 0;

protected:
	msgfx::Vector3f _position;
	msgfx::Vector3f _up, _direction;
	msgfx::Vector3f _u, _v, _w;
	ViewPlane _viewPlane;
	MultiJittered* _sampler;
};

std::ostream& operator <<( std::ostream &out, const Camera &h);
#endif

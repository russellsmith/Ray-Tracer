#include "OrthoCamera.h"
#include "Ray.h"

OrthographicCamera::OrthographicCamera()
{
}

OrthographicCamera::~OrthographicCamera()
{
	// Nothing to free
}

void OrthographicCamera::ComputeRay(const int& column, const int& row, Ray& r)
{
	/*int pixelSize =  _viewPlane.PixelSize(),
		hres = _viewPlane.HorizontalResolution(),
		vres = _viewPlane.VerticalResolution();*/
	static msgfx::Vector3f topLeftPosition = _position + _up * _viewPlane.VerticalResolution() * 0.5f - Right() * _viewPlane.HorizontalResolution() * 0.5f
		- _up * _viewPlane.PixelSize() * 0.5f + Right() * _viewPlane.PixelSize() * 0.5f;
	//std::cout << _viewPlane.HorizontalResolution() << "x" << _viewPlane.VerticalResolution();
 	r.Start(topLeftPosition - _up * row * _viewPlane.PixelSize() + Right() * _viewPlane.PixelSize() * column);
	r.End(r.Start() + _direction * 25.f);
}

void OrthographicCamera::write(std::ostream &out) const {

	out << "Camera Position: [" << _position.x() << ", " << _position.y() << ", " << _position.z() << "]" << std::endl;
	out << "Camera Up Vec: [" << _up.x() << ", " << _up.y() << ", " << _up.z() << "]" << std::endl;
	out << "Camera Dir Vec: [" << _direction.x() << ", " << _direction.y() << ", " << _direction.z() << "]" << std::endl;
	out << "Camera Basis Vectors: w: " << _w << " u: " << _u << " v: " << _v << std::endl;
}

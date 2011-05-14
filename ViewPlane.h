#ifndef _VIEWPLANE_H_
#define _VIEWPLANE_H_

class ViewPlane {
public:
	ViewPlane() : _hres(0), _vres(0), _pixelSize(1.f) {  }
	ViewPlane(float hres, float vres) : _hres(hres), _vres(vres), _pixelSize(1.f) { }
	~ViewPlane() {}
	const float& PixelSize() { return _pixelSize; }
	const float& HorizontalResolution() { return _hres; }
	const float& VerticalResolution() { return _vres; }
	void PixelSize(const float& pixelSize) { _pixelSize = pixelSize; }
	void HorizontalResolution(const float& hres) { _hres = hres; }
	void VerticalResolution(const float& vres) { _vres = vres; }
private:
	float _hres, _vres;
	float _pixelSize;
};
#endif

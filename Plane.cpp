#include "Plane.h"
#define EPSILON 0.000001

Plane::Plane(const msgfx::Vector3f& normal, const float& offset)
{
    this->normal = normal;
    this->normal.normalize();
    this->offset = offset;

    // Get an arbitrary point on the plane
    this->point = this->normal * offset;
}

Plane::~Plane(){
    // Nothing to free
}

const float& Plane::Offset(){
    return offset;
}

void Plane::Offset(const float& offset){
    this->offset = offset;
}

const msgfx::Vector3f& Plane::Normal(){
    return normal;
}

void Plane::Normal(const msgfx::Vector3f& normal){
    this->normal = normal;
}

void Plane::write(std::ostream &out) const{
    out << "Plane:" << std::endl;
    out << "Normal: ";
    normal.write_row(out);
    out << "Offset: " << offset << std::endl;
}
bool Plane::intersects(Ray &r, Hit &h){
	msgfx::Vector3f v1 = point - r.Start(),
			v2 = r.Direction();
	//v1.normalize();
	//v2.normalize();
	float t = (normal.dot(v1)) / normal.dot(v2);

	if(t > EPSILON) {
		h.Depth() = t;
		h.Normal() = normal;
		h.Position() = r.Start() + v2 * t;
		return true;
	} else {
		return false;
	}

}

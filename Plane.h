#ifndef _PLANE_H_
#define _PLANE_H_
#include "Object3D.h"
#include "Vector3.h"

class Plane : public Object3D
{
public:
    Plane(const msgfx::Vector3f& normal, const float& offset);
    ~Plane();
    const float& Offset();
    void Offset(const float& offset);
    const msgfx::Vector3f& Normal();
    void Normal(const msgfx::Vector3f& normal);
    virtual void write(std::ostream &out) const;
    virtual bool intersects(Ray &r, Hit &h);

private:
    float offset;
    msgfx::Vector3f normal, point;
};

#endif

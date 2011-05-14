#include "Vector3.h"
#include "Object3D.h"
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

class Ray;
class Hit;

class Triangle : public Object3D
{
public:
    Triangle(msgfx::Vector3f& vert1, msgfx::Vector3f& vert2, msgfx::Vector3f& vert3);
    ~Triangle();
    const msgfx::Vector3f& Vertex1();
    void Vertex1(const msgfx::Vector3f& v1);
    const msgfx::Vector3f& Vertex2();
    void Vertex2(const msgfx::Vector3f& v2);
    const msgfx::Vector3f& Vertex3();
    void Vertex3(const msgfx::Vector3f& v3);
    const msgfx::Vector3f& Normal();

    virtual void write(std::ostream &out) const;
    virtual bool intersects(Ray &ray, Hit &hit);

private:
    void ComputeNormal();
    msgfx::Vector3f v1, v2, v3, normal;
};

#endif

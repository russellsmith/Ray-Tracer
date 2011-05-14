#include "Triangle.h"
#include "Vector3.h"
#include "Ray.h"
#include "Hit.h"
#include <cassert>
#define EPSILON 0.000001

Triangle::Triangle(msgfx::Vector3f& vert1, msgfx::Vector3f& vert2, msgfx::Vector3f& vert3) : v1(vert1), v2(vert2), v3(vert3){
    ComputeNormal();
}

Triangle::~Triangle(){
    // Nothing to free
}

const msgfx::Vector3f& Triangle::Vertex1(){
    return v1;
}

void Triangle::Vertex1(const msgfx::Vector3f &v1) {
    this->v1 = v1;
}

const msgfx::Vector3f& Triangle::Vertex2(){
    return v2;
}

void Triangle::Vertex2(const msgfx::Vector3f &v2) {
    this->v2 = v2;
}

const msgfx::Vector3f& Triangle::Vertex3(){
    return v3;
}

void Triangle::Vertex3(const msgfx::Vector3f& v3) {
    this->v3 = v3;
}

const msgfx::Vector3f& Triangle::Normal(){
    return normal;
}

void Triangle::ComputeNormal(){
    msgfx::Vector3f a = v2 - v1,
    b = v3 - v1;
    normal = cross(a, b);
    normal.normalize();
}

void Triangle::write(std::ostream &out) const {
    out << "Triangle:" << std::endl;
    out << "Vertex 1: ";
    v1.write_row(out);
    out << "Vertex 2: ";
    v2.write_row(out);
    out << "Vertex 3: ";
    v3.write_row(out);
}
bool Triangle::intersects(Ray &ray, Hit &hit) {
    float a = v1.x() - v2.x(), b = v1.x() - v3.x(), c = ray.Direction().x(), d = v1.x() - ray.Start().x(),
        e = v1.y() - v2.y(), f = v1.y() - v3.y(), g = ray.Direction().y(), h = v1.y() - ray.Start().y(),
        i = v1.z() - v2.z(), j = v1.z() - v3.z(), k = ray.Direction().z(), l = v1.z() - ray.Start().z();

    float m = f * k - g * j,
          n = h * k - g * l,
          p = f * l - h * j,
          q = g * i - e * k,
          s = e * j - f * i;

    float inv_denom = 1.0 / (a * m + b * q + c * s);

    float e1 = d * m - b * n - c * p;
    float beta = e1 * inv_denom;

    if(beta < 0.0)
        return false;

    float r = e * l - h * i;
    float e2 = a * n + d * q + c * r;
    float gamma = e2 * inv_denom;

    if(gamma < 0.0)
        return false;

    if(beta + gamma > 1.f)
        return false;

    double e3 = a * p - b * r + d * s;
    float t = e3 * inv_denom;

    if(t < EPSILON)
        return false;

    hit.Depth() = t;
    hit.Normal() = normal;
    hit.Position() = ray.Start() + ray.Direction() * t;
    return true;

}

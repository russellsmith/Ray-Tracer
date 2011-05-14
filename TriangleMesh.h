#include <vector>
#include "Object3D.h"
#include "FaceList.h"
#include "Triangle.h"

#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

class TriangleMesh : public Object3D
{
public:
    TriangleMesh(FaceList *fl);
	~TriangleMesh();
	virtual void write(std::ostream &out) const;
	virtual bool intersects(Ray &r, Hit &h);
private:
	std::vector<Triangle> triangles;
};

#endif // TRIANGLEMESH_H

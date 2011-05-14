#include "TriangleMesh.h"
#include "Vector3.h"
#include "Ray.h"
#include "Hit.h"

TriangleMesh::TriangleMesh(FaceList* fl)
{
	msgfx::Vector3f v1, v2, v3;
	for(unsigned int i = 0; i < fl->faceCount(); ++i)
	{
		v1.set(fl->vertices[fl->faces[i][0]][0], fl->vertices[fl->faces[i][0]][1], fl->vertices[fl->faces[i][0]][2]);
		v2.set(fl->vertices[fl->faces[i][1]][0], fl->vertices[fl->faces[i][1]][1], fl->vertices[fl->faces[i][1]][2]);
		v3.set(fl->vertices[fl->faces[i][2]][0], fl->vertices[fl->faces[i][2]][1], fl->vertices[fl->faces[i][2]][2]);
		triangles.push_back(Triangle(v1, v2, v3));
	}
}

TriangleMesh::~TriangleMesh()
{

}
void TriangleMesh::write(std::ostream &out) const{

}
bool TriangleMesh::intersects(Ray &r, Hit &h)
{
	Hit min = h, h1 = h;
	for(std::vector<Triangle>::iterator vIt = triangles.begin(); vIt != triangles.end(); vIt++)
	{
		if(vIt->intersects(r, h1))
		{
			if(h1.Depth() < min.Depth())
			{
				min = h1;
			}
		}
	}
	if(min.Depth() != h.Depth())
	{
		// A collision occurred at some point..
		h = min;
		return true;
	}
	return false;
}
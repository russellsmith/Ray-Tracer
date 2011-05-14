/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */
#include <ostream>
#ifndef _PHONG_MATERIAL_H_
#define _PHONG_MATERIAL_H_

class Material{
public:
	Material( );
	~Material( );
	void write(std::ostream &out) const;

	float diffuseColor[3];
	float specularColor[3];
	float exponent;
	float transparentColor[3];
	float reflectiveColor[3];
	float indexOfRefraction;
};

std::ostream& operator <<( std::ostream &out, const Material *m);
#endif
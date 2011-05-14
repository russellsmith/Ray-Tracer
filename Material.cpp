/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */
#include "Material.h"

Material::Material() : exponent(1.0f),
	indexOfRefraction(0.0f)
{
	diffuseColor[0] = 0.0f;
	diffuseColor[1] = 0.0f;
	diffuseColor[2] = 0.0f;

	specularColor[0] = 0.0f;
	specularColor[1] = 0.0f;
	specularColor[2] = 0.0f;

	transparentColor[0] = 0.0f;
	transparentColor[1] = 0.0f;
	transparentColor[2] = 0.0f;

	reflectiveColor[0] = 0.0f;
	reflectiveColor[1] = 0.0f;
	reflectiveColor[2] = 0.0f;
}

Material::~Material()
{
	// Nothing to free
}

void Material::write(std::ostream &out) const
{
	out << "Diffuse: [" << diffuseColor[0] << ", " << diffuseColor[1] << ", " << diffuseColor[2] << "]" << std::endl;
	out << "Specular: [" << specularColor[0] << ", " << specularColor[1] << ", " << specularColor[2] << "]" << std::endl;
	out << "Transparent: [" << transparentColor[0] << ", " << transparentColor[1] << ", " << transparentColor[2] << "]" << std::endl;
	out << "Reflective: [" << reflectiveColor[0] << ", " << reflectiveColor[1] << ", " << reflectiveColor[2] << "]" << std::endl;
	out << "Exponent: " << exponent << std::endl;
	out << "Index of Refraction: " << indexOfRefraction;
}
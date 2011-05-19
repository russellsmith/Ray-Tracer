/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */


#ifndef _SCENE_H_
#define _SCENE_H_
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <Magick++.h>

#include "Camera.h"
#include "Material.h"
#include "Group.h"
#include "Hit.h"
#include "Light.h"
#include "RGBColor.h"

#define RECURSION_DEPTH 10
#define EPSILON .0000001
class Triangle;
class Sphere;
class Plane;
class ViewPlane;
class TriangleMesh;
class Reflective;
class Phong;
class Matte;
using namespace std;

class Scene{
	public:
		Scene( string inputFilename = "", string outputFilename = "", string depthFilename = "" );
		~Scene( );

		// Accessors
		Camera& camera( );
		Magick::Color& backgroundColor( );
		int numberOfMaterials( );
		void setCurrentMaterial( int i );
		Material* currentMaterial( );
		Group* group( );
		string& inputSceneFile( );
		string& outputFile( );
		string& depthFile( );
		
		void setInputSceneFile( string file );
		void setOutputFile( string file );
		void setDepthFile( string file );

		bool hasInputSceneFilePath( );
		bool hasOutputFilePath( );
		bool hasDepthFilePath( );

		bool parse( );

		void rayTrace(int dimension);
		bool isPointVisibleToLight(msgfx::Vector3f position, Light* light);
		RGBColor traceRay(Ray r, int depth, Hit& h);

		// I/O
		void write( std::ostream &out ) const;
		RGBColor ambientLight;
		Light **myLights;
		int myNumberOfLights;

	private:
		string myInputSceneFile;
		string myOutputFile;
		string myDepthFile;
		Camera *myCamera;
		Magick::ColorRGB myBackgroundColor;
		int myNumberOfMaterials;
		
		Material **materials;
		Material *myCurrentMaterial;
		Group *myGroup;
		
		ViewPlane myViewplane;
		ifstream inputFileStream;
		
		
		// For parsing
		char currentLine[255];
		char currentToken[255];
		int lineNumber;
		int tokenCount;
		int length;
		int i;
		int j;
		void nextToken( );
		void parseCamera( );
		void parseViewPlane( );
		void nextOnLine( );
		bool areMoreTokens( );
		void advance( );
		void checkToken( const char *str, const char *stage  );
		void parseBackground( );
		void phongShader(const msgfx::Vector3f& vertex, const msgfx::Vector3f& normal, msgfx::Vector3f camera, const Material& material, RGBColor& surfaceColor);
		float parseFloat( );
    double parseDouble( );
		int parseInt( );
		void parseMaterials( );
		void parseGroup( );
		void parseLightGroup();

		void parseAmbientLight();
		Light* parseLight();
		Triangle* parseTriangle( );
		Sphere*  parseSphere( );
		Plane* parsePlane( );
		TriangleMesh* parseTriangleMesh();
		Reflective* parseReflectiveMaterial();
		Matte* parseMatteMaterial();
		Phong* parsePhongMaterial();
};

std::ostream& operator <<( std::ostream &out, const Scene &s );
std::ostream& operator <<( std::ostream &out, const Magick::Color &c );


#endif

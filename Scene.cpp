/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */

#include "Scene.h"
#include "Triangle.h"
#include "TriangleMesh.h"
#include "Plane.h"
#include "OrthoCamera.h"
#include "PerspectiveCamera.h"
#include "ViewPlane.h"
#include "PlyModel.h"
#include "DirectionalLight.h"
#include <string>
#include <string.h>
#include <cmath>
#include <assert.h>
#include <limits>
#define KA 0.01
#define KD 0.5
#define KS 0.5
#define PIDIV180 0.0174532925

struct Color
{
	float r, g, b;
};
Scene::Scene( string inputFilename, string outputFilename, string depthFilename ) :
	myInputSceneFile( inputFilename ),
	myOutputFile( outputFilename ),
	myDepthFile( depthFilename ),
	myBackgroundColor( 0.0, 0.0, 0.0 ),
	lineNumber(0),
	tokenCount(0),
	length(0),
	i(0),
	j(0)
{
	myNumberOfMaterials = -1;
	materials = NULL;
	myCurrentMaterial = NULL;
	myGroup = NULL;
	myCamera = NULL;
	myLights = NULL;
}

Scene::~Scene( ){
	// Free up materials
	for(int i = 0; i < myNumberOfMaterials; ++i)
	{
		delete materials[i];
	}
	delete [] materials;
	delete myCamera;

	// Free up group
	delete myGroup;

	for(int i = 0; i < myNumberOfLights; ++i)
	{
		delete myLights[i];
	}
	delete [] myLights;
}

Camera& Scene::camera( ){
	return( *myCamera );
}

Magick::Color& Scene::backgroundColor( ){
	return( myBackgroundColor );
}

int Scene::numberOfMaterials( ){
	return( myNumberOfMaterials );
}

void Scene::setCurrentMaterial( int i ){
	if( i >= myNumberOfMaterials ){
	  throw( "Index out of range" );	
	}else{
		myCurrentMaterial = materials[i];
	}
}

Material* Scene::currentMaterial( ){
	return( myCurrentMaterial );
}

Group* Scene::group( ){
	return( myGroup );
}

string& Scene::inputSceneFile( ){
	return( myInputSceneFile );
}

string& Scene::outputFile( ){
	return( myOutputFile );
}

string& Scene::depthFile( ){
	return( myDepthFile );
}

bool Scene::hasInputSceneFilePath( void ){
	bool ret = true;
	if( myInputSceneFile == "" ){
		ret = false;
	}
	return( ret );
}

bool Scene::hasOutputFilePath( void ){
	bool ret = true;
	if( myOutputFile == "" ){
		ret = false;
	}
	return( ret );
}

bool Scene::hasDepthFilePath( void ){
	bool ret = true;
	if( myDepthFile == "" ){
		ret = false;
	}
	return( ret );
}


void Scene::setInputSceneFile( string file ){
	myInputSceneFile = file;
}

void Scene::setOutputFile( string file ){
	myOutputFile = file;
}

void Scene::setDepthFile( string file ){
	myDepthFile = file;
}

float Scene::parseFloat( ){
	float ret = (float)atof( currentToken );
	return( ret );
}

double Scene::parseDouble( ){
	double ret = (double)atof( currentToken );
	return( ret );
}

int Scene::parseInt( ){
	int ret = atoi( currentToken );
	return( ret );
}

void Scene::checkToken( const char *str, const char *stage  ){
	if( strcmp( currentToken, str ) != 0 ){
		cerr << stage << " parse error at line " << lineNumber << " token " << tokenCount << ": " << currentToken << endl;
		cerr << "Current line: " << currentLine << endl;
		cerr << "Expected \'" << str << "\'" << endl;
		exit( 1 );
	}
}

void Scene::parseCamera( ){
	// You will need to adjust this so that the result 
	// from parseFloat is stored somewhere meaningful.
	ViewPlane vp;
	int i;
	float vec[3];
	nextToken( );
	if(strcmp("OrthographicCamera", currentToken) == 0)
	{
		nextToken( );
		OrthographicCamera *camera = new OrthographicCamera();
		checkToken( "{", "Camera" );
		nextToken( );
		checkToken( "center", "Camera" );
		for(i = 0; i < 3; i++ ){
			nextToken( );
			vec[i] = parseFloat( );
		}
		camera->Position(vec[0], vec[1], vec[2]);
		nextToken( );
		checkToken( "direction", "Camera" );
		for(i = 0; i < 3; i++ ){
			nextToken( );
			vec[i] = parseFloat( );
		}
		camera->Direction(vec[0], vec[1], vec[2]);
		nextToken( );
		checkToken( "up", "Camera" );
		for(i = 0; i < 3; i++ ){
			nextToken( );
			vec[i] = parseFloat( );
		}
		camera->Up(vec[0], vec[1], vec[2]);
		nextToken( );
		checkToken( "}", "Camera" );
		camera->CalculateOrthoNormalBases();

		myCamera = camera;
	}
	else if(strcmp("PerspectiveCamera", "PerspectiveCamera") == 0)
	{
		nextToken();
		PerspectiveCamera *camera = new PerspectiveCamera();
		checkToken( "{", "Camera" );
		nextToken( );
		checkToken("center", "PerspectiveCamera");
		for(i = 0; i < 3; ++i)
		{
			nextToken();
			vec[i] = parseFloat();
		}
		camera->Position(vec[0], vec[1], vec[2]);
		nextToken();
		checkToken("direction", "PerspectiveCamera");
		for(i = 0; i < 3; ++i)
		{
			nextToken();
			vec[i] = parseFloat();
		}
		camera->Direction(vec[0], vec[1], vec[2]);
		nextToken();
		checkToken("up", "PerspectiveCamera");
		for(i = 0; i < 3; ++i)
		{
			nextToken();
			vec[i] = parseFloat();
		}
		camera->Up(vec[0], vec[1], vec[2]);
		nextToken();
		checkToken("distance", "PerspectiveCamera");
		nextToken();
		vec[0] = parseFloat();
		camera->Distance(vec[0]);
		nextToken();
		checkToken("}", "PerspectiveCamera");
		camera->CalculateOrthoNormalBases();
		myCamera = camera;
	}
	else
	{
		std::cerr << "No camera defined";
		exit(1);
	}
}

void Scene::parseViewPlane( )
{
	float width, height, pixelSize;
	nextToken();
	checkToken("ViewPlane", "ViewPlane");
	nextToken();
	checkToken("{", "ViewPlane");
	nextToken();
	checkToken("width", "ViewPlane");
	nextToken();
	width = parseFloat();
	nextToken();
	checkToken("height", "ViewPlane");
	nextToken();
	height = parseFloat();
	nextToken();
	checkToken("pixelsize", "ViewPlane");
	nextToken();
	pixelSize = parseFloat();
	nextToken();
	checkToken("}", "ViewPlane");
	myViewplane.HorizontalResolution(width);
	myViewplane.VerticalResolution(height);
	myViewplane.PixelSize(pixelSize);
	myCamera->viewPlane(myViewplane);
}

void Scene::parseBackground( ){
	// You will need to adjust this so that the result 
	// from parseFloat is stored somewhere meaningful.	
	float vec[3];
	nextToken( );
	checkToken( "Background", "Background" );
	nextToken( );
	checkToken( "{", "Background" );
	
	nextToken( );
	checkToken( "color", "Background" );
	for( int i = 0; i < 3; i++ ){
		nextToken( );
		vec[i] = parseFloat( );
	}
	
	nextToken( );
	checkToken( "}", "Background" );

	// Convert floats to unsigned char
	myBackgroundColor.red(vec[0]);
	myBackgroundColor.green(vec[1]);
	myBackgroundColor.blue(vec[2]);
}

void Scene::parseMaterials( ){
	nextToken();
	checkToken("Materials", "Materials");
	nextToken();
	checkToken("{", "Materials");
	nextToken();
	checkToken("numMaterials", "Materials");
	nextToken();
	myNumberOfMaterials = parseInt();
	materials = new Material*[myNumberOfMaterials];

	for(int i = 0; i < myNumberOfMaterials; ++i)
	{
		nextToken();
		checkToken("PhongMaterial", "PhongMaterial");
		materials[i] = new Material();
		nextToken();
		checkToken("{", "PhongMaterial");
		nextToken();
		checkToken("diffuseColor", "PhongMaterial");
		for(int j = 0; j < 3; ++j)
		{
			nextToken();
			materials[i]->diffuseColor[j] = parseFloat();
		}

		nextToken();

		// While not at end of block token
		while(strcmp("}", currentToken) != 0)
		{
			// Check for optional parameters
			if(strcmp("specularColor", currentToken) == 0)
			{
				for(int j = 0; j < 3; ++j)
				{
					nextToken();
					materials[i]->specularColor[j] = parseFloat();
				}
			}
			else if(strcmp("exponent", currentToken) == 0)
			{
				nextToken();
				materials[i]->exponent = parseFloat();
			}
			else if(strcmp("transparentColor", currentToken) == 0)
			{
				for(int j = 0; j < 3; ++j)
				{
					nextToken();
					materials[i]->transparentColor[j] = parseFloat();
				}
			}
			else if(strcmp("reflectiveColor", currentToken) == 0)
			{
				for(int j = 0; j < 3; ++j)
				{
					nextToken();
					materials[i]->reflectiveColor[j] = parseFloat();
				}
			}
			else if(strcmp("indexOfRefraction", currentToken) == 0)
			{
				nextToken();
				materials[i]->indexOfRefraction = parseFloat();
			}
			nextToken();
		}
	}
	nextToken();
	checkToken("}", "Materials");
}

void Scene::parseGroup( ){
	int numObjects;
	int materialIndex = 0;
	Sphere *s = 0;
	Triangle *t = 0;
	Plane *p = 0;
	TriangleMesh* mesh = 0;
	nextToken();
	checkToken("Group", "Group");
	nextToken();
	checkToken("{", "Group");
	nextToken();
	// Instantiate new group
	myGroup = new Group;

	checkToken("numObjects", "Group");
	nextToken();
	numObjects = parseInt();
	for(int i = 0; i < numObjects; ++i)
	{
		nextToken();
		if(strcmp("MaterialIndex", currentToken) == 0)
		{
			// Setting new material index
			nextToken();
			materialIndex = parseInt();
			nextToken();
		}
		if(strcmp("Sphere", currentToken) == 0)
		{
			s = parseSphere();
			s->MaterialIndex(materialIndex);
			myGroup->AddObject(s);
		}
		else if(strcmp("Triangle", currentToken) == 0)
		{
			t = parseTriangle();
			t->MaterialIndex(materialIndex);
			myGroup->AddObject(t);
		}
		else if(strcmp("Plane", currentToken) == 0)
		{
			p = parsePlane();
			p->MaterialIndex(materialIndex);
			myGroup->AddObject(p);
		}
		else if(strcmp("TriangleMesh", currentToken) == 0)
		{
			mesh = parseTriangleMesh();
			mesh->MaterialIndex(materialIndex);
			myGroup->AddObject(mesh);
		}
	}
	nextToken();
	checkToken("}", "Group");
}

void Scene::parseLightGroup()
{
	int numLights;
	Light* l = 0;
	nextToken();
	checkToken("Lights", "Lights");
	nextToken();
	checkToken("{", "Lights");
	nextToken();
	checkToken("numLights", "Lights");
	nextToken();
	numLights = parseInt();
	myLights = new Light*[numLights];
	myNumberOfLights = numLights;

	for(numLights = 0; numLights < myNumberOfLights; ++numLights)
	{
		l = parseLight();
		myLights[numLights] = l;
	}
	nextToken();
	checkToken("}", "Lights");
}

void Scene::parseAmbientLight()
{
	nextToken();
	checkToken("AmbientLight", "AmbientLight");
	nextToken();
	checkToken("{", "AmbientLight");
	nextToken();
	checkToken("color", "AmbientLight");
	float vec[3];
	nextToken();
	for(int i = 0; i < 3; ++i)
	{
		vec[i] = parseFloat();
		nextToken();
	}
	RGBColor color(vec[0], vec[1], vec[2]);
	checkToken("}", "AmbientLight");
	ambientLight = color;
}
Light* Scene::parseLight()
{
	nextToken();
	int i;
	float vec[3];
	if(strcmp("PointLight", currentToken) == 0)
	{
		Light *l;
		checkToken("PointLight", "PointLight");
		nextToken();
		checkToken("{", "PointLight");
		nextToken();
		checkToken("position", "PointLight");
		nextToken();
		
		for(i = 0; i < 3; ++i)
		{
			vec[i] = parseFloat();
			nextToken();
		}
		l = new Light();
		l->Position(vec[0], vec[1], vec[2]);
		checkToken("color", "PointLight");
		nextToken();
		for(i = 0; i < 3; ++i)
		{
			vec[i] = parseFloat();
			nextToken();
		}
		l->Color(vec[0], vec[1], vec[2]);
		if(strcmp("attenuation", currentToken) == 0)
		{
			nextToken();
			for(i = 0; i < 3; ++i)
			{
				vec[i] = parseFloat();
				nextToken();
			}
			l->Attenuation(vec[0], vec[1], vec[2]);
		}
		checkToken("}", "PointLight");
		return l;
	}
	else if(strcmp("DirectionalLight", currentToken) == 0)
	{
		DirectionalLight* dl;
		checkToken("DirectionalLight", "DirectionalLight");
		nextToken();
		checkToken("{", "DirectionalLight");
		nextToken();
		checkToken("position", "DirectionalLight");
		nextToken();
		for(i = 0; i < 3; ++i)
		{
			vec[i] = parseFloat();
			nextToken();
		}
		dl = new DirectionalLight();
		dl->Position(vec[0], vec[1], vec[2]);
		checkToken("direction", "DirectionalLight");
		nextToken();
		for(i = 0; i < 3; ++i)
		{
			vec[i] = parseFloat();
			nextToken();
		}
		dl->Direction(vec[0], vec[1], vec[2]);
		checkToken("color", "DirectionalLight");
		nextToken();
		for(i = 0; i < 3; ++i)
		{
			vec[i] = parseFloat();
			nextToken();
		}
		dl->Color(vec[0], vec[1], vec[2]);
		if(strcmp("angle", currentToken) == 0)
		{
			nextToken();
			vec[0] = parseFloat();
			dl->Angle(vec[0]);
			nextToken();
		}
		if(strcmp("attenuation", currentToken) == 0)
		{
			nextToken();
			for(i = 0; i < 3; ++i)
			{
				vec[i] = parseFloat();
				nextToken();
			}
			dl->Attenuation(vec[0], vec[1], vec[2]);
		}
		checkToken("}", "DirectionalLight");
		return dl;
	}
	else
	{
		// Shouldn't get hit
		std::cerr << "Light expected but not found.";
		exit (1);
	}
}

Triangle* Scene::parseTriangle()
{
    float v[3];
    int i;
    checkToken("Triangle", "Group");
    nextToken();
    checkToken("{", "Triangle");
    nextToken();
    checkToken("vertex0", "Triangle");
    nextToken();
    for(i = 0; i < 3; i++)
    {
        v[i] = parseFloat();
        nextToken();
    }
    msgfx::Vector3f v0(v[0], v[1], v[2]);
    checkToken("vertex1", "Triangle");
    nextToken();
    for(i = 0; i < 3; i++)
    {
        v[i] = parseFloat();
        nextToken();
    }
    msgfx::Vector3f v1(v[0], v[1], v[2]);
    checkToken("vertex2", "Triangle");
    nextToken();
    for(i = 0; i < 3; i++)
    {
        v[i] = parseFloat();
        nextToken();
    }
    msgfx::Vector3f v2(v[0], v[1], v[2]);
    checkToken("}", "Triangle");
    Triangle *t = new Triangle(v0, v1, v2);
    return t;
}

TriangleMesh* Scene::parseTriangleMesh()
{
	std::string fileName;
	checkToken("TriangleMesh", "TriangleMesh");
	nextToken();
	checkToken("{", "TriangleMesh");
	nextToken();
	checkToken("ply_file", "TriangleMesh");
	nextToken();
	fileName = currentToken;
	nextToken();
	checkToken("}", "TriangleMesh");
	FaceList* fl = readPlyModel(fileName.c_str());
	TriangleMesh* mesh = new TriangleMesh(fl);
	delete fl;
	return mesh;
}

Sphere* Scene::parseSphere( )
{
    float center[3];
    float radius;
    checkToken("Sphere", "Group");
    nextToken();
    checkToken("{", "Sphere");
    nextToken();
    checkToken("center", "Sphere");
    for(int j = 0; j < 3; ++j)
    {
            nextToken();
            center[j] = parseFloat();
    }
    nextToken();
    checkToken("radius", "Sphere");
    nextToken();
    radius = parseFloat();
    nextToken();
    checkToken("}", "Sphere");
    Sphere* s = new Sphere(center[0], center[1], center[2], radius);
    return s;
}

Plane* Scene::parsePlane( )
{
	float normal[3];
	float offset;
	checkToken("Plane", "Group");
	nextToken();
	checkToken("{", "Plane");
	nextToken();
	checkToken("normal", "Plane");
	nextToken();
	for(int i = 0; i < 3; i++)
	{
		normal[i] = parseFloat();
		nextToken();
	}
	checkToken("offset", "Plane");
	nextToken();
	offset = parseFloat();
	nextToken();
	checkToken("}", "Plane");
	msgfx::Vector3f v(normal[0], normal[1], normal[2]);
	v.normalize();
	Plane *p = new Plane(v, offset);
	return p;
}


bool Scene::parse( ){	
	bool ret = true;
	lineNumber = 0;
	tokenCount = 0;
	
	inputFileStream.open( myInputSceneFile.c_str( ), ios::in );
	if( inputFileStream.fail( ) ){
		cerr << "Error opening \"" << myInputSceneFile << "\" for reading." << endl;
		exit( 1 );
	}
	parseCamera( );
	parseViewPlane();
	parseAmbientLight();
	parseLightGroup();
	parseBackground( );
	parseMaterials( );
	parseGroup( );

	inputFileStream.close( );
	
	return( ret );
}

bool Scene::areMoreTokens( ){
	bool ret = false;
	if( j < length ){
		ret = true;
	}
	return( ret );
}

void Scene::advance( ){
	if( currentLine[j] == ' ' || currentLine[j] == '\t' || currentLine[j] == '\n' ){
		while( currentLine[j] == ' ' || currentLine[j] == '\t' || currentLine[j] == '\n' ){
			j++;
		}
		i = j;
	}
}
void Scene::nextOnLine( ){
	//advance( );
	while( currentLine[j] != ' ' && currentLine[j] != '\t' && currentLine[j] != '\n' && currentLine[j] != 0 ){
		j++;
	}
	//cout << "ending: " << i <<  ", " << j << endl;
	currentLine[j] = 0;
	int tmp = i;
	if( i != j ){
		while( i <= j ){
			currentToken[i - tmp] = currentLine[i];
			//cout << "copying: " << (i - tmp) <<  ", " << i << endl;
			i++;
		}
		//cerr << lineNumber << ": " << ++tokenCount << ": '" << currentToken << "'" << endl;
	}
	j++;
	i = j;
}

void Scene::nextToken( ){
	if( !inputFileStream.eof( ) ){
		advance( );
		if( areMoreTokens( ) ){
			nextOnLine( );
		}else{
			do{
				inputFileStream.getline( currentLine, sizeof(currentLine) );
				lineNumber++;
				length = strlen( currentLine );
				//cerr << "new line of length: " << length << endl;
			}while( length <= 0 );
			i = 0;
			j = 0;
			advance( );
			//cerr << "Line: " << currentLine << endl;
			if( areMoreTokens( ) ){
				nextOnLine( );
			}
		}
	}
}

void Scene::rayTrace(int dimension)
{
	ViewPlane vp = myCamera->viewPlane();
	vp.PixelSize( (float)(vp.HorizontalResolution() + vp.VerticalResolution()) / (2.0f * dimension) );
	myCamera->viewPlane(vp);
	float bigFloat = MAX_DEPTH;
	int collisions = 0;

	Ray ray;
	Magick::Image shadedImage(Magick::Geometry(dimension, dimension), myBackgroundColor),
		depthImage(Magick::Geometry(dimension, dimension), Magick::Color("white"));

	Hit h1, min;
	std::vector<Object3D*>::const_iterator vecIt;
	std::vector<Object3D*> vecObjects = myGroup->Objects();
	Magick::ColorRGB phong;
	int material = 0;
	//msgfx::Vector3f start, end;
	//const int pixelSize = myCamera->viewPlane().PixelSize();
	int row, col;
	// Create rays
	for(int i = 0; i < dimension * dimension; ++i)
	{
		row = i / dimension;
		col = i % dimension;
		/*if(i % dimension == 0)
		{
			currentPosition = topLeftPosition - cameraUp * (i / dimension) * partitionSize;
		}
		ray.Start(currentPosition);
		ray.End(start + cameraDirection * bigFloat);*/
		myCamera->ComputeRay(col, row, ray);
		

		min.Depth() = std::numeric_limits<float>::max();
		h1.Depth() = std::numeric_limits<float>::max();

		// Check if ray intersects with any objects
		for(vecIt = vecObjects.begin(); vecIt != vecObjects.end(); ++vecIt)
		{
			if((*vecIt)->intersects(ray, h1))
			{
				if(h1.Depth() < min.Depth())
				{
					min = h1;
					collisions++;
					material = (*vecIt)->MaterialIndex();
				}
			}
		}
		

		if(min.Depth() < std::numeric_limits<float>::max() && min.Depth() > 0.f)
		{
			// Ray collided with object
			// Set pixel in depth image
			depthImage.pixelColor(col, row, Magick::ColorRGB(min.Depth(), min.Depth(), min.Depth()));
			
			// Calculate shading
			phongShader(min.Position(), min.Normal(), ray.Start(), *materials[material], phong);
			shadedImage.pixelColor(col, row, phong);
		}

		// Adjust currentPosition to the "right" by one pixel sample
		//currentPosition += cameraRight * partitionSize;

	}

	depthImage.write( myDepthFile );
	shadedImage.write( myOutputFile );
	//printf("%d collisions from %d rays.\n", collisions, dimension * dimension);
}

void Scene::phongShader(const msgfx::Vector3f& vertex, const msgfx::Vector3f& normal, msgfx::Vector3f camera, const Material& material, Magick::ColorRGB& surfaceColor)
{
	msgfx::Vector3f reflection, light, lightPos;
	RGBColor c = ambientLight;
	DirectionalLight* dl;
	c.r *= KA;
	c.g *= KA;
	c.b *= KA;
	float nDotL, rDotV, exponent, attenuation, d, lDotL;
	int k = 0, collisions = 0;
	Ray shadowRay;
	std::vector<Object3D*>::const_iterator vecIt;
	std::vector<Object3D*> vecObjects = myGroup->Objects();
	Hit h;
	
	// Translate camera vector to be with respect to vertex
	camera = camera - vertex;
	camera.normalize();

	for(k = 0; k < myNumberOfLights; ++k)
	{
		// Translate light vector to be with respect to vertex
		light = myLights[k]->Position() - vertex;
		shadowRay.Start(vertex);
		shadowRay.End(myLights[k]->Position());
		d = light.length();
		light.normalize();
		collisions = 0;
		if(myLights[k]->LightType() == Directional)
		{
			dl = (DirectionalLight *) myLights[k];
			lDotL = dl->Direction().dot(-light);
			if(lDotL < cos(DEG2RAD(dl->Angle())))
				// Point is outside the cone of the directional light
				continue;
		}
		else
			lDotL = 1.f;

		// Check for intersections between shadow ray and other objects
		for(vecIt = vecObjects.begin(); vecIt != vecObjects.end(); ++vecIt)
		{
			if(!(*vecIt)->intersects(shadowRay, h))
			{
				// Calculate reflection vector
				reflection = normal * 2.0 * (normal.dot(light)) - light;
				reflection.normalize();

				nDotL = normal.dot(light);
				if(nDotL < 0.f)
					continue;
				rDotV = reflection.dot(camera);
				if(rDotV < 0.f)
				{
					rDotV = 0.f;
				}
				exponent = pow(rDotV, material.exponent);

				attenuation = 1 / (d*d*myLights[k]->Attenuation().r + d*myLights[k]->Attenuation().g + myLights[k]->Attenuation().b);

				c.r += attenuation * myLights[k]->Color().r * lDotL * (KD * material.diffuseColor[0] * nDotL + KS * material.specularColor[0] * exponent);
				c.g += attenuation * myLights[k]->Color().g * lDotL * (KD * material.diffuseColor[1] * nDotL + KS * material.specularColor[1] * exponent);
				c.b += attenuation * myLights[k]->Color().b * lDotL * (KD * material.diffuseColor[2] * nDotL + KS * material.specularColor[2] * exponent);
			}
		}
	}
	// Clamp color values to be in range of [0.0, 1.0]
	c.Clamp();
	surfaceColor.red(c.r);
	surfaceColor.green(c.g);
	surfaceColor.blue(c.b);
}

void Scene::write( std::ostream &out ) const {
	out << "Input scene file: " << myInputSceneFile << endl;
	out << "Output file: " << myOutputFile << endl;
	out << "Depth file: " << myDepthFile << endl;
	out << "Camera:" << endl;
	out << *myCamera << endl;
	out << "Background Color: " << myBackgroundColor << endl;
	out << "Number of Materials: " << myNumberOfMaterials << endl;
	out << "Materials:" << endl;
	for(int i = 0; i < myNumberOfMaterials; ++i)
		out << materials[i] << endl;
	out << "Group:" << endl;
	out << myGroup << endl;
}

std::ostream& operator <<( std::ostream &out, const Scene &s ){
	s.write( out );
	return( out );
}

std::ostream& operator <<( std::ostream &out, const Camera &h)
{
	h.write(out);
	return out;
}

std::ostream& operator <<( std::ostream &out, const Material *m)
{
	m->write(out);
	return out;
}

std::ostream& operator <<( std::ostream &out, const Group *g)
{
	g->write(out);
	return out;
}

std::ostream& operator <<( std::ostream &out, const Magick::Color &c ){
  out << "[" << c.redQuantum() << ", " << c.greenQuantum() << ", " << c.blueQuantum() << "]";
  return( out );
}

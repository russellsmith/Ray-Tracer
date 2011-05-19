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
#include "MultiJittered.h"
#include "ViewPlane.h"
#include "PlyModel.h"
#include "DirectionalLight.h"
#include "Constants.h"
#include "Matte.h"
#include "Phong.h"
#include "Reflective.h"
#include <string>
#include <string.h>
#include <cmath>
#include <assert.h>
#include <limits>
#define KA 0.25
#define KD 0.5
#define KS 0.15
#define KR 0.75
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
	Material* material;

	for(int i = 0; i < myNumberOfMaterials; ++i)
	{
		nextToken();
		if(strcmp("Reflective", currentToken) == 0)
		{
			material = parseReflectiveMaterial();
			materials[i] = material;
		}
		else if(strcmp("Phong", currentToken) == 0)
		{
			material = parsePhongMaterial();
			materials[i] = material;
		}
		else if(strcmp("Matte", currentToken) == 0)
		{
			material = parseMatteMaterial();
			materials[i] = material;
		}
		
		//checkToken("PhongMaterial", "PhongMaterial");
		//Reflective* m = new Reflective();
		////materials[i] = new Matte();
		//nextToken();
		//checkToken("{", "PhongMaterial");
		//nextToken();
		//checkToken("diffuseColor", "PhongMaterial");
		//for(int j = 0; j < 3; ++j)
		//{
		//	nextToken();
		//	m->diffuseColor[j] = parseFloat();
		//}
		//RGBColor cd(m->diffuseColor[0], m->diffuseColor[1], m->diffuseColor[2]);
		//m->SetCD(cd);
		//m->SetKA(KA);
		//m->SetKD(KD);
		//materials[i] = m;
		//nextToken();

		///*cd.r = 1.0;
		//cd.g = .2;
		//cd.b = .3;*/
		//m->SetCR(white);
		//m->SetKR(KR);

		//// While not at end of block token
		//while(strcmp("}", currentToken) != 0)
		//{
		//	// Check for optional parameters
		//	if(strcmp("specularColor", currentToken) == 0)
		//	{
		//		for(int j = 0; j < 3; ++j)
		//		{
		//			nextToken();
		//			m->specularColor[j] = parseFloat();
		//		}
		//		RGBColor cs(m->specularColor[0], m->specularColor[1], m->specularColor[2]);
		//		m->SetCS(cs);
		//	}
		//	else if(strcmp("exponent", currentToken) == 0)
		//	{
		//		nextToken();
		//		m->SetExponent(parseFloat());
		//	}
		//	else if(strcmp("transparentColor", currentToken) == 0)
		//	{
		//		for(int j = 0; j < 3; ++j)
		//		{
		//			nextToken();
		//			materials[i]->transparentColor[j] = parseFloat();
		//		}
		//	}
		//	else if(strcmp("reflectiveColor", currentToken) == 0)
		//	{
		//		for(int j = 0; j < 3; ++j)
		//		{
		//			nextToken();
		//			materials[i]->reflectiveColor[j] = parseFloat();
		//		}
		//	}
		//	else if(strcmp("indexOfRefraction", currentToken) == 0)
		//	{
		//		nextToken();
		//		materials[i]->indexOfRefraction = parseFloat();
		//	}
		//	nextToken();
		//}
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

Reflective* Scene::parseReflectiveMaterial(){
	float input[3];
	Reflective* material = NULL;
	checkToken("Reflective", "Reflective");
	nextToken();
	checkToken("{", "Reflective");
	nextToken();

	// Parse ambient coefficient
	checkToken("ambientCoefficient", "Reflective");
	nextToken();
	input[0] = parseFloat();
	nextToken();
	material = new Reflective;
	material->SetKA(input[0]);

	// Parse diffuse coefficient
	checkToken("diffuseCoefficient", "Reflective");
	nextToken();
	input[0] = parseFloat();
	material->SetKD(input[0]);
	nextToken();

	// Parse specular coefficient
	checkToken("specularCoefficient", "Reflective");
	nextToken();
	input[0] = parseFloat();
	material->SetKS(input[0]);
	nextToken();

	// Parse reflection coefficient
	checkToken("reflectionCoefficient", "Reflective");
	nextToken();
	input[0] = parseFloat();
	material->SetKR(input[0]);
	nextToken();

	// Parse exponent
	checkToken("exponent", "Reflective");
	nextToken();
	input[0] = parseFloat();
	material->SetExponent(input[0]);
	nextToken();

	// Parse diffuse color
	checkToken("diffuseColor", "Reflective");
	nextToken();
	int i;
	for(i = 0; i < 3; ++i)
	{
		input[i] = parseFloat();
		nextToken();
	}
	material->SetCD(RGBColor(input[0], input[1], input[2]));

	// Parse specular color
	checkToken("specularColor", "Reflective");
	nextToken();
	for(i = 0; i < 3; ++i)
	{
		input[i] = parseFloat();
		nextToken();
	}
	material->SetCS(RGBColor(input[0], input[1], input[2]));

	// Parse reflective color
	checkToken("reflectionColor", "Reflective");
	nextToken();
	for(i = 0; i < 3; ++i)
	{
		input[i] = parseFloat();
		nextToken();
	}
	material->SetCR(RGBColor(input[0], input[1], input[2]));

	checkToken("}", "Reflective");
	return material;
}
Matte* Scene::parseMatteMaterial(){
	float input[3];
	Matte* material = NULL;
	checkToken("Matte", "Matte");
	nextToken();
	checkToken("{", "Matte");
	nextToken();

	// Parse ambient coefficient
	checkToken("ambientCoefficient", "Matte");
	nextToken();
	input[0] = parseFloat();
	nextToken();
	material = new Matte;
	material->SetKA(input[0]);

	// Parse diffuse coefficient
	checkToken("diffuseCoefficient", "Matte");
	nextToken();
	input[0] = parseFloat();
	material->SetKD(input[0]);
	nextToken();

	// Parse diffuse color
	checkToken("diffuseColor", "Matte");
	nextToken();
	int i;
	for(i = 0; i < 3; ++i)
	{
		input[i] = parseFloat();
		nextToken();
	}
	material->SetCD(RGBColor(input[0], input[1], input[2]));

	checkToken("}", "Matte");
	return material;
}
Phong* Scene::parsePhongMaterial(){
	float input[3];
	Phong* material = NULL;
	checkToken("Phong", "Phong");
	nextToken();
	checkToken("{", "Phong");
	nextToken();

	// Parse ambient coefficient
	checkToken("ambientCoefficient", "Phong");
	nextToken();
	input[0] = parseFloat();
	nextToken();
	material = new Phong;
	material->SetKA(input[0]);

	// Parse diffuse coefficient
	checkToken("diffuseCoefficient", "Phong");
	nextToken();
	input[0] = parseFloat();
	material->SetKD(input[0]);
	nextToken();

	// Parse specular coefficient
	checkToken("specularCoefficient", "Phong");
	nextToken();
	input[0] = parseFloat();
	material->SetKS(input[0]);
	nextToken();

	// Parse exponent
	checkToken("exponent", "Phong");
	nextToken();
	input[0] = parseFloat();
	material->SetExponent(input[0]);
	nextToken();

	// Parse diffuse color
	checkToken("diffuseColor", "Phong");
	nextToken();
	int i;
	for(i = 0; i < 3; ++i)
	{
		input[i] = parseFloat();
		nextToken();
	}
	material->SetCD(RGBColor(input[0], input[1], input[2]));

	// Parse specular color
	checkToken("specularColor", "Phong");
	nextToken();
	for(i = 0; i < 3; ++i)
	{
		input[i] = parseFloat();
		nextToken();
	}
	material->SetCS(RGBColor(input[0], input[1], input[2]));

	checkToken("}", "Phong");
	return material;
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
	//MultiJittered sampler(100);
	ViewPlane vp = myCamera->viewPlane();
	vp.PixelSize( (float)(vp.HorizontalResolution() + vp.VerticalResolution()) / (2.0f * dimension) );
	myCamera->viewPlane(vp);
	float bigFloat = MAX_DEPTH;
	//int collisions = 0;

	Ray ray;
	Magick::Image shadedImage(Magick::Geometry(dimension, dimension), myBackgroundColor),
		depthImage(Magick::Geometry(dimension, dimension), Magick::Color("white"));
	
	Hit h1;
	h1.scenePtr = this;
	h1.recursionDepth = 0;

	RGBColor phong;
	Magick::ColorRGB screenColor;
	int row, col;
	// Create rays
	for(int i = 0; i < dimension * dimension; ++i)
	{
		row = i / dimension;
		col = i % dimension;
		for(int j = 0; j < vp.num_samples; ++j)
		{
			myCamera->ComputeRay(col, row, ray);
			h1.Depth() = std::numeric_limits<float>::max();

			phong = phong + traceRay(ray, 0, h1);
		}

		phong = phong / vp.num_samples;
		

		//if(h1.Depth() < std::numeric_limits<float>::max() && h1.Depth() > 0.f)
		//{
		// Ray collided with object
		// Set pixel in depth image
		depthImage.pixelColor(col, row, Magick::ColorRGB(h1.Depth(), h1.Depth(), h1.Depth()));
			
		screenColor.red(phong.r);
		screenColor.green(phong.g);
		screenColor.blue(phong.b);
		shadedImage.pixelColor(col, row, screenColor);
		//}

		// Adjust currentPosition to the "right" by one pixel sample
		//currentPosition += cameraRight * partitionSize;

	}

	depthImage.write( myDepthFile );
	shadedImage.write( myOutputFile );
	//printf("%d collisions from %d rays.\n", collisions, dimension * dimension);
}

RGBColor Scene::traceRay(Ray r, int depth, Hit& h)
{
	if(depth > RECURSION_DEPTH)
		return black;
	Hit min, h1;
	h1.scenePtr = min.scenePtr = this;
	h1.recursionDepth = min.recursionDepth = depth;
	Ray minRay;
	std::vector<Object3D*>::const_iterator vecIt;
	std::vector<Object3D*> vecObjects = myGroup->Objects();
	min.Depth() = std::numeric_limits<float>::max();
	h1.Depth() = std::numeric_limits<float>::max();
	//int material;
	RGBColor phong;

	// Check if ray intersects with any objects
	for(vecIt = vecObjects.begin(); vecIt != vecObjects.end(); ++vecIt)
	{
		if((*vecIt)->intersects(r, h1))
		{
			h1.ray = r;
			if(h1.Depth() < min.Depth())
			{
				min = h1;
				//collisions++;
				//minRay = r;
				min.materialIndex = (*vecIt)->MaterialIndex();
			}
		}
	}
		

	if(min.Depth() < std::numeric_limits<float>::max() && min.Depth() > 0.f)
	{
		// Ray collided with object
		// Set pixel in depth image
		//depthImage.pixelColor(col, row, Magick::ColorRGB(min.Depth(), min.Depth(), min.Depth()));
			
		// Calculate shading
		phong = materials[min.materialIndex]->shade(min);
		
		h = min;
		return phong;
	}
	else
		return black;
	
}

void Scene::phongShader(const msgfx::Vector3f& vertex, const msgfx::Vector3f& normal, msgfx::Vector3f camera, const Material& material, RGBColor& surfaceColor)
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
	h.scenePtr = this;
	
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
	surfaceColor = c;
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

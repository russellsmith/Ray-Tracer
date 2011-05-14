/* Russell Smith
 * russellsmith@csu.fullerton.edu
 * CS 566
 * February 18, 2011
 */
#include "Hit.h"

Hit::Hit( ) : depth(1.0f), position(0.f, 0.f, 0.f), normal(0.f, 0.f, 0.f)
{

}
Hit::~Hit( )
{

}
float& Hit::Depth() 
{ 
	return depth;
}
msgfx::Vector3f& Hit::Position() 
{
	return position;
}
msgfx::Vector3f& Hit::Normal()
{
	return normal;
}
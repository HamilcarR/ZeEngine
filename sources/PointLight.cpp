#include "PointLight.h"


using namespace std;
using namespace glm;
PointLight::PointLight(vec3 pos,vec3 col,GLfloat inte, vec3 atten,string &uni,string &uni2,string &uni_int,string &uni_atten, GLuint programID) :
	Light(pos,  col,  inte,  atten,  uni,  uni2, uni_int,uni_atten, programID)
{
	

}


PointLight::~PointLight()
{
}


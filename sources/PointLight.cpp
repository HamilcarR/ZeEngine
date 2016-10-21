#include "../includes/PointLight.h"


using namespace std;
using namespace glm;
PointLight::PointLight(vec3 pos,vec3 col,GLfloat inte, vec3 atten,string &uni,string &uni2,string &uni_int,string &uni_atten) :
	Light(pos,  col,  inte,  uni,  uni2, uni_int)
{
	attenuation = atten;
	uniform_attenuation = uni_atten;


	uniform_attenuationI = glGetUniformLocation(programID, uniform_attenuation.c_str());


}


PointLight::~PointLight()
{
}



void PointLight::BindUniform(GLuint programid) {



	Light::BindUniform(programid);
	uniform_attenuationI = glGetUniformLocation(programID, uniform_attenuation.c_str());
	glUniform3f(uniform_attenuationI, attenuation.x, attenuation.y, attenuation.z);



}

void PointLight::operator=(PointLight A) {


	Light::operator=(A);
	attenuation = A.getAttenuation();
	uniform_attenuation = A.getUniformAttenuation();
	uniform_attenuationI = glGetUniformLocation(programID, uniform_attenuation.c_str());


}


void PointLight::setProgramID(GLuint programid) {

	Light::setProgramID(programid);
	uniform_attenuationI = glGetUniformLocation(programID, uniform_attenuation.c_str());


}

#include "Light.h"

using namespace std; 
using namespace glm; 

Light::Light(vec3 pos, vec3 col, GLfloat inte, vec3 atten, string &uni, string &uni2, string &uni_int, string &uni_atten, GLuint programID) 
{





	position = pos;
	color = col;
	uniform_position = uni;
	uniform_color = uni2;
	intensity = inte;
	uniform_intensity = uni_int;
	attenuation = atten;
	uniform_attenuation = uni_atten;

	uniform_positionI = glGetUniformLocation(programID, uniform_position.c_str());
	uniform_colorI = glGetUniformLocation(programID, uniform_color.c_str());
	uniform_intensityI = glGetUniformLocation(programID, uniform_intensity.c_str());
	uniform_attenuationI = glGetUniformLocation(programID, uniform_attenuation.c_str());

}


Light::~Light()
{
}





void Light::BindUniform() {

	glUniform3f(uniform_positionI, position.x, position.y, position.z);
	glUniform3f(uniform_colorI, color.x, color.y, color.z);
	glUniform1f(uniform_intensityI, intensity);
	glUniform3f(uniform_attenuationI, attenuation.x, attenuation.y, attenuation.z);
}
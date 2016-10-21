#include "../includes/Light.h"

using namespace std; 
using namespace glm; 

Light::Light(vec3 pos, vec3 col, GLfloat inte, string &uni, string &uni2, string &uni_int) 
{





	position = pos;
	color = col;
	uniform_position = uni;
	uniform_color = uni2;
	intensity = inte;
	uniform_intensity = uni_int;
	

}


Light::~Light()
{
}





void Light::BindUniform(GLuint id) {

	programID = id; 
	uniform_positionI = glGetUniformLocation(programID, uniform_position.c_str());
	uniform_colorI = glGetUniformLocation(programID, uniform_color.c_str());
	uniform_intensityI = glGetUniformLocation(programID, uniform_intensity.c_str());
	glUniform3f(uniform_positionI, position.x, position.y, position.z);
	glUniform3f(uniform_colorI, color.x, color.y, color.z);
	glUniform1f(uniform_intensityI, intensity);
}





void Light::operator=(Light A) {


	position = A.getPosition();
	color = A.getColor();
	uniform_position = A.getUniformPosition();
	uniform_color = A.getUniformColor();
	intensity = A.getIntensity();
	uniform_intensity = A.getUniformIntensity();

	uniform_positionI = glGetUniformLocation(programID, uniform_position.c_str());
	uniform_colorI = glGetUniformLocation(programID, uniform_color.c_str());
	uniform_intensityI = glGetUniformLocation(programID, uniform_intensity.c_str());

}




void Light::setProgramID(GLuint id) {

	programID = id; 


	uniform_positionI = glGetUniformLocation(programID, uniform_position.c_str());
	uniform_colorI = glGetUniformLocation(programID, uniform_color.c_str());
	uniform_intensityI = glGetUniformLocation(programID, uniform_intensity.c_str());

}




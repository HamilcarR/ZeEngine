#include "DirectionnalLight.h"



DirectionnalLight::DirectionnalLight(glm::vec3 position, glm::vec3 color, GLfloat intensity, glm::vec3 attenuation, std::string &uniform_position, std::string &uniform_color, std::string &uniform_intensity, std::string &uniform_attenuation, GLuint programID) 
	: Light( position, color,  intensity, attenuation,  uniform_position, uniform_color, uniform_intensity, uniform_attenuation, programID)
{
}


DirectionnalLight::~DirectionnalLight()
{
}

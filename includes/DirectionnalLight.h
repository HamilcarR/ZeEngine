
#ifndef DIRECTIONNALLIGHT_H
#define DIRECTIONNALLIGHT_H
#include "Light.h"
class DirectionnalLight :public Light
{
public:
	DirectionnalLight(glm::vec3 position, glm::vec3 color, GLfloat intensity, glm::vec3 attenuation, std::string &uniform_position, std::string &uniform_color, std::string &uniform_intensity, std::string &uniform_attenuation, GLuint programID);
	~DirectionnalLight();
};
#endif

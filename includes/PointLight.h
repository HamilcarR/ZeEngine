#pragma once



#include "Material.h"
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight(glm::vec3 position,glm::vec3 color,GLfloat intensity, glm::vec3 attenuation,std::string &uniform_position,std::string &uniform_color,std::string &uniform_intensity,std::string &uniform_attenuation, GLuint programID);
	~PointLight();
	

private:
	


};


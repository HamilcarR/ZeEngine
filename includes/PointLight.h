#ifndef POINTLIGHT_H
#define POINTLIGHT_H


#include "Material.h"
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight(glm::vec3 position,glm::vec3 color,GLfloat intensity, glm::vec3 attenuation,std::string &uniform_position,std::string &uniform_color,std::string &uniform_intensity,std::string &uniform_attenuation);
	~PointLight();
	
	std::string getUniformAttenuation() { return uniform_attenuation; }
	glm::vec3 getAttenuation() { return attenuation; }
	virtual void setAttenuation(glm::vec3 at) { attenuation = at; }
	void operator=(PointLight A); 
	virtual void BindUniform(GLuint programid); 
	void setProgramID(GLuint programID); 
private:
	
	std::string uniform_attenuation;
	glm::vec3 attenuation;
	GLuint uniform_attenuationI;
};
#endif

#pragma once
#include "Material.h"

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color, GLfloat intensity, glm::vec3 attenuation, std::string &uniform_position, std::string &uniform_color, std::string &uniform_intensity, std::string &uniform_attenuation, GLuint programID);
	virtual ~Light();
	 glm::vec3 getPosition() { return position; }
	glm::vec3 getColor() { return color; }
	GLuint getLocation() { return location_uniform; }

	void setPosition(glm::vec3 pos) { position = pos; }
	virtual void setColor(glm::vec3 col) { color = col; }
	virtual void setAttenuation(glm::vec3 at) { attenuation = at; }

	virtual void BindUniform();
	void setIntensity(float intens) { intensity = intens; }
	GLfloat getIntensity() { return intensity; }

protected:
	std::string uniform_position;
	std::string uniform_color;
	std::string uniform_attenuation;
	std::string uniform_intensity;
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 attenuation;

	GLuint location_uniform;
	GLuint programID;

	GLfloat intensity;

	GLuint uniform_positionI;
	GLuint uniform_colorI;
	GLuint uniform_intensityI;
	GLuint uniform_attenuationI;

};


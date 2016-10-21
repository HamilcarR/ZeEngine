#ifndef LIGHT_H
#define LIGHT_H

#include "Material.h"

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color, GLfloat intensity, std::string &uniform_position, std::string &uniform_color, std::string &uniform_intensity);
	virtual ~Light();
	 glm::vec3 getPosition() { return position; }
	glm::vec3 getColor() { return color; }
	std::string getUniformPosition() { return uniform_position; }
	std::string getUniformColor() { return uniform_color; }
	std::string getUniformIntensity() { return uniform_intensity; }
	
	GLuint getLocation() { return location_uniform; }
	virtual void operator=(Light A);
	void setPosition(glm::vec3 pos) { position = pos; }
	virtual void setProgramID(GLuint programid);
	virtual void setColor(glm::vec3 col) { color = col; }
	virtual void BindUniform(GLuint programID);
	void setIntensity(float intens) { intensity = intens; }
	GLfloat getIntensity() { return intensity; }
	
protected:
	std::string uniform_position;
	std::string uniform_color;
	
	std::string uniform_intensity;
	glm::vec3 position;
	glm::vec3 color;
	

	GLuint location_uniform;
	GLuint programID;

	GLfloat intensity;

	GLuint uniform_positionI;
	GLuint uniform_colorI;
	GLuint uniform_intensityI;


};

#endif

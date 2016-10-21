#ifndef SKYBOX_H
#define SKYBOX_H
#include "Mesh.h"

class Skybox 
{
public:
	Skybox(std::string vertexShader,std::string fragmentShader);
	~Skybox();

	void render(const glm::mat4 projection,const glm::mat4 view);
	void setScale(glm::vec3 scale);

private:

	ShaderReader shader;
	Texture*  texture;
	GLuint buf;
	GLuint projectionMatrix;
	GLuint viewMatrix;
	GLuint modelMatrix;
	float angle = 0.0F;
	glm::mat4 model;
	glm::vec3 scaleSkybox;

	

	

};


#endif


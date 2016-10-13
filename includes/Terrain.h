#pragma once



#include "CustomImporter.h"


 struct Shader {
	std::string vertex_shader;
	std::string fragment_shader;
};
typedef struct Shader Shader;




class Terrain
{
public:
	Terrain(int size,int gridX, int gridZ ,Material &material,Lights *lights);
	~Terrain();

	void Bind();
	void setScale(glm::vec3& scale);
	void render(glm::mat4 view, glm::mat4 projection, Lights lights);
	
	
private:
	int m_size;
	int m_vertex_count;
	int m_posX;
	int m_posZ;
	glm::vec3 scaleTerrain;
	GLfloat* m_vertex;
	GLfloat* m_UVcoord;
	GLuint* m_indices;
	GLfloat* m_normales;

	Material *material;

	GLuint vao;
	GLuint vbo[4];
	glm::mat4 model;

	GLuint uniform_model;
	GLuint uniform_view;
	GLuint uniform_projection;
	GLuint uniform_lights;

	Lights *light_list;
};



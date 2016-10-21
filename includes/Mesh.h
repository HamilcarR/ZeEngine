#ifndef MESH_H
#define MESH_H


#include "Lights.h"
#include <vector>


class Mesh
{
public:
	Mesh(GLfloat vertices[], GLfloat color[], GLfloat UV[], GLuint index[], GLfloat *normales,  GLfloat* tangents, int index_size, int vertex_size, int uv_size, Material &material);
	~Mesh();
	Mesh();

	GLuint *getIndex() { return index.data(); }
	GLuint getIndexSize() { return index_size; }
	GLuint getVertexSize() { return vertex_size; }
	GLuint getUVSize() { return uv_size; }

	GLfloat *getNormals() { return normals.data(); }
	void setData(GLfloat *vertices, GLfloat *color, GLfloat *UV, GLuint *index, GLfloat *normales, GLfloat* tangents, int index_size, int vertex_size, int uv_size, Material &material);

	void setTexture(GLuint tex,int position) { material.setTexture(tex,position); }   /*NB : ne met pas a jour le chemin de texture */
	void setTexture(std::string& name, int position,GLuint tex) { material.setTexture(name, position,tex); }
	void setTexture(Texture *A,int position) { material.setTexture(A,position); }
	GLfloat *getVertices() { return vertices.data(); }
	GLfloat *getColor() { return color.data(); }
	GLfloat	*getUV() { return UV_tex.data(); }

	void Load(glm::mat4 view,glm::mat4 projection,Lights& lights);
	void Bind();

	Texture** getTexture() { return material.getTexture(); }

	void setLights(Lights& light) { lights = light; }

	void setModel(glm::mat4 &matrix) { model = matrix; }
	void add_Uniform_4f(float arg0, float arg1, float arg2, float arg3, float arg4); //add or refresh a vec4 float value to shader
	void add_Uniform_1f(float arg0, float arg1); //add or refresh a 1 float value to shader
	void refresh_Uniform_4f(float arg0, float arg1, float arg2, float arg3, float arg4);
	glm::mat4 &getModel() { return model; }
	void copy(Mesh* mesh);
	void setPosition(glm::vec3 &translation) { position = translation; model = glm::translate(model, translation); }
	void setRotation(glm::vec3 &rotat, float angle) { rotation = glm::vec4(rotat, angle); model = glm::rotate(model, angle, rotat); }
	void setScale(glm::vec3& scalei) { scale = scalei; model = glm::scale(model, scale); }
	bool isTransparent() { return material.isTransparent(); }
	void setTransparency(bool a) { material.setTransparent(a); }
	Material& getMaterial() { return material; }
	void setProperty(glm::vec3 &position, Lights &lights);
	GLfloat* getTangents() { return tangents.data(); }
	void setDraw(bool t) { isDrawn = t; }
	void Load(glm::mat4& projection);
	void addTexture_Material(Texture* A);

private:
	glm::mat4 model;
	glm::vec3 position;
	glm::vec4 rotation;
	glm::vec3 scale;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> color;
	std::vector<GLfloat> UV_tex;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> tangents;
	GLuint vbo[6];
	GLuint vao;
	std::vector<GLuint> index;
	Material material;

	int index_size;
	int vertex_size;
	int uv_size;
	unsigned int materialID;

	GLuint uniform_projection;
	GLuint uniform_model;
	GLuint uniform_view;
	GLuint uniform_lightNumber;

	Lights lights;
	
	std::vector<std::vector<float>> m_optional_uniform_4;
	std::vector<std::vector<float>> m_optional_uniform_1;

	
	/* test*/

	ShaderReader* m_shader;
	Texture **Sample;

protected:
	bool isDrawn;
	
};


#endif

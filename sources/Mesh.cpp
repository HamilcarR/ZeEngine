#pragma once

#include "Renderer.h"
#include "Mesh.h"
#include <ctime>


using namespace std;
using namespace glm;





void Mesh::setData(GLfloat *vert, GLfloat *col, GLfloat *UV, GLuint *ind, GLfloat *normales, GLfloat* tang, int isize, int vsize, int uvsize, Material &mat) {
	/*index = new GLuint[isize];
	vertices = new GLfloat[vsize];
	color = new GLfloat[vsize];
	UV_tex = new GLfloat[uvsize];
	normals = new GLfloat[vsize];
	tangents = new GLfloat[vsize];
	



	material = mat;

	
	index_size = isize;
	vertex_size = vsize;
	uv_size = uvsize;


	for (int i = 0; i < isize; i++) {
		index[i] = ind[i];



	}

	for (int i = 0; i < vsize; i++) {
		vertices[i] = vert[i];
		color[i] = col[i];
		normals[i] = normales[i];
		tangents[i] = tang[i];
	}

	for (int i = 0; i < uvsize; i++)
		UV_tex[i] = UV[i];


	

	glGenVertexArrays(1, &vao);
	glGenBuffers(6, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertex_size * sizeof(GLfloat), vertices, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, vertex_size * sizeof(GLfloat), color, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, uv_size * sizeof(GLfloat), UV_tex, GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size * sizeof(GLuint), index, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glBufferData(GL_ARRAY_BUFFER, vertex_size * sizeof(GLfloat), normals, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
	glBufferData(GL_ARRAY_BUFFER, vertex_size*sizeof(GLfloat), tangents, GL_STREAM_DRAW);




	uniform_projection = glGetUniformLocation(material.getShader()->getProgram(), "projection");
	uniform_model = glGetUniformLocation(material.getShader()->getProgram(), "model");
	uniform_view = glGetUniformLocation(material.getShader()->getProgram(), "view");
	uniform_lightNumber = glGetUniformLocation(material.getShader()->getProgram(), "lightNumber");


	Bind();
	*/

}


void Mesh::copy(Mesh* mesh) {/*
	mesh->setData(vertices, color, UV_tex, index, normals, tangents, index_size, vertex_size, uv_size, material);
	mesh->setDraw(isDrawn);
	mesh->setPosition(position);
	mesh->setRotation(vec3(rotation), rotation.a);

	*/}
Mesh::Mesh() {

}

Mesh::Mesh(GLfloat vert[], GLfloat col[], GLfloat UV[], GLuint ind[], GLfloat *normales,GLfloat* tang, int isize, int vsize, int uvsize,Material &mat)
{
	/*
	index = new GLuint[isize];
	vertices = new GLfloat[vsize];
	color = new GLfloat[vsize];
	UV_tex = new GLfloat[uvsize];
	normals = new GLfloat[vsize];
	tangents = new GLfloat[vsize];
	*/

	isDrawn = true;

	material=mat;

	model = mat4(1.);
	position = vec3(0);
	rotation = vec4(1, 0, 0, 0);
	scale = vec3(1);
	index_size = isize;
	vertex_size = vsize;
	uv_size = uvsize;
	

	for (int i = 0; i < isize; i++) {
		index.push_back(ind[i]);
		


	}

	for (int i = 0; i < vsize; i++) {
		vertices.push_back(vert[i]);
		color.push_back(col[i]);
		normals.push_back( normales[i]);
		tangents.push_back( tang[i]);
	}

	for (int i = 0; i < uvsize; i++) 
		UV_tex.push_back( UV[i]);
	

	
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(6, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()* sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()* sizeof(GLfloat), color.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, UV_tex.size() * sizeof(GLfloat), UV_tex.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLuint), index.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()* sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), tangents.data(), GL_STATIC_DRAW);
	
	


	 uniform_projection= glGetUniformLocation(material.getShader()->getProgram(), "projection");
	 uniform_model= glGetUniformLocation(material.getShader()->getProgram(), "model");
	 uniform_view= glGetUniformLocation(material.getShader()->getProgram(), "view");
	 uniform_lightNumber= glGetUniformLocation(material.getShader()->getProgram(), "lightNumber");
	

	 Bind();
	 


}



void Mesh::setProperty(vec3 &position, Lights& lights) {

	setPosition(position);
	
}



Mesh::~Mesh()
{

}



void Mesh::Bind() {
	
	

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(5);

	glBindVertexArray(0);
}




void Mesh::Load( glm::mat4 view,glm::mat4 projection,Lights &light ) {
	setLights(light);
	

	if (isDrawn) {
		model = mat4(1.0);
		setPosition(position);
		setRotation(vec3(rotation), rotation.a);
		setScale(scale);
		if (isTransparent()) {
			glDisable(GL_CULL_FACE);
		}
		else {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}



		for_each(m_optional_uniform_4.begin(), m_optional_uniform_4.end(), [](vector<float> arg){
																							glUniform4f((unsigned int) arg[0], arg[1], arg[2], arg[3],arg[4]); }  );

		for_each(m_optional_uniform_1.begin(), m_optional_uniform_1.end(), [](vector<float> arg) {
																							glUniform1f((unsigned int) arg[0], arg[1]);});

		glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(view));
		glUniform1i(uniform_lightNumber, lights.getLights().size());

		Material m = material;
		for_each(lights.getLights().begin(), lights.getLights().end(), [&m](Light* M) {M->BindUniform(m.getShader()->getProgram()); });

		glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, index_size, GL_UNSIGNED_INT, 0);





		glBindVertexArray(0);

		glDisableVertexAttribArray(5);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		

	}
	model = mat4(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}



/*For rendering GUIs*/
void Mesh::Load(mat4 &projection) {

	if (isDrawn) {
		model = mat4(1.0);
		setPosition(position);
		setRotation(vec3(rotation), rotation.a);
		setScale(scale);
		if (isTransparent()) {
			glDisable(GL_CULL_FACE);
		}
		else {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}

		{
			glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(model));

			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, index_size, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			glDisableVertexAttribArray(5);
			glDisableVertexAttribArray(3);
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
			

		}

	}
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	model = mat4(1.0);
}










void Mesh::add_Uniform_4f(float arg0, float arg1, float arg2, float arg3, float arg4) {
	vector<float> tab = { arg0,arg1,arg2,arg3,arg4 };
	
	std::vector<vector<float>>::iterator it = std::find_if(m_optional_uniform_4.begin(), m_optional_uniform_4.end(), [&arg0](vector<float> t) { return t[0] == arg0; });
	if (it == m_optional_uniform_4.end())
		m_optional_uniform_4.push_back(tab);
	else
	{
		(*it)[1] = arg1;
		(*it)[2] = arg2;
		(*it)[3] = arg3;
		(*it)[4] = arg4;
	}

};

void Mesh::add_Uniform_1f(float arg0, float arg1) {
	vector<float> tab = { arg0,arg1 };

	std::vector<vector<float>>::iterator it = std::find_if(m_optional_uniform_1.begin(), m_optional_uniform_1.end(), [&arg0](vector<float> t) { return t[0] == arg0; });
	if (it == m_optional_uniform_1.end())
		m_optional_uniform_1.push_back(tab);
	else
	{
		(*it)[1] = arg1;
	}
}

void Mesh::refresh_Uniform_4f(float arg0,float arg1,float arg2,float arg3,float arg4) {
	std::vector<vector<float>>::iterator it = std::find_if(m_optional_uniform_4.begin(), m_optional_uniform_4.end(), [&arg0](vector<float> t) { return t[0] == arg0; });
	if (it != m_optional_uniform_4.end())
	{

		(*it)[1] = arg1;
		(*it)[2] = arg2;
		(*it)[3] = arg3;
		(*it)[4] = arg4;

	}
	else
		throw new exception("array[5] in refresh_uniform_4f not found!");
}







void Mesh::addTexture_Material(Texture* A) {
	material.addSampler(A);
	Renderer *instance = Renderer::getInstance();
	instance->sort();
}
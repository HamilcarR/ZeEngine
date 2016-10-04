#include "Terrain.h"

#define SIZE 200
using namespace std;
using namespace glm;

Terrain::Terrain(int size,int gridX,int gridZ,Material &mat,Lights *lights):m_size(size)
{

	TextureArray* instance = TextureArray::getInstance();

	
	material = &mat;

	m_posX = gridX*size;
	m_posZ = gridZ*size;
	scaleTerrain = vec3(1);
	
	
	m_vertex = new GLfloat[size*size * 3];
	m_UVcoord = new GLfloat[size*size * 2];
	m_normales = new GLfloat[size*size * 3];
	m_indices = new GLuint[(size-1)*(size-1) * 6];

	model = mat4(1.0);
	model = translate(model, vec3(m_posX, 0, m_posZ));
	light_list = lights;

	int vertexPointer = 0;
	for (int i = 0; i < size ; i++) {
		for (int j = 0; j < size; j++) {
			m_vertex[vertexPointer * 3] = (float)j / ((float)size - 1) * SIZE;
			m_vertex[vertexPointer * 3 + 1] = 0;
			m_vertex[vertexPointer * 3 + 2] = (float)i / ((float)size - 1) * SIZE;
			m_normales[vertexPointer * 3] = 0;
			m_normales[vertexPointer * 3 + 1] = 1;
			m_normales[vertexPointer * 3 + 2] = 0;

			m_UVcoord[vertexPointer * 2] = (float)j / ((float)size - 1);
			m_UVcoord[vertexPointer * 2 + 1] = (float)i / ((float)size - 1);

			vertexPointer++;

		}
	}

	int pointer = 0;
	for (int gz = 0; gz < size - 1; gz++) {
		for (int gx = 0; gx < size - 1; gx++) {
			int topLeft = (gz*size) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*size) + gx;
			int bottomRight = bottomLeft + 1;
			m_indices[pointer++] = topLeft;
			m_indices[pointer++] = bottomLeft;
			m_indices[pointer++] = topRight;
			m_indices[pointer++] = topRight;
			m_indices[pointer++] = bottomLeft;
			m_indices[pointer++] = bottomRight;


		}
	}






	glGenVertexArrays(1, &vao);
	glGenBuffers(4, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, size*size * 3 * sizeof(GLfloat), m_vertex, GL_STATIC_DRAW);
	glBindBuffer( GL_ARRAY_BUFFER,vbo[1] );
	glBufferData(GL_ARRAY_BUFFER, size*size * 2 *sizeof(GLfloat), m_UVcoord, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (size - 1)*(size - 1) * 6 * sizeof(GLuint), m_indices, GL_STATIC_DRAW);


	glBindBuffer( GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, size*size * 3 * sizeof(GLfloat), m_normales, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	Bind();


}


Terrain::~Terrain()
{
	delete[] m_indices;
	delete[] m_normales;
	delete[] m_vertex;
	delete[] m_UVcoord;
	

}



void Terrain::Bind() {

	glBindVertexArray(vao);

	glBindBuffer( GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer( GL_ARRAY_BUFFER, vbo[1] );
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	

	glBindVertexArray(0);

}



void Terrain::render(glm::mat4 view, glm::mat4 projection, Lights lights){


	material->Bind();
	model = translate(model, vec3(-100, 0, -100));
	model = scale(model, scaleTerrain);

	glUniformMatrix4fv(glGetUniformLocation(material->getShader()->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(material->getShader()->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(material->getShader()->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));

	glUniform1i(glGetUniformLocation(material->getShader()->getProgram(), "lightNumber"), lights.getLights().size());


	list<Light*> lists = lights.getLights();
	for (list<Light*>::iterator it = lists.begin(); it != lists.end(); it++) {

		(*it)->BindUniform();
	}

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, (m_size - 1)*(m_size - 1) * 6, GL_UNSIGNED_INT, 0);


	
	glBindVertexArray(0);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	material->UnBind();

	model = mat4(1.0);



}

void Terrain::setScale(vec3& sc) {
	scaleTerrain = sc;
}
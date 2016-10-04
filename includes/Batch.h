#pragma once

#include "Mesh.h"

class Batch
{
public:
	Batch();
	Batch(std::list<Mesh*> liste);
	~Batch();



private:

	GLuint *globalIndexArray;
	GLfloat *globalVertexArray;
	GLfloat *TextureArray;

};


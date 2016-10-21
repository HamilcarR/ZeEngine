#ifndef SHADERREADER_H
#define SHADERREADER_H

#include "Texture.h"


class ShaderReader
{
public:
	ShaderReader();
	ShaderReader(std::string vertexS,std::string fragmentS);
	~ShaderReader();
	void useProgram(bool useProgram);
	void checkCompilation(GLuint shader);

	GLuint getProgram() { return programID; }
	
	std::string& getVertex() { return vertexP; }
	std::string& getFragment() { return fragmentP; }

private:
	GLuint fragment;
	GLuint vertex;
	GLuint programID;
	std::string vertexP;
	std::string fragmentP;
};

#endif

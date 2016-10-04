#include "ShaderReader.h"


using namespace std;
ShaderReader::ShaderReader(string &vertexS,string &fragmentS)
{

	vertexP = vertexS;
	fragmentP = fragmentS;
	if (!ifstream(vertexS, ios::in)) {
		cout << "Vertex shader file not found" << endl;
	}
	else if (!ifstream(fragmentS, ios::in)) {
		cout << "Fragment shader file not found" << endl;
	}
	else {
		ifstream fragmentPath(fragmentS, ios::in);
		ifstream vertexPath(vertexS, ios::in);



		vertex = glCreateShader(GL_VERTEX_SHADER);
		fragment = glCreateShader(GL_FRAGMENT_SHADER);

		if (vertex == 0 || fragment == 0) {
			cout << "Shader creation failed!" << endl;
		}

		string vertexSource;
		string fragmentSource;

		vertexSource.assign(istreambuf_iterator<char>(vertexPath), istreambuf_iterator<char>());
		fragmentSource.assign( (istreambuf_iterator<char>(fragmentPath) ), (istreambuf_iterator<char>() ) );

		const char* vchar = vertexSource.c_str();
		const char* fchar = fragmentSource.c_str();
		
		GLint sizev = (const GLint)vertexSource.size();
		GLint sizef = (const GLint)fragmentSource.size();

		glShaderSource(vertex, 1, (const GLchar**)&vchar, &sizev);
		glShaderSource(fragment, 1, (const GLchar**)&fchar, &sizef);

		glCompileShader(vertex);
		glCompileShader(fragment);

		checkCompilation(vertex);
		checkCompilation(fragment);


		programID=glCreateProgram();

		glAttachShader(programID, vertex);
		glAttachShader(programID, fragment);


		glLinkProgram(programID);


		GLint linkStat;
		glGetProgramiv(programID, GL_LINK_STATUS, &linkStat);
		
		if (linkStat != GL_TRUE) {
			GLint logSize = 0;
			GLchar* errorMsg;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logSize);

			errorMsg = (GLchar*)malloc(logSize);
			if (errorMsg == NULL) {
				cout << "Allocation of log error failed in program linkage" << endl;
			}


			glGetProgramInfoLog(programID, logSize, &logSize, errorMsg);

			cout <<"linking program failed:"<< errorMsg << endl;

			free(errorMsg);
			


		}

	}



}


ShaderReader::ShaderReader() {

}

ShaderReader::~ShaderReader()
{
}





void ShaderReader::checkCompilation(GLuint shader) {

	GLint compilationStatus = 0;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationStatus);

	if (compilationStatus != GL_TRUE) {
		GLint logSize = 0;
		GLchar* errorMsg;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);

		errorMsg = (GLchar*)malloc(logSize);
		if (errorMsg == NULL) {
			cout << "Allocation of log error failed in shader compilation" << endl;
		}


		glGetShaderInfoLog(shader, logSize, &logSize, errorMsg);

		if(shader == vertex)
		cout << "compiling vertex shader " << vertexP <<" failed: "  << errorMsg << endl;
		if (shader == fragment)
			cout << "compiling fragment shader "<< fragmentP <<" failed: " << errorMsg << endl;
		
		free(errorMsg);


	}


}


void ShaderReader::useProgram(bool useProgram) {
	
	if (useProgram)
		glUseProgram(programID);
	else
		glUseProgram(0);
}




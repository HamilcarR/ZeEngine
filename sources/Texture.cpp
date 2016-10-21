#include "../includes/Texture.h"


TextureArray* TextureArray::instance = 0;


using namespace std;


Texture::Texture(string &path, bool cubemap) {
	
	string p = "res/textures/";
	
	texture = SOIL_load_OGL_cubemap("res/textures/skybox/right.png", 
									"res/textures/skybox/left.png", 
									"res/textures/skybox/up.png",
									"res/textures/skybox/down.png", 
									"res/textures/skybox/back.png", 
									"res/textures/skybox/front.png", 0, 0, SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_POWER_OF_TWO);
	
texture = SOIL_load_OGL_cubemap("res/textures/skybox/nright.png",
		"res/textures/skybox/nleft.png",
		"res/textures/skybox/nup.png",
		"res/textures/skybox/ndown.png",
		"res/textures/skybox/nback.png",
		"res/textures/skybox/nfront.png", 0, 0, SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_POWER_OF_TWO);

	if (texture == 0) {
		cout << "cube map loading problem ! " << endl;
	}
	else {
		cout << "cube map loaded!" << endl;
	}


	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}


void Texture::BindCubeMap() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

}

void Texture::UnBindCubeMap() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


Texture::Texture(string& file):fileName(file)
{

	const char* filePath = file.c_str();

	glGenTextures(1,&texture);
	
	int w, h;
	image = SOIL_load_image(filePath, &w, &h, 0, SOIL_LOAD_RGBA);
	if (image == 0) {
		cout << "SOIL loading image " << file << " issue!" << endl;
	}	
	else {
		cout << "Texture:  " << file << " loaded" << endl;

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -3.0);
	}

	//glBindTexture(GL_TEXTURE_2D, 0);
	
}


Texture::Texture(GLuint id, string &name) {
	fileName = name;
	texture = id;
	image = NULL;
	cubemap = 0;

}


Texture::Texture() {

}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
	SOIL_free_image_data(image);
	

}



void Texture::Bind(int i) {
	glActiveTexture(GL_TEXTURE0+i);
	glBindTexture(GL_TEXTURE_2D, texture);
}


void Texture::UnBind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}








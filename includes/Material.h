#ifndef MATERIAL_H
#define MATERIAL_H
#include "ShaderReader.h"
#include <exception>
#define SAMPLER_SIZE 20
enum INDEX {DIFFUSE0,NORMAL,OPACITY,DIFFUSE1,DIFFUSE2,DIFFUSE3};

 class Material 
{

public:
	Material(std::string *texture, int size, std::string& vertex,std::string& fragment,float shineDamping,float reflectivity, int id);
	~Material();
	Material();

	GLfloat getReflectivity() { return reflectivity; }
	GLfloat getShineDamping() { return shineDamping; }
	int getSizeSampler() { return size_sampler; }
	bool isTransparent() { return transparency; }
	void setTransparent(bool a) { transparency = a; }
	Texture** getTexture() { return Sampler; }
	void setTexture(GLuint tex,int position) { 
		
		if (position < size_sampler)
			Sampler[position]->setTexture(tex);
		else
			
			throw new std::runtime_error("SET TEXTURE OUT OF BOUNDARIES : setTexture(GLuint,int) - Material.h");
	}

	void setTexture(std::string& name, int position,GLuint tex) {
		if (position < size_sampler) {

			texture[position] = name;
			if (Sampler[position] != nullptr)
				delete Sampler[position];
			TextureArray *instance = TextureArray::getInstance();
			Sampler[position] = instance->addTexture(tex, name);
		}
	}

	void setTexture(Texture *A, int position) {
		if (position < SAMPLER_SIZE) {
			TextureArray *instance = TextureArray::getInstance();
			texture[position] = A->getFileName();
			if (Sampler[position] != nullptr) {
//				delete Sampler[position];
				Sampler[position] = nullptr;
			}
			
			Sampler[position] = instance->addTexture(A);
			if (position >= size_sampler)
				size_sampler++;
			
		}
		else 
			throw new std::runtime_error("SET TEXTURE OUT OF BOUNDARIES : setTexture(Texture*,int) - Material.h");
	}
	ShaderReader* getShader() { return shader; }
	void Bind();
	void UnBind();
	bool operator<(Material& material);
	bool operator==(Material& material);
	int getID() { return id; }
	void setID(int a) { id = a; }
	void addSampler(Texture*);
private:
	std::string texture[SAMPLER_SIZE];
	Texture* Sampler[SAMPLER_SIZE];//[0] =  diffuse , [1] = normal map , [2] = opacity
	int size_sampler;
	bool transparency;
	int id;
	ShaderReader* shader;
	GLfloat reflectivity;
	GLfloat shineDamping;
	GLuint uniform_reflectivity;
	GLuint uniform_shineDamping;
	GLuint uniform_opacity;
	GLuint uniform_diffuse;
	GLuint uniform_normals;
	GLuint uniform_tex1;
	GLuint uniform_tex2;

};




 class Comparator {

 public:
	 bool operator()(Material& M1, Material &M2);
 };

#endif

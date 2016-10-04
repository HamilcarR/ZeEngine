#pragma once




#include <list>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <SDL.h>
#include<glm.hpp>
#include<gtx/transform.hpp>
#include<gtc/type_ptr.hpp>
#include<SOIL.h>




class Texture
{

	

public:
	Texture();
	Texture(GLuint id, std::string &name);
	Texture(std::string &file );
	Texture(std::string &file, bool isCubeMap);
	~Texture();
	std::string getTexturePath() { return fileName; }
	GLuint getTexture() { return texture; }
	void Bind(int);
	void UnBind();
	std::string& getFileName() { return fileName; }
	void BindCubeMap();
	void UnBindCubeMap();
	void setTexture(GLuint tex) { texture = tex; }
private:
	std::string fileName;
	unsigned char* image;
	GLuint texture;
	unsigned int cubemap;
};

 class TextureArray {
public:

	class Search {
		bool operator()(Texture *id1, Texture *id2) {
			if (id1->getTexture() != id2->getTexture())
				return false;
			else
				return true;
		}


	};

	Texture* addTexture(Texture* A) {



		if (A->getTexture() != 0) {

			for (std::list<Texture*>::iterator it = Texture_Array->begin(); it != Texture_Array->end(); it++) {
				if ((*it)->getTexture() == A->getTexture())
					return *it;
			}
			Texture_Array->push_back(A);
			return A;

		}
		else
			throw new std::exception("addTexture , texture.h , getTexture==0");
	}


	Texture* getTexture(Texture* A) {

		std::list<Texture*>::iterator iterator = std::find_if(Texture_Array->begin(), Texture_Array->end(), [&,A](Texture *B) {return B->getTexture() == A->getTexture(); });
		if (iterator != Texture_Array->end())
			return *iterator;
		else
			return nullptr;
	
	}

	Texture* addTexture(GLuint id,std::string &name) {



		if (id != 0) {

			for (std::list<Texture*>::iterator it = Texture_Array->begin(); it != Texture_Array->end(); it++) {
				if ((*it)->getTexture()==id)
					return *it;
			}
			Texture* A = new Texture(id, name);
			Texture_Array->push_back(A);
			return A;
		
		}
		else
			throw new std::exception("addTexture , texture.h , getTexture==0");
	}


	void addTexture(std::string &texture) {
		if (!texture.empty()) {
			for (std::list<Texture*>::iterator it = Texture_Array->begin(); it != Texture_Array->end(); it++) {
				if ((*it)->getFileName() == texture)
					return;
			}
			Texture_Array->push_back(new Texture(texture));
		}
	}


	bool isPresent(std::string &texture) {
		for (std::list<Texture*>::iterator it = Texture_Array->begin(); it != Texture_Array->end(); it++) {
			if ((*it)->getFileName() == texture)
				return true;
		}
		return false;
	}

	Texture* getTexture(std::string &texture) {
		for (std::list<Texture*>::iterator it = Texture_Array->begin(); it != Texture_Array->end(); it++) {
			if (texture == (*it)->getFileName())
				return *it;
		}

		std::cout << texture << " not in database " << std::endl;
		return nullptr;
	}

	

	Texture* getTexture(GLuint texID) {

		for (Texture* M : *Texture_Array)
			{
				if (M->getTexture() == texID)
					return M;


			}
		return nullptr;

	}


	Texture* getTexture(int a) {
		if ((unsigned int) a > Texture_Array->size())
		{
			std::cout << "out of bound selection texture" << std::endl;
		}
		else {
			int k = 0;
			for (std::list<Texture*>::iterator it = Texture_Array->begin(); it != Texture_Array->end(); it++) {
				if (k == a)
					return (*it);
				k++;
			}
		}
		return NULL;

	}

	static TextureArray* getInstance() {
		if (instance == NULL)
			instance = new TextureArray();
		return instance;
	}

	
	~TextureArray() {
		for (Texture* M : *Texture_Array)
			delete M;
		delete Texture_Array;
		delete instance;
		instance = nullptr;
	}

	void listing() {
		for (std::list<Texture*>::iterator it = Texture_Array->begin(); it != Texture_Array->end(); it++)
			std::cout << (*it)->getFileName() << std::endl;

	}


private:
	std::list<Texture*> *Texture_Array;
	static TextureArray *instance;

	TextureArray() { Texture_Array = new std::list<Texture*>(); }
	

};






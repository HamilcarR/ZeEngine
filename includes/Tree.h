#pragma once

#include "Terrain.h"
#include "MasterObject.h"
#include "Renderer.h"
#include "CustomImporter.h"


class Leaf : MasterObject{
public:

	Leaf(std::list<Mesh*> *liste,glm::vec3 &position,glm::vec3 &rotation);
	~Leaf();
	Leaf();
	void setModel(std::list<Mesh*> *mesh) { leaf_model = mesh; }
	void setPosition(glm::vec3 &position) { leaf_translation = position; }
	void setRotation(glm::vec4 &rotation) { leaf_rotation = glm::vec3(rotation); angle = rotation.w; }
	
	glm::vec3& getPosition() { return leaf_translation; }
	void render(glm::mat4 projection, glm::mat4 view , Lights &lights);
	std::list<Mesh*>* getMeshes() { return leaf_model; }
	void copy(Leaf* F);


private:
	glm::vec3 leaf_translation;
	glm::vec3 leaf_rotation;
	std::list<Mesh*> *leaf_model;
	float angle;










};



class Tree : MasterObject
{
public:

	Tree(std::string &tree_model, std::string &leafs_model,int number_of_leafs,ShaderReader &shader,bool transparency,bool isDrawn,bool isStatic);
	~Tree();
	void setPosition(glm::vec3 &pos);
	void setPosition(glm::vec3 &pos, glm::vec4 &rotation);
	void setRotation(glm::vec4 &rotation);
	glm::vec4& getRotation() { return rotation; }
	glm::vec3& getPosition() { return position; }
	void render( glm::mat4 projection, glm::mat4 view, Lights &lights);
	Tree(Tree *object,bool isDrawn);
	
	std::pair<std::list<Mesh*>*, std::list<Leaf*>*> getModels() {
		return std::pair<std::list<Mesh*>*, std::list<Leaf*>*>(liste, leafs);
	}
	

private:

	std::list<Leaf*> *leafs;
	float speed;
	
	

};








#include "../includes/Tree.h"

#include <random>

using namespace std;
using namespace glm;


Renderer *renderer = Renderer::getInstance();
CustomImporter *importer = CustomImporter::getReference();

/*
Tree::Tree(GLfloat vert[], GLfloat col[], GLfloat UV[], GLuint ind[], GLfloat *normales, int isize, int vsize, int uvsize, Material &material)
	Mesh (vert,  col,  UV,  ind, normales, isize,  vsize,  uvsize,  material)
{


	
}
*/

Leaf::Leaf() {
	leaf_model = new list<Mesh*>();
	leaf_translation = vec3(1.0);
	leaf_rotation = vec3(1.0);
	angle = 0.F;
}

Leaf::Leaf(list<Mesh*> *liste,vec3 &position,vec3 &rotation) {

	leaf_model = liste;
	leaf_translation = position;
	leaf_rotation = rotation;
	angle = 0.0F;


}


Leaf::~Leaf() {
	delete leaf_model;
}

void Leaf::copy(Leaf* F) {
	list<Mesh*>* temp = new list<Mesh*>();
	for (Mesh* mesh : *leaf_model) {
		Mesh* m = new Mesh();
		mesh->copy(m);
		temp->push_back(m);
		
	}

	F->setModel(temp);
	
}
void Leaf::render(glm::mat4 projection, glm::mat4 view,Lights &lights) {

	angle += 0.01F;
	for (list<Mesh*>::iterator E = leaf_model->begin(); E != leaf_model->end();E++) {
		(*E)->setPosition(leaf_translation);
		vec3 A(1,0,0);
		(*E)->setRotation(A ,angle );
		(*E)->setLights(lights);
		
	}

}

vec3 pos(1.0);
/**
Tree::Tree(Tree *tree,bool isDrawn) {
	liste = new list<Mesh*>();
	leafs = new list<Leaf*>();
	pair<list<Mesh*>*, list<Leaf*>*> models = tree->getModels();
	for (Mesh* mesh : (*models.first)) {
		Mesh *m = new Mesh();
		mesh->copy(m);
		liste->push_back(m);
		m->setDraw(isDrawn);

	}

	renderer->add(liste);
	speed = (rand() % 10 + 1) / 1000.F;
	list<Mesh*>* leaf_list = new list<Mesh*>();
	for (Leaf* leaf : (*models.second)) {
		Leaf* L = new Leaf();
		leaf->copy(L);

		leafs->push_back(L);

		for (Mesh* mesh : *L->getMeshes()) {
			leaf_list->push_back(mesh);
		}
		renderer->add(leaf_list);

	}

}
*/


Tree::Tree(string &model,string &leaf,int leaf_number,ShaderReader &shader,bool transparency,bool isDrawn,bool isStatic) : MasterObject(model,shader,transparency,isDrawn,isStatic) {

	rotation = vec4(0, 1, 0,0);
	
	
	
	
	
}




Tree::~Tree()
{
	delete leafs;
	delete liste;
	
}


void Tree::setPosition(vec3 &pos, vec4 &rot) {
	position = pos;
	rotation = rot;
	for (std::list<Mesh*>::iterator it = liste->begin(); it != liste->end(); it++) {
		(*it)->setPosition(position);
		vec3 A(rotation.x, rotation.y, rotation.z);
		(*it)->setRotation(A, rotation.w);
	}
}

void Tree::setPosition(vec3 &pos) {
	position = pos;
	for (std::list<Mesh*>::iterator it = liste->begin(); it != liste->end(); it++) {
		(*it)->setPosition(position);
	}
}

void Tree::setRotation( vec4 &rot) {
	rotation = rot;
	for (std::list<Mesh*>::iterator it = liste->begin(); it != liste->end(); it++) {
		vec3 A(rotation.x, rotation.y, rotation.z);
		(*it)->setRotation(A, rotation.w);
	}
}

/*rotation = vec4(vec3 rotation , angle) */
void Tree::render(mat4 projection,mat4 view, Lights& lights) {

	
	

	for (list<Mesh*>::iterator it = liste->begin(); it != liste->end(); it++) {
		(*it)->setLights(lights);
		

		
	}
	

	if (leafs->size() > 0) {
		float angle = 0.0F;
		for (list<Leaf*>::iterator E = leafs->begin(); E != leafs->end();E++) {
			if ((*E)->getPosition().y > 0) {
				vec3 A(vec3((*E)->getPosition().x, (*E)->getPosition().y - speed, (*E)->getPosition().z));
				(*E)->setPosition(A);
				(*E)->render(projection, view, lights);
			}
			else {
				vec3 A(position.x + (rand() % 10 + 1) / 10, 1.0F, position.z + (rand() % 10 + 1) / 10);
				(*E)->setPosition(A);
				speed = (rand() % 10 + 1) / 1000.F;
			}
			angle += 0.01F;
		}
	}

}

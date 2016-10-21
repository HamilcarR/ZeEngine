#include "../includes/MasterObject.h"
#include "../includes/CustomImporter.h"
#include "../includes/Renderer.h"



using namespace std;
using namespace glm;

MasterObject::MasterObject() {
	liste = new list<Mesh*>();
	position = vec3(0);
	rotation = vec4(0);
	scale = vec3(1);
}

MasterObject::MasterObject(string model, ShaderReader shader, bool transparency, bool isDrawn,bool isStatic) {
	rotation = vec4(0, 1, 0, 0);
	position = vec3(0);
	scale = vec3(1);
	is_Static = isStatic; 
	Renderer *renderer = Renderer::getInstance();
	CustomImporter *importer = CustomImporter::getReference();
	name = model;
	liste = importer->LoadMesh(model, shader);
	if (transparency) {
		for (Mesh* mesh : *liste) {
			mesh->setTransparency(true);
			mesh->setDraw(isDrawn);
		}
	}
	else {
		for (Mesh* mesh : *liste) {
			mesh->setTransparency(false);
			mesh->setDraw(isDrawn);
		}
	}
	if (isStatic)
		renderer->add_static_mesh(liste);
	else
		renderer->add_dynamic_mesh(liste);
}





MasterObject::~MasterObject() {
	for (Mesh* A : *liste)
		delete A;
	delete liste;
	
}



void MasterObject::render(glm::mat4 projection, glm::mat4 view, Lights &lights) {

	for (list<Mesh*>::iterator it = liste->begin(); it != liste->end(); it++) {
		(*it)->setLights(lights);
		(*it)->setPosition(position);
		vec3 X(rotation);
		(*it)->setRotation(X, rotation.a);
		(*it)->setScale(scale);
		(*it)->Load(view, projection, lights);
	}




	

}







void MasterObject::addTexture_Material(Texture* A) {
	cout << "MasterObject adding texture " << A->getFileName() << endl;
	for (Mesh* M : *liste) {
		M->addTexture_Material(A);
	}
}











void MasterObject::setTexture(Texture* A , int position) { 
	
	cout << "MasterObject setting texture " << A->getFileName() << endl;

	for (Mesh* m : *liste) 
		m->setTexture(A, position); 

	Renderer* instance = Renderer::getInstance();

	instance->sort();
}
void MasterObject::setTexture(std::string name, int position, GLuint tex) { 
	
	for (Mesh* m : *liste) m->setTexture(name, position, tex); 

}

void MasterObject::setTexture(GLuint tex, int position) { 
	
	for (Mesh* m : *liste) m->setTexture(tex, position); 
}

void MasterObject::add_uniform_4f( float arg1, float arg2, float arg3, float arg4,string name) {
	cout << "MasterObject add uniform 4f " <<endl;

	list<Mesh*>::iterator it = liste->begin();
	GLuint U = glGetUniformLocation((*it)->getMaterial().getShader()->getProgram(), name.c_str()); 
	for_each(liste->begin(), liste->end(), [&, U, arg1, arg2, arg3, arg4](Mesh* M) {M->add_Uniform_4f(U, arg1, arg2, arg3, arg4); });

}

void MasterObject::add_uniform_1f(float arg1, string name) {

	list<Mesh*>::iterator it = liste->begin();
	GLuint U = glGetUniformLocation((*it)->getMaterial().getShader()->getProgram(), name.c_str());
	for_each(liste->begin(), liste->end(), [&, U, arg1](Mesh* M) {M->add_Uniform_1f(U, arg1); });
}

void MasterObject::refresh_Uniform_4f(float arg0, float arg1, float arg2, float arg3, float arg4) {
	for_each(liste->begin(), liste->end(), [&, arg0, arg1, arg2, arg3, arg4](Mesh* M) {M->refresh_Uniform_4f(arg0, arg1, arg2, arg3, arg4); });
}

void MasterObject::setPosition(vec3 pos, vec4 rot) {
	position = pos;
	rotation = rot;
	for (std::list<Mesh*>::iterator it = liste->begin(); it != liste->end(); it++) {
		(*it)->setPosition(position);
		glm::vec3 A(rotation.x, rotation.y, rotation.z);
		(*it)->setRotation(A, rotation.w);
	}

}


void MasterObject::setScale(vec3 scalei) {
	scale = scalei;
	for (list<Mesh*>::iterator it = liste->begin(); it != liste->end(); it++) 
		(*it)->setScale(scalei);

}

void MasterObject::setPosition(vec3 pos) {
	position = pos;
	for (std::list<Mesh*>::iterator it = liste->begin(); it != liste->end(); it++) {
		(*it)->setPosition(position);
	}
}


void MasterObject::setRotation(vec4 rot) {
		rotation = rot;
	for (std::list<Mesh*>::iterator it = liste->begin(); it != liste->end(); it++) {
		glm::vec3 A(rotation.x, rotation.y, rotation.z);
		(*it)->setRotation(A, rotation.w);
	}
}




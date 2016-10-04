#include "GUI.h"
#include "Renderer.h"
using namespace std;
using namespace glm;

GUI::GUI(std::string &model, ShaderReader &shader, bool transparency, bool isDrawn) : MasterObject()
{

	Renderer *renderer = Renderer::getInstance();
	CustomImporter *importer = CustomImporter::getReference();
	name = model;
	rotation = vec4(1, 0, 0, 90);
	liste = importer->LoadMesh(model, shader);
	
		for (Mesh* mesh : *liste) {
			mesh->setTransparency(transparency);
			mesh->setDraw(isDrawn);
			mesh->setRotation(vec3(1, 0, 0), rotation.a);
		}
	
	

	renderer->add_GUI(liste);


	//Todo : fix rendering...sort
}


GUI::~GUI()
{
}



void GUI::render(mat4& projection) {
	
	for (list<Mesh*>::iterator it = liste->begin(); it != liste->end(); it++)
		(*it)->Load(projection);
	
}


void GUI::setTexture(Texture* A, int position) {
	for (Mesh* m : *liste)
		m->setTexture(A, position);

	Renderer* instance = Renderer::getInstance();

	instance->sort_GUI();
}
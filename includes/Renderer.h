#ifndef RENDERER_H
#define RENDERER_H
#include "Mesh.h"
#include <map>
#include "Tree.h"




class Renderer
{
public:
	static Renderer* getInstance();
	~Renderer();
	void render(glm::mat4 projection,glm::mat4 view,Lights &lights);
	void render_static_meshes(glm::mat4 projection, glm::mat4 view, Lights &lights); 
	void render_dynamic_meshes(glm::mat4 projection, glm::mat4 view, Lights &lights); 
	Material& getMaterial(int a);
	void setScaleObjects(glm::vec3 scale);
	void giveID(Material& material);
	bool existsID(int);
	void add_static_mesh(Mesh* mesh);
	void add_static_mesh(std::list<Mesh*>* liste);
	void add_dynamic_mesh(Mesh* liste);
	void add_dynamic_mesh(std::list<Mesh*>* liste);
	void add(Material& material);
	void add(Material& material, std::list<Mesh*>* newModel);
	void add_Uniform_Meshes_4f(float arg0, float arg1, float arg2, float arg3, float arg4,const std::string vert,const std::string frag,const std::string name);
	void add_GUI(Mesh* liste);
	void add_GUI(std::list<Mesh*>* liste);
	void render_GUI(glm::mat4 projection);
	void sort();
	void sort_static_meshes();
	void sort_dynamic_meshes();
	void sort_GUI();
	friend Mesh* merge(Mesh* M1, Mesh* M2);
private:
	static Renderer *instance;
	Renderer();
	
	std::list<std::pair<Material, std::list<Mesh*>*>*> *m_GUI;
	std::list<std::pair<Material, std::list<Mesh*>* >*> *objects;

	std::list < std::pair<Material, Mesh*>*> *batches;
};
#endif

#pragma once
#include "Mesh.h"



/*For each entity in the world,a mother class to rule them all.*/

class MasterObject
{
	
public:

	MasterObject();
	virtual ~MasterObject();
	MasterObject(std::string &model, ShaderReader &shader, bool transparency, bool isDrawn , bool isStatic);
	virtual void setPosition(glm::vec3 &pos);
	virtual void setPosition(glm::vec3 &pos, glm::vec4 &rotation);
	virtual void setRotation(glm::vec4 &rotation);
	virtual glm::vec3& getPosition() { return position; }
	virtual glm::vec4& getRotation() { return rotation; }
	virtual void setScale(glm::vec3& scalei);
	virtual glm::vec3 getScale() { return scale; }
	virtual void render(glm::mat4 &projection, glm::mat4 &view, Lights &lights);
	std::string getName() { return name; }
	void Draw(bool a) {
		for (Mesh *mesh : *liste)
			mesh->setDraw(a);

	}

	bool isStatic() { return is_Static;  }
	virtual void add_uniform_4f(float arg1, float arg2, float arg3, float arg4, std::string& name);//add a uniform vec4
	virtual void refresh_Uniform_4f(float, float arg1, float arg2, float arg3, float arg4); //update the uniform at location arg0
	virtual void add_uniform_1f(float arg1, std::string& name);
	virtual void setTexture(GLuint tex, int position);
	virtual void setTexture(std::string& name, int position, GLuint tex);
	virtual void setTexture(Texture* A, int position); //replace texture at position 
	virtual void addTexture_Material(Texture* A);//put a texture inside the Sampler array in materials

	
protected:


	std::list<Mesh*> *liste;
	glm::vec3 position;
	glm::vec4 rotation;
	glm::vec3 scale;
	bool is_Static;
	std::string name;

private:

	
};


#ifndef WATER_H
#define WATER_H

#include "MasterObject.h"
#include "Mesh.h"
#include "WaterRenderer.h"
#include "Skybox.h"
class Water : public MasterObject
{



public:
	Water(std::string model, ShaderReader shader, bool transparency, bool isDrawn,bool isStatic);
	~Water();
	void render(Camera* camera,Lights& lights,Terrain *terrain , Skybox* skybox, WindowClass &window);
	void setPlane(glm::vec4& plane) { m_plane = plane; }
	GLuint getPlaneUniform();

	


private :
	GLuint planeUniform;
	WaterRenderer *waterFBO; 
	float time; 
	glm::vec4 m_plane;
};


#endif

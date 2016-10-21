#include "../includes/Water.h"
#include "../includes/CustomImporter.h"
#include "../includes/Texture.h"
using namespace std;
using namespace glm;

const vec4 plane(0, 1, 0, 1);
const float DELTA_TIME = 0.00001f;
 string dudv= "../../res/textures/dudv.png";
 string water_normal = "../../res/Textures/water-n.png";
 string refr = "refractionTexWater"; 
 string refl = "reflectionTexWater";

Water::Water(string model, ShaderReader shader, bool transparency, bool isDrawn,bool isStatic) : MasterObject(model, shader, transparency, isDrawn,isStatic)
{



	waterFBO =new WaterRenderer(); 
	time = 0.f; 
	TextureArray* reference = TextureArray::getInstance(); 
	
	
	
	reference->addTexture(dudv);
	reference->addTexture(water_normal);
	Texture* W = reference->getTexture(dudv);
	Texture* N = reference->getTexture(water_normal);
	Texture* A = reference->getTexture(refr);
	Texture* B = reference->getTexture(refl);
	addTexture_Material(A);
	setTexture(B, 0);
	addTexture_Material(W);
	setTexture(N, 1);
	vec3 pos = vec3(10,0.01,10);
	vec3 scale = vec3(50,1,50); 
	setPosition(pos);
    	setScale(scale);
}


Water::~Water()
{
	delete waterFBO;
}

GLuint Water::getPlaneUniform() {
	return planeUniform;
}


void Water::render(Camera* camera,Lights &scene_lights,Terrain *terrain , Skybox *skybox, WindowClass &window) {
	Renderer *MeshRenderer = Renderer::getInstance();
	string timev = "time";
	add_uniform_1f(time, timev);
	{
		window.clipDistance(0, true);
		waterFBO->BindReflectionBuffer();

		Draw(false);
		window.clearBuffers();
		float distance = 2 * (camera->getPosition().y - 0);
		camera->invert_pitch();
		camera->move(vec3(camera->getPosition().x, camera->getPosition().y - distance, camera->getPosition().z));

		MeshRenderer->add_Uniform_Meshes_4f(0, plane.r, plane.g, plane.b, -0.*getPosition().y, string("vertex.vert"), string("fragment.frag"), string("plane"));
		MeshRenderer->render(camera->getProjectionMatrix(), camera->getViewMatrix(), scene_lights);
		terrain->render(camera->getViewMatrix(), camera->getProjectionMatrix(), scene_lights);
		skybox->render(camera->getProjectionMatrix(), camera->getViewMatrix());
		waterFBO->UnBindFrameBuffer();
		camera->invert_pitch();
		camera->move(vec3(camera->getPosition().x, camera->getPosition().y + distance, camera->getPosition().z));
		window.clipDistance(0, false);
	}

	{

		window.clipDistance(0, true);
		waterFBO->BindRefractionBuffer();
		window.clearBuffers();
		Draw(false);
		
		MeshRenderer->add_Uniform_Meshes_4f(0, plane.r, -plane.g, plane.b, 40 * getPosition().y, string("vertex.vert"), string("fragment.frag"), string("plane"));
		MeshRenderer->render(camera->getProjectionMatrix(), camera->getViewMatrix(), scene_lights);
		terrain->render(camera->getViewMatrix(), camera->getProjectionMatrix(), scene_lights);
		skybox->render(camera->getProjectionMatrix(), camera->getViewMatrix());
		waterFBO->UnBindFrameBuffer();
		window.clipDistance(0, false);
	}
	window.clearBuffers();
	Draw(true); 

	time += DELTA_TIME; 

}




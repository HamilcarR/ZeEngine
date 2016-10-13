
#pragma once

#include "Tree.h"
#include "Skybox.h"
#include "Renderer.h"
#include "WaterRenderer.h"
#include "Water.h"
#include "GUI.h"
#include "PointLight.h"
#include <time.h>
#define WIDTH 1080
#define HEIGHT 900
#define MESH_MATERIAL 0
#define TERRAIN_MATERIAL 1



using namespace std;

using namespace glm;

glm::vec3 translation(0.1);
glm::vec3 lightpos(1.F, 1.F, 1.F);
glm::vec3 lightColor(0.1F);
const vec4 plane(0, 1, 0, 1);



Lights lights = Lights(vector<Light*>());
GLfloat intensity = 100.F;
glm::vec3 attenuation(10, 10, 10);
float reflectivity = 1;
float damping = 10.F;
string l = "lightPos";
string n = "lightColor";
string pathtex("res/textures/ground.jpg");
string pathtexN("res/textures/ground.jpg");
string fragment("fragment.frag");
string vertexx("vertex.vert");

string *terrain_tex_array;
static const GLfloat quad[] = {
	-1.f, -1.f, 0.0f,
	1.f, -1.f, 0.0f,
	-1.f,  1.f, 0.0f,
	-1.f,  1.f, 0.0f,
	1.f, -1.f, 0.0f,
	1.f,  1.f, 0.0f,
};

static const GLfloat textures[] = {
	0.0f, 0.0f,
	1.0f, 0.0f, 
	0.0f,  1.0f,
	-0.0f,  1.0f,
	1.0f, -0.0f,
	1.0f,  1.0f,
};




int main(int argc, char**argv) {
	time_t start = time(0);

	int selector = 0;
	bool move = false;
	float time = 0.0F;

	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "erreur SDL INIT" << endl;
	}
	WindowClass window(HEIGHT, WIDTH);
	
	
	Camera *camera = new Camera(1.0F, 0.1F, glm::vec3(0, 1, 0), 70.F, (float)WIDTH / HEIGHT, 0.1F, 1000.F);

	
	ShaderReader shader(vertexx, fragment);

	terrain_tex_array = new string[2];
	terrain_tex_array[0] = pathtex;
	terrain_tex_array[1] = pathtexN;
	


	string v("skybox.vert");
	string f("skybox.frag");
	Skybox *skybox = new Skybox(v,f);



	

	CustomImporter *importer = CustomImporter::getReference();
	TextureArray *reference = TextureArray::getInstance();

	Renderer * MeshRenderer = Renderer::getInstance();
		
		
		
		Shader* shader_struct =new Shader;
		shader_struct->vertex_shader=string("terrain.vert");
		shader_struct->fragment_shader =string("terrain.frag");

		ShaderReader shader_material(shader_struct->vertex_shader, shader_struct->fragment_shader);
		
		Material terrain_material(terrain_tex_array, 1, shader_struct->vertex_shader,shader_struct->fragment_shader, 1.F, 1.F,TERRAIN_MATERIAL);
		Lights* pointer_to_light;
		pointer_to_light = &lights;
		Terrain* terrain = new Terrain(100, 0, 0, terrain_material, pointer_to_light);
		
		float angle = 0.F;
		float fact = 0.5F;


		

		glm::mat4 model = glm::mat4(1.0F);
		string p("res/tree1.obj");
		Material M;

		

			
		MasterObject *static_scene = new MasterObject(p, shader, true, true,true);
	//	MasterObject *tree = new MasterObject(string("res/lamp.obj"), shader, true, true,true);
	//	MasterObject *lamp = new MasterObject(string("res/lamp.obj"), shader, true, true);
		MasterObject *sphere = new MasterObject(string("res/sphere.obj"), shader, true, true, false); 
		sphere->setScale(vec3(0.1, 0.1, 0.1));
		ShaderReader GuiShader(string("GUI.vert"), string("GUI.frag"));
		ShaderReader waterShader = ShaderReader(string("water.vert"), string("water.frag"));
		
		Water  *water = new Water(string("res/waterQ.obj"), waterShader, false, true,true);
		
		//tree->setPosition(vec3(6, 0, 3));
		
	Light* sun = new PointLight(vec3(0, 500, 0), vec3(0.8, 0.9, 0.7), 600000.F, vec3(10, 10, 10), string("lightPos[" + to_string(6) + "]"), string("lightColor[" + to_string(6) + "]"), string("lightIntensity[" + to_string(6) + "]"), string("attenuation[" + to_string(6) + "]"));
	lights.addLight(new PointLight(lightpos, lightColor, intensity, attenuation, string("lightPos[" + to_string(0) + "]"), string("lightColor[" + to_string(0) + "]"), string("lightIntensity[" + to_string(0) + "]"), string("attenuation[" + to_string(0) + "]")));
	lights.addLight(new PointLight(vec3(4, 1, 4), vec3(0.6, 0.4, 0.3), 60.F, vec3(100, 1000, 10), string("lightPos[" + to_string(1) + "]"), string("lightColor[" + to_string(1) + "]"), string("lightIntensity[" + to_string(1) + "]"), string("attenuation[" + to_string(1) + "]")));
	lights.addLight(new PointLight(vec3(-4, 1, -4),vec3(0.9, 0.7, 0.5), 60.F,vec3(10, 10, 10), string("lightPos[" + to_string(2) + "]"), string("lightColor[" + to_string(2) + "]"), string("lightIntensity[" + to_string(2) + "]"), string("attenuation[" + to_string(2) + "]")));
	lights.addLight(new PointLight(vec3(-10, 1, -3), vec3(0.9, 0.3, 0.2), 60.F, vec3(10,100,10), string("lightPos[" + to_string(3) + "]"), string("lightColor[" + to_string(3) + "]"), string("lightIntensity[" + to_string(3) + "]"), string("attenuation[" + to_string(3) + "]")));
	lights.addLight(new PointLight(vec3(10, 1, -3), vec3(0.3, 0.7, 0.9), 30.F, vec3(10, 10, 10), string("lightPos[" + to_string(4) + "]"), string("lightColor[" + to_string(4) + "]"), string("lightIntensity[" + to_string(4) + "]"), string("attenuation[" + to_string(4) + "]")));
	lights.addLight(new PointLight(vec3(7, 1, 0), vec3(0.4, 0.8, 0.3), 20.F, vec3(10, 10, 10), string("lightPos[" + to_string(5) + "]"), string("lightColor[" + to_string(5) + "]"), string("lightIntensity[" + to_string(5) + "]"), string("attenuation[" + to_string(5) + "]")));
	lights.addLight(sun);
	

	
	
	while (window.getRun()) {
	
		

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
		

			if (event.type == SDL_QUIT )
				window.setRun(false);

			if (event.type == SDL_KEYDOWN) {
				
				 if (event.key.keysym.sym == SDLK_UP) {
					lightColor.y += 0.1F;
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					lightColor.y -= 0.1F;
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					lightColor.x -= 0.1F;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					lightColor.x += 0.1F;
				}

				if (event.key.keysym.sym == SDLK_KP_8) {
					translation.y +=0.1F;
					move = true;
				}
				if (event.key.keysym.sym == SDLK_KP_2) {
					translation.y -= 0.1F;
					move = true;
				}
				if (event.key.keysym.sym == SDLK_KP_6) {
					translation.x += 0.1F;
					move = true;
				}
				if (event.key.keysym.sym == SDLK_KP_4) {
					translation.x -= 0.1F;
					move = true;
				}
				if (event.key.keysym.sym == SDLK_KP_9) {
					translation.z += 0.1F;
				}
				if (event.key.keysym.sym == SDLK_KP_3) {
					translation.z -= 0.1F;
				}
				if (event.key.keysym.sym == SDLK_t) {
					attenuation.x += 1.F;
				}
				else if (event.key.keysym.sym == SDLK_g) {
					attenuation.x -= 1.F;
				}
				else if (event.key.keysym.sym == SDLK_f) {
					attenuation.y += 1.F;
				}
				else if (event.key.keysym.sym == SDLK_h) {
					attenuation.y -= 1.F;
				}
				else if (event.key.keysym.sym == SDLK_y) {
					attenuation.z += 1.F;
				}
				else if (event.key.keysym.sym == SDLK_u) {
					attenuation.z -= 1.F;
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					window.setRun(false);
				}
				else if (event.key.keysym.sym == SDLK_LSHIFT) {
					intensity++; 
					cout << "Intensity : " << intensity << endl; 
				}
				else if (event.key.keysym.sym == SDLK_RSHIFT) {
					intensity--; 
					cout << "Intensity : " << intensity << endl;
				}
				if (event.key.keysym.sym == SDLK_PAGEDOWN) {
					
					if (selector == 0) {
						selector = 0;
					}
				
					else {
						selector--;
					}
				}
				else if (event.key.keysym.sym == SDLK_PAGEUP) {
					 if (selector == lights.getLights().size() - 1) {
						selector = lights.getLights().size() - 1;
					}
					else {
						selector++;
					}
				}
				
				
			}
			
			camera->Move(event);
		
		}
	

		sphere->setPosition(translation);

		


		int k = 0;
		vec3 t = translation; 
		vec3 c = lightColor; 
		vec3 at = attenuation; 
		float inte = intensity;
	

	
		
	
		 
		window.clearBuffers();

		

		water->render(camera, lights, terrain, skybox, window);

		



		
		
		MeshRenderer->render(camera->getProjectionMatrix(), camera->getViewMatrix(), lights);
		terrain->render(camera->getViewMatrix(), camera->getProjectionMatrix(), lights);
		skybox->render(camera->getProjectionMatrix(), camera->getViewMatrix());
		MeshRenderer->render_GUI(camera->getProjectionMatrix());
		window.swapWindow();
		
		
		

		

	}

	

	

	


	
	
	return 0;
}


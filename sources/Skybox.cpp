#include "Skybox.h"

using namespace std;
using namespace glm;



float SIZE = 500.f;


GLfloat VERTICES[] = {
	-SIZE,  SIZE, -SIZE,
	-SIZE, -SIZE, -SIZE,
	SIZE, -SIZE, -SIZE,
	SIZE, -SIZE, -SIZE,
	SIZE,  SIZE, -SIZE,
	-SIZE,  SIZE, -SIZE,

	-SIZE, -SIZE,  SIZE,
	-SIZE, -SIZE, -SIZE,
	-SIZE,  SIZE, -SIZE,
	-SIZE,  SIZE, -SIZE,
	-SIZE,  SIZE,  SIZE,
	-SIZE, -SIZE,  SIZE,

	SIZE, -SIZE, -SIZE,
	SIZE, -SIZE,  SIZE,
	SIZE,  SIZE,  SIZE,
	SIZE,  SIZE,  SIZE,
	SIZE,  SIZE, -SIZE,
	SIZE, -SIZE, -SIZE,

	-SIZE, -SIZE,  SIZE,
	-SIZE,  SIZE,  SIZE,
	SIZE,  SIZE,  SIZE,
	SIZE,  SIZE,  SIZE,
	SIZE, -SIZE,  SIZE,
	-SIZE, -SIZE,  SIZE,

	-SIZE,  SIZE, -SIZE,
	SIZE,  SIZE, -SIZE,
	SIZE,  SIZE,  SIZE,
	SIZE,  SIZE,  SIZE,
	-SIZE,  SIZE,  SIZE,
	-SIZE,  SIZE, -SIZE,

	-SIZE, -SIZE, -SIZE,
	-SIZE, -SIZE,  SIZE,
	SIZE, -SIZE, -SIZE,
	SIZE, -SIZE, -SIZE,
	-SIZE, -SIZE,  SIZE,
	SIZE, -SIZE,  SIZE
};



Skybox::Skybox(string& vertex,string& fragment) 
{

	shader = ShaderReader(vertex, fragment);
	texture = new Texture(string(), true);





	
	projectionMatrix = glGetUniformLocation(shader.getProgram(), "projection");
	viewMatrix = glGetUniformLocation(shader.getProgram(), "view");
	modelMatrix = glGetUniformLocation(shader.getProgram(), "model");
	model = translate(model, vec3(0, 0, 0));


	glGenBuffers(1, &buf);
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glBufferData(GL_ARRAY_BUFFER, 36*3 * sizeof(float), VERTICES, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


Skybox::~Skybox()
{
}



void Skybox::render(mat4 &projection,mat4 &vview) {

	
	angle += 0.000001F;
	shader.useProgram(true);
	texture->BindCubeMap();
	mat4 view = vview;
	model = rotate(angle, vec3(0, 1, 0));
	glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, value_ptr(model));


	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glDrawArrays(GL_TRIANGLES, 0, 36);



	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	texture->UnBindCubeMap();
	shader.useProgram(false);


	


}



void Skybox::setScale(vec3& sc) {
	scaleSkybox = sc;
}
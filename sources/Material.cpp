#include "../includes/Material.h"


using namespace std;

bool Material::operator==(Material& material) {
	if (getSizeSampler() == material.getSizeSampler()) {
		for (int i = 0; i < getSizeSampler(); i++) {
			if (material.getTexture()[i]->getTexturePath().compare(getTexture()[i]->getTexturePath()) != 0) {

				return false;
			}
		}
		if (getReflectivity() == material.getReflectivity() && getShineDamping() == material.getShineDamping()

			&& getShader()->getFragment().compare(material.getShader()->getFragment() ) == 0

			&& getShader()->getFragment().compare(material.getShader()->getFragment()) ==0 ) 

			return true;

		else

			return false;



	}

	else

		return false;

		

}





bool Material::operator<( Material& material) {

	if (getSizeSampler() == material.getSizeSampler()) {

		for (int i = 0; i < getSizeSampler(); i++) {

			if (!material.getTexture()[i]->getTexturePath().compare(getTexture()[i]->getTexturePath()))

				return true;

		}

		if (getReflectivity() == material.getReflectivity() && getShineDamping() == material.getShineDamping()

			&& getShader()->getFragment().compare(material.getShader()->getFragment())

			&& getShader()->getFragment().compare(material.getShader()->getFragment())) {

			return false;

		}

		else

			return true;



	}

	else

		return true;



}









bool Comparator::operator ()(Material& M1, Material& M2) {

		if (M1.getTexture()[0]->getTexture() <= M2.getTexture()[0]->getTexture())

			return false;

		else

			return true;



	}



Material::Material() {



}





Material::Material(string *texture,int size, string &vertex,string &fragment, float shine, float reflecte,int idd):shineDamping(shine),reflectivity(reflecte)

{









	shader = new ShaderReader(vertex, fragment);







	size_sampler = size;

	TextureArray *instance = TextureArray::getInstance();

	

	for (int i = 0; i < size; i++) {

		instance->addTexture(texture[i]);

		Sampler[i] = instance->getTexture(texture[i]);



	}



	id = idd;



	uniform_reflectivity = glGetUniformLocation(shader->getProgram(), "reflectivity");

	uniform_shineDamping = glGetUniformLocation(shader->getProgram(), "shineDamping");

	uniform_opacity = glGetUniformLocation(shader->getProgram(), "opacity");

	uniform_normals = glGetUniformLocation(shader->getProgram(), "normalMap");

	uniform_diffuse = glGetUniformLocation(shader->getProgram(), "diffuse");

	uniform_tex1 = glGetUniformLocation(shader->getProgram(), "texture1");

	uniform_tex2= glGetUniformLocation(shader->getProgram(), "DUDV");





}





Material::~Material()

{

	

//	delete[] Sampler;

	//if(shader!=0)

	//delete shader;



}







void Material::addSampler(Texture* A) {

	

	setTexture(A, size_sampler);



}





void Material::Bind() {

	shader->useProgram(true);

	

	for (int i = 0; i < size_sampler; i++) {

		switch (i)

		{

		case 0:

			Sampler[0]->Bind(0);

			glUniform1i(uniform_diffuse, 0);

			break;

		case 1:

			Sampler[1]->Bind(1);

			glUniform1i(uniform_normals, 1);

			break;

		case 2:

			Sampler[2]->Bind(2);

			glUniform1i(uniform_opacity, 2);

			break;

		case 3:
			Sampler[3]->Bind(3);

			glUniform1i(uniform_tex1, 3);
			break;
		case 4:
			Sampler[4]->Bind(4);

			glUniform1i(uniform_tex2, 4);
			break;


		default:
			break;

		}

	}



	glUniform1f(uniform_reflectivity, reflectivity);

	glUniform1f(uniform_shineDamping, shineDamping);

	



}









void Material::UnBind() {



	Sampler[0]->UnBind();

	shader->useProgram(false);

}

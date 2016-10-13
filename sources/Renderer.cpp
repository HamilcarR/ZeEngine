#include "Renderer.h"

Renderer *Renderer::instance = 0;
using namespace glm;
using namespace std;




void Renderer::setScaleObjects(vec3& scale) {
	
	for (pair<Material, list<Mesh*>*> * M : *objects) {
		for_each(M->second->begin(), M->second->end(), [&scale](Mesh* mesh) {mesh->setScale(scale);   });

	}
}


void Renderer::sort() {
	sort_static_meshes(); 
	sort_dynamic_meshes();

}

void Renderer::sort_dynamic_meshes() {
	for (pair<Material, list<Mesh*>*> * M : *objects) {
		Material D = M->first;
		list<Mesh*>::iterator it;
		it = find_if((M->second)->begin(), (M->second)->end(), [&D](Mesh * mesh) {return  !(mesh->getMaterial() == D); });
		if (it != M->second->end())
		{
			add_dynamic_mesh(*it);
			M->second->erase(it);

		}

	}
}

void Renderer::sort_static_meshes() {

	for (pair<Material, Mesh*> * paire : *batches) {
		if (paire->second !=nullptr && !(paire->first == paire->second->getMaterial())) {
			add_static_mesh(paire->second);
			paire->second = nullptr;
		}
	}

	//just for testing
	/*
	
	*/
}

void Renderer::sort_GUI() {
	for (pair<Material, list<Mesh*>*> * M : *m_GUI) {
		Material D = M->first;
		list<Mesh*>::iterator it;
		it = find_if((M->second)->begin(), (M->second)->end(), [&D](Mesh * mesh) {return  !(mesh->getMaterial() == D) ; });
		if (it != M->second->end())
		{
			add_GUI(*it);
			M->second->erase(it);
			cout << "erased" << endl;
		}

	}
}

Renderer::Renderer()
{
	objects = new list<pair<Material, list<Mesh*> * > * >();
	m_GUI = new list < pair<Material, list<Mesh*> * > * >();
	batches = new list<pair<Material, Mesh*>*>();
}


Renderer::~Renderer()
{
	
	for (list<pair<Material, list<Mesh*>*>*>::iterator it = objects->begin(); it != objects->end(); it++) {
		pair<Material, list<Mesh*>*>* paire = (*it); 
		for (Mesh *M : *(paire->second))
			delete M;

		delete paire;
	}

	for_each(batches->begin(), batches->end(), [](pair<Material,Mesh*>* M) 
											{
												delete M->second;
												delete M; 
																	
											});

}


Renderer *Renderer::getInstance() {
	if (instance == 0)
		instance = new Renderer();
	return instance;
}

/**
Material& Renderer::getMaterial(int a) {
	

	
	return Material();
}
*/




void Renderer::add_Uniform_Meshes_4f(float arg0, float arg1, float arg2, float arg3, float arg4,string& vert,string& frag,string& name) {

	for (pair<Material, Mesh* > * M : *batches) {
		Mesh* D = M->second;

		if (D!= nullptr && D->getMaterial().getShader()->getVertex().compare(vert) == 0 &&
			D->getMaterial().getShader()->getFragment().compare(frag) == 0) {
			GLuint arg0v = glGetUniformLocation(D->getMaterial().getShader()->getProgram(), name.c_str());
			D->add_Uniform_4f(arg0v, arg1, arg2, arg3, arg4);

		}
	}

	
	for (pair<Material , list<Mesh*>*> * M : *objects) {
		
		for (Mesh * D : *M->second) {
			if (D->getMaterial().getShader()->getVertex().compare(vert) == 0 &&
				D->getMaterial().getShader()->getFragment().compare(frag) == 0) {
				GLuint arg0v = glGetUniformLocation(D->getMaterial().getShader()->getProgram(), name.c_str());
				D->add_Uniform_4f(arg0v, arg1, arg2, arg3, arg4);

			}
		}
	}






}




void Renderer::render(mat4 &projection, mat4 &view, Lights &lights) {
	
	
	render_static_meshes(projection, view, lights);
	render_dynamic_meshes(projection, view, lights);

	
	


}


void Renderer::add(Material& material, list<Mesh*>* newModel) {

	
}

bool Renderer::existsID(int i) {


	return false;
}


void Renderer::giveID(Material& material) {
	
}


void Renderer::add(Material& material) {


}



void Renderer::add_GUI(Mesh *mesh) {
	//cout << " SIZE : " << objects.size() << endl;
	for (list<pair<Material, list<Mesh*>*>*>::iterator it = m_GUI->begin(); it != m_GUI->end();it++ ) {
		Material M = ((*it)->first);

	//	cout << "EGAL : " << (M == mesh->getMaterial()) << endl;
		if (mesh->getMaterial().getTexture()[0]->getTexture() == M.getTexture()[0]->getTexture() ) {
			((*it)->second)->push_back(mesh);
			return;
		}
	}

	list<Mesh*> *newList = new list<Mesh*>();
	newList->push_back(mesh);
	pair<Material, list<Mesh*>*> *newPair = new pair<Material, list<Mesh*>*>(mesh->getMaterial(), newList);
	m_GUI->push_back(newPair);

}



void Renderer::add_GUI(list<Mesh*> *mesh) {

	for (list<Mesh*>::iterator it = mesh->begin(); it != mesh->end();it++)
		add_GUI((*it));
	

	
}






Mesh* merge(Mesh* M1, Mesh* M2) {
	vector<GLfloat> newVertex ;
	vector<GLuint> newIndex ;
	vector<GLfloat> newTexture ;
	vector<GLfloat> newNormal ;
	vector<GLfloat> newColor ;
	vector<GLfloat> newTangent ;

	for (unsigned int i = 0; i < M1->getVertexSize(); i++) {
		newVertex.push_back (M1->getVertices()[i]);
		newNormal.push_back(M1->getNormals()[i]);
		newColor.push_back(M1->getColor()[i]);
		newTangent.push_back(M1->getTangents()[i]);
	}

	for (unsigned int i = 0; i < M1->getIndexSize(); i++) 
		newIndex.push_back(M1->getIndex()[i]);

	for (unsigned int i = 0; i < M1->getUVSize(); i++)
		newTexture.push_back(M1->getUV()[i]);


	for (unsigned int i = 0 ; i < M2->getVertexSize(); i++) {
		newVertex.push_back(M2->getVertices()[i]);
		newNormal.push_back(M2->getNormals()[i]);
		newColor.push_back(M2->getColor()[i]);
		newTangent.push_back(M2->getTangents()[i]);
	}

	for (unsigned int i = 0; i < M2->getUVSize(); i++)
		newTexture.push_back(M2->getUV()[i]);



	for (unsigned int i = 0; i < M2->getIndexSize(); i++)
		newIndex.push_back(M2->getIndex()[i] + M1->getVertexSize()/3) ;


	Mesh *newM = new Mesh(newVertex.data(), newColor.data(), newTexture.data(), newIndex.data(), newNormal.data(), newTangent.data(), newIndex.size(),newVertex.size(), newTexture.size(), M1->getMaterial());
	
	

	return newM;



	
	


}






void Renderer::add_dynamic_mesh(Mesh *mesh) {

	
		

	
	for (list<pair<Material, list<Mesh*>*>*>::iterator it = objects->begin(); it != objects->end(); it++) {
		Material M = ((*it)->first);
	
		if (mesh->getMaterial() == M) {
			((*it)->second)->push_back(mesh);
			return;
		}
	}

	list<Mesh*> *newList = new list<Mesh*>();
	newList->push_back(mesh);
	pair<Material, list<Mesh*>*> *newPair = new pair<Material, list<Mesh*>*>(mesh->getMaterial(), newList);
	objects->push_back(newPair);
	
}



void Renderer::add_dynamic_mesh(list<Mesh*> *mesh) {

	
	for (list<Mesh*>::iterator it = mesh->begin(); it != mesh->end(); it++)
		add_dynamic_mesh((*it));
		
}










void Renderer::render_GUI(mat4 &projection) {
	
	glDisable(GL_DEPTH_TEST);
	for (list<pair<Material, list<Mesh*>*>*>::iterator it = m_GUI->begin(); it != m_GUI->end(); it++) {
		((*it)->first).Bind();
			for (list<Mesh*>::iterator it2 = ((*it)->second)->begin(); it2 != ((*it)->second)->end(); it2++) {
				(*it2)->Load(projection);
			}
			((*it)->first).UnBind();

	}

	glEnable(GL_DEPTH_TEST);
}




void Renderer::render_dynamic_meshes(mat4 &projection, mat4 &view, Lights &lights) {
	for (list<pair<Material, list<Mesh*>*>*>::iterator it = objects->begin(); it != objects->end(); it++) {
		((*it)->first).Bind();
		for (list<Mesh*>::iterator it2 = ((*it)->second)->begin(); it2 != ((*it)->second)->end(); it2++) {
			(*it2)->Load(view, projection, lights);
		}


		((*it)->first).UnBind();


	}
}

void Renderer::render_static_meshes(mat4& projection, mat4 &view, Lights &lights) {
	for_each(batches->begin(), batches->end(), [&projection, &view, &lights](pair<Material, Mesh*> *paire) {
		if (paire->second != nullptr) {
			(paire->first).Bind();
			(paire->second)->Load(view, projection, lights);
			(paire->first).UnBind();
		}
	});

}



void Renderer::add_static_mesh(list<Mesh*> *liste) {
	for (list<Mesh*>::iterator it = liste->begin(); it != liste->end(); it++)
		add_static_mesh((*it));
}

void Renderer::add_static_mesh(Mesh* mesh) {
	list<pair<Material, Mesh*>*>::iterator it = find_if(batches->begin(), batches->end(), [&mesh](pair<Material, Mesh*> *paire)
	{
		return mesh->getMaterial() == paire->first;



	}

	);

	if (it != batches->end()) {
		if ((*it)->second == nullptr)
			(*it)->second = mesh;

		else {
			Mesh* M = (*it)->second;
			Mesh* temp = merge(M, mesh);
			(*it)->second = temp;

			delete M;
			delete mesh;


		}

	}
	else {


		batches->push_back(new pair<Material, Mesh*>(mesh->getMaterial(), mesh));
	}
}

/*TODO :1 ) Render static scene + dynamic scene.
2 ) implement water class.




*/
#pragma once


#include "Camera.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>


 class CustomImporter
{
public:
	
	


	std::list<Mesh*>* LoadMesh(std::string& path,ShaderReader&);

	static CustomImporter* getReference() {
		if (reference == 0)
			reference = new CustomImporter();
		return reference;
	}


private:
	CustomImporter();
	~CustomImporter();

	static CustomImporter* reference;

	






};


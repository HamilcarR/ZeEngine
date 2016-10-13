#include "CustomImporter.h"

using namespace std;
using namespace Assimp;
using namespace glm;


TextureArray *instance = TextureArray::getInstance();
CustomImporter *CustomImporter::reference = 0;
CustomImporter::CustomImporter()
{



}


CustomImporter::~CustomImporter()
{
	delete reference;
}





list<Mesh*> * CustomImporter::LoadMesh(string &path,ShaderReader &shader) {
	list<Mesh*> *liste = new list<Mesh*>();
	Importer importer;
	const char* cstr = path.c_str();
	const aiScene* scene = importer.ReadFile(cstr, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices );
	
	
	string positions = "";
	if (!scene) 
		cout << "File : " << path << " not found!" << endl;
	else {
		if (!scene->HasMeshes())
			cout << "No mesh in file" << endl;
		else {
			/*extract all lights in scene
			aiLight **light_array = scene->mLights;
			Lights lights;
			for (int i = 0; i < scene->mNumLights; i++) {
				aiVector3D position_temp = light_array[i]->mPosition;
				vec3 position(position_temp.x, position_temp.y, position_temp.z);
				aiColor3D color_temp = light_array[i]->mColorSpecular;
				vec3 color(color_temp.r, color_temp.g, color_temp.b);
				float attenuation_constante = light_array[i]->mAttenuationConstant;
				float attenuation_lineaire = light_array[i]->mAttenuationLinear;
				float attenuation_quadratique = light_array[i]->mAttenuationQuadratic;
			
				vec3 attenuation(attenuation_constante, attenuation_lineaire, attenuation_quadratique);
				string uniformPos = "lightPos[" + to_string(i) + "]";
				string uniformCol = "lightColor[" + to_string(i) + "]";
				string uniformIntensity = "lightIntensity[" + to_string(i) + "]";
				string uniformAttenuation = "attenuation[" + to_string(i) + "]";


				Light newLight(position, color, 3.F, vec3(10,10,1000), uniformPos, uniformCol, uniformIntensity, uniformAttenuation);

				lights.addLight(newLight);



			}

			
			*/

			/*extract all meshes from the scene*/
			aiMesh** meshArray = scene->mMeshes;
			unsigned int numMeshes = scene->mNumMeshes;
			aiMaterial* material;
			cout << "mesh count: " << scene->mNumMeshes << endl;
				for (unsigned int i = 0; i < numMeshes; i++) {

					
					cout <<  (meshArray[i]->mName).C_Str() << endl;
					int indexSize = (meshArray[i]->mNumFaces)*3;
					int vertexSize = (meshArray[i]->mNumVertices)*3;
					int normalSize = vertexSize;
					int UVSize = (meshArray[i]->mNumVertices)*2;

					GLfloat *vertex=new GLfloat[vertexSize];
					GLfloat *color = new GLfloat[vertexSize]; ;
					GLfloat *normals= new GLfloat[normalSize];
					GLfloat *UV= new GLfloat[UVSize];
					GLuint *index= new GLuint[indexSize];
					GLfloat *tangent = new GLfloat[vertexSize];

					aiVector3t<GLfloat>* vertexArray = (meshArray[i]->mVertices);
					aiVector3t<GLfloat>* normalArray = (meshArray[i]->mNormals);
					aiVector3t<GLfloat>* UVArray =     (meshArray[i]->mTextureCoords)[0];
					aiVector3t<GLfloat>* tangentArray = (meshArray[i]->mTangents);
					
					aiColor4t<GLfloat>* colorArray = (meshArray[i]->mColors)[0];
					if (colorArray != 0) {
						
					}
					

					
					material = scene->mMaterials[meshArray[i]->mMaterialIndex];
					string path[3]; 

					path[0]= "res/";
					path[1] = "res/";
					path[2] = "res/";
					aiString path_temp;
					for (unsigned int k = 0; k < material->GetTextureCount(aiTextureType_DIFFUSE); k++) 

						material->GetTexture(aiTextureType_DIFFUSE, k, &path_temp);


					
					
					string contain = path_temp.C_Str();

						path[0] = path[0] + path_temp.C_Str();
					
					
					instance->addTexture(path[0]);
					cout << "Normal map count :" << material->GetTextureCount(aiTextureType_HEIGHT) << endl;
					for (unsigned int k = 0; k < material->GetTextureCount(aiTextureType_HEIGHT); k++)

						material->GetTexture(aiTextureType_HEIGHT, k, &path_temp);

					 contain = path_temp.C_Str();

					path[1] = path[1] + path_temp.C_Str() ;
					
					instance->addTexture(path[1]);

					for (unsigned int k = 0; k < material->GetTextureCount(aiTextureType_OPACITY); k++)

						material->GetTexture(aiTextureType_OPACITY, k, &path_temp);


					 contain = path_temp.C_Str();
				
						path[2] = path[2] + path_temp.C_Str();
				

					

					instance->addTexture(path[2]);





					for (unsigned int j = 0, k = 0, l = 0; k < meshArray[i]->mNumVertices; j += 3, k++, l += 2) {
						vertex[j] = vertexArray[k].x;
						vertex[j + 1] = vertexArray[k].y;
						vertex[j + 2] = vertexArray[k].z;
						
						normals[j] = normalArray[k].x;
						normals[j + 1] = normalArray[k].y;
						normals[j + 2] = normalArray[k].z;

						if (colorArray != 0) {
							color[j] = colorArray[k].r;
							color[j + 1] = colorArray[k].g;
							color[j + 2] = colorArray[k].b;
							cout << "color array not null" << endl;
						}
						if (UVArray != NULL) {
							UV[l] = UVArray[k].x;
							UV[l + 1] = UVArray[k].y;
						}
						if (tangentArray != NULL) {
							tangent[j] = tangentArray[k].x;
							tangent[j + 1] = tangentArray[k].y;
							tangent[j + 2] = tangentArray[k].z;
						}



					}

					
					
					int k = 0;
					for (unsigned int j = 0; j < meshArray[i]->mNumFaces; j++) {
						
						aiFace &face = meshArray[i]->mFaces[j];
						

						index[k]   = face.mIndices[0];
						index[k+1] = face.mIndices[1];
						index[k+2] = face.mIndices[2];

						k += 3;

						
						
						
					}





					Material material(path,3, shader.getVertex(),shader.getFragment(), 10.F, 0.05F,0);
					
					Mesh * mesh = new Mesh(vertex, color, UV, index, normals,tangent, indexSize, vertexSize, UVSize,material);
					
					liste->push_back(mesh);

				   delete[] vertex;
				   delete[] normals;
				   delete[] UV;
				   delete[] index;
			}
		
				

		
		
		}

		




	}
	
	return liste;

}
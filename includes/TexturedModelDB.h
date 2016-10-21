#ifndef TEXTUREDMODELDB_H
#define TEXTUREDMODELDB_H
#include "MasterObject.h"
#include <vector>

//template<typename T> class Vector;

class TexturedModelDB
{

	
public:
	virtual ~TexturedModelDB();
	static TexturedModelDB* getReference() {
		if (reference == 0)
			reference = new TexturedModelDB();
		return reference;
	}
	virtual void addModel(MasterObject &A);
	void getModel(std::string& name);



protected:


	TexturedModelDB();
	std::vector<MasterObject> *model_array;
	static TexturedModelDB *reference;



};
#endif


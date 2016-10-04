#pragma once


#include "Light.h"

class Lights {

public:
	Lights() { LightsArray =  std::list<Light*>(); }
	Lights(std::list<Light*> &list);

	~Lights();


	std::list<Light*> &getLights() { return LightsArray; }
	void addLight(Light *light) { LightsArray.push_back(light); }
	

private:

	std::list<Light*> LightsArray;



};


#pragma once


#include "Light.h"
#include <vector>
class Lights {

public:
	Lights() { LightsArray =  std::vector<Light*>(); }
	Lights(std::vector<Light*> &list);

	~Lights();


	std::vector <Light*> &getLights() { return LightsArray; }
	void addLight(Light *light) { LightsArray.push_back(light); }
	

private:

	std::vector<Light*> LightsArray;



};


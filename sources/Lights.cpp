#include "Lights.h"





Lights::Lights(std::list<Light*> &list) :LightsArray(list) 
{

}



Lights::~Lights() {
	LightsArray.clear();
		
}
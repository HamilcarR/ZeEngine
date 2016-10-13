

#include "Lights.h"



using namespace std;

Lights::Lights(vector<Light*> &list) :LightsArray(list) 
{

}



Lights::~Lights() {
	LightsArray.clear();
		
}



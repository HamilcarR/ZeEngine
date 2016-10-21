
#ifndef GUI_H
#define GUI_H
#include "MasterObject.h"


//render GUI always last.

class GUI : public MasterObject
{
public:
	GUI(std::string model, ShaderReader shader, bool transparency, bool isDrawn);
	~GUI();

	virtual void render(glm::mat4 projection);
	void setTexture(Texture* A, int position);

protected:


};
#endif

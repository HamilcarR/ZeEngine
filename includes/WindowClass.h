#pragma once


#include "Mesh.h"

class WindowClass
{
public:
	WindowClass(int height, int width );
	~WindowClass();

	void loop();
	bool getRun() { return run; }
	void setRun(bool a) { run = a; }
	SDL_Window* GetWindow() { return window; }
	SDL_Event *getEvent() { return &event; }
	void swapWindow();
	void clearBuffers();
	void clipDistance(int clip, bool val);

private:
	int height;
	int width;
	SDL_Window *window;
	SDL_Event event;
	SDL_GLContext context;
	bool run;
	GLenum glewinit;
};


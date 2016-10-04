#include "WindowClass.h"


using namespace std;

WindowClass::WindowClass(int h,int w)
{
	

	

	height = h;
	width = w;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	window = SDL_CreateWindow("fu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
	
	
	

	if (window == 0) {
		cout << "Creating window fail" << SDL_GetError() << endl;
		SDL_Quit();
	}

	 run = true;
	 context = SDL_GL_CreateContext(window);


	if (context == 0) {
		cout << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();

	}

	glewinit = glewInit();
	glewExperimental = GL_TRUE;
	if (glewinit != GLEW_OK)
	{
		cout << "Glew initialisation" << endl;

		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		SDL_Quit();


	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CLIP_DISTANCE0);

}

void WindowClass::swapWindow() {
	SDL_GL_SwapWindow(GetWindow());
}

void WindowClass::clearBuffers() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
WindowClass::~WindowClass()
{
	SDL_GL_DeleteContext(context);

	SDL_DestroyWindow(window);

	SDL_Quit();
}

void WindowClass::clipDistance(int clip,bool val) {
	if(!val && clip <= 5 && clip >= 0 )
		glDisable(GL_CLIP_DISTANCE0+clip);
	else if (val && clip <= 5 && clip >= 0)
		glEnable(GL_CLIP_DISTANCE0 + clip);
	else
		throw new exception("clip value out of bounds");
}



void WindowClass::loop() {


	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT)
			run = false;
	}

	

}
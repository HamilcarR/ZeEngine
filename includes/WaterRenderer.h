#ifndef WATERRENDERER_H
#define WATERRENDERER_H
#include "Terrain.h"
#include "MasterObject.h"
#include "Renderer.h"
#include "CustomImporter.h"

class WaterRenderer 
{
public:
	WaterRenderer();
	~WaterRenderer();
	GLuint generateFrameBuffer();
	GLuint createTextureAttachment(int width, int height);
	GLuint createDepthTextureAttachment(int width, int height);
	GLuint createDepthRenderBuffer(int width, int height);
	void BindFrameBuffer(GLuint framebuffer,int width,int height);
	void UnBindFrameBuffer();
	void BindReflectionBuffer();
	void BindRefractionBuffer();
	void UnBindBuffer();

	GLuint getRefractionFrameBuffer() { return refractionFB; }
	GLuint getRefractionTexture() { return refractionTEX; }
	GLuint getRefractionRenderBuffer() { return refractionDEPTH; }

	GLuint getReflectionFrameBuffer() { return reflectionFB; }
	GLuint getReflectionTexture() { return reflectionTEX; }
	GLuint getReflectionRenderBuffer() { return reflectionDEPTH; }

private:

	GLuint refractionFB;
	GLuint refractionTEX;
	GLuint refractionDEPTH;

	GLuint reflectionFB;
	GLuint reflectionTEX;
	GLuint reflectionDEPTH;

	Mesh mesh;



};
#endif

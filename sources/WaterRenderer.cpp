#include "../includes/WaterRenderer.h"
constexpr int WIDTH =1080;
constexpr int HEIGHT=900;

constexpr int REFR_WIDTH=2048;
constexpr int REFL_WIDTH=2048;

constexpr int REFL_HEIGHT=2048;
constexpr int REFR_HEIGHT=2048;

using namespace std;
WaterRenderer::WaterRenderer()
{

	TextureArray* reference = TextureArray::getInstance();
	 refractionFB = generateFrameBuffer();
	 refractionTEX = createTextureAttachment(REFR_WIDTH,REFR_HEIGHT);
	 refractionDEPTH = createDepthRenderBuffer(REFR_WIDTH,REFR_HEIGHT);

	 reflectionFB = generateFrameBuffer();
	 reflectionTEX = createTextureAttachment(REFR_WIDTH, REFR_HEIGHT);
	 reflectionDEPTH = createDepthRenderBuffer(REFR_WIDTH, REFR_HEIGHT);
	 string a = "refractionTexWater", b = "reflectionTexWater" ; 

	 reference->addTexture(refractionTEX, a);
	 reference->addTexture(reflectionTEX, b);

	 UnBindFrameBuffer();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaterRenderer::BindRefractionBuffer() {
	glViewport(0, 0, REFR_WIDTH, REFR_HEIGHT);
	BindFrameBuffer(refractionFB, REFR_WIDTH, REFR_HEIGHT);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaterRenderer::BindReflectionBuffer() {
	glViewport(0, 0, REFL_WIDTH, REFR_HEIGHT);
	BindFrameBuffer(reflectionFB, REFL_WIDTH, REFL_HEIGHT);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaterRenderer::UnBindBuffer() {
	UnBindFrameBuffer();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WaterRenderer::~WaterRenderer()
{
	glDeleteFramebuffers(1, &reflectionFB);
	glDeleteFramebuffers(1, &refractionFB);

	glDeleteTextures(1, &reflectionTEX);
	glDeleteTextures(1, &refractionTEX);

	glDeleteRenderbuffers(1, &reflectionDEPTH);
	glDeleteRenderbuffers(1, &refractionDEPTH);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaterRenderer::UnBindFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, WIDTH, HEIGHT);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaterRenderer::BindFrameBuffer(GLuint framebuffer, int w, int h) {
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	//glViewport(0, 0, w, h);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GLuint WaterRenderer::generateFrameBuffer() {
	GLuint framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//glNamedFramebufferDrawBuffer(framebuffer, GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return framebuffer;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GLuint WaterRenderer::createTextureAttachment(int width,int height) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,texture, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)

		cout << " FB COLOR PROBLEM" << endl;
	return texture;


}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GLuint WaterRenderer::createDepthTextureAttachment(int width, int height) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)

		cout << " FB DEPTH PROBLEM" << endl;
	return texture;


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GLuint WaterRenderer::createDepthRenderBuffer(int width, int height) {
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	return depthBuffer;
}



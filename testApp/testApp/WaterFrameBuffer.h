#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class WaterFrameBuffer
{
protected:
	static const int REFLECTION_WIDTH = 320;
	static const int REFRACTION_WIDTH = 1280;
private:
	int WIDTH = 800, HEIGHT = 600;
	static const int REFLECTION_HEIGHT = 180;
	static const int REFRACTION_HEIGHT = 720;

	GLuint reflectionFrameBuffer;
	GLuint reflectionTexture;
	GLuint reflectionDepthBuffer;

	int refractionFrameBuffer;
	int refractionTexture;
	int refractionDepthTexture;

	void initialiseReflectionFrameBuffer() 
	{
		reflectionFrameBuffer = createFrameBuffer();
		reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
		reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	}

	void initialiseRefractionFrameBuffer() 
	{
		refractionFrameBuffer = createFrameBuffer();
		refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
		refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	}

	void bindFrameBuffer(int frameBuffer, int width, int height) 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
	}

	int createFrameBuffer() 
	{
		GLuint frameBuffer;
		glGenFramebuffers( 1,&frameBuffer);
		//generate name for frame buffer
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		//create the framebuffer
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		//indicate that we will always render to color attachment 0
		return frameBuffer;
	}

	int createTextureAttachment(int width, int height) 
	{
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			texture, 0);
		return texture;
	}

	int createDepthTextureAttachment(int width, int height) 
	{
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
		return texture;
	}

	int createDepthBufferAttachment(int width, int height) 
	{
		GLuint depthBuffer;
		glGenRenderbuffers(1,&depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
		return depthBuffer;
	}

public:
	WaterFrameBuffer()
	{
		initialiseReflectionFrameBuffer();
		initialiseRefractionFrameBuffer();
	}
	void bindReflectionFrameBuffer()//call before rendering to this FBO
	{
		bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
	}
	void bindRefractionFrameBuffer()
	{//call before rendering to this FBO
		bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
	}
	void unbindCurrentFrameBuffer() 
	{//call to switch to default frame buffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, WIDTH, HEIGHT);
	}
	int getReflectionTexture() 
	{//get the resulting texture
		return reflectionTexture;
	}
	int getRefractionTexture() 
	{//get the resulting texture
		return refractionTexture;
	}
	int getRefractionDepthTexture() 
	{//get the resulting depth texture
		return refractionDepthTexture;
	}
	
	~WaterFrameBuffer();
};


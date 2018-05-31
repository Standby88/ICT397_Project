#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
* @class WaterFrameBuffer
* @brief used to manage buffers used to display water
*
* @author Desmond
* @version 1
* @date
*
* @todo
*
* @bug
*/
class WaterFrameBuffer
{
protected:
	/// integer for reflection width
	static const int REFLECTION_WIDTH = 320;
	///integer for refraction width
	static const int REFRACTION_WIDTH = 1280;
private:
	///integers for width and height 
	int WIDTH = 800, HEIGHT = 600;
	///integers for reflection height
	static const int REFLECTION_HEIGHT = 180;
	///integers for refraction height
	static const int REFRACTION_HEIGHT = 720;
	///GLuint variable for reflection frame buffer
	GLuint reflectionFrameBuffer;
	///GLuint variable for reflection texture
	GLuint reflectionTexture;
	///GLuint variable for reflection depth buffer
	GLuint reflectionDepthBuffer;
	///integer variable for refraction frame buffer
	int refractionFrameBuffer;
	///integer variable for refraction texture
	int refractionTexture;
	///integer variable for refraction depth buffer
	int refractionDepthTexture;

	/**
	* @brief 
	*
	* @param void
	* @return void
	* @pre
	* @post
	*/
	void initialiseReflectionFrameBuffer() 
	{
		reflectionFrameBuffer = createFrameBuffer();
		reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
		reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	}

	/**
	* @brief
	*
	* @param void
	* @return void
	* @pre
	* @post
	*/
	void initialiseRefractionFrameBuffer() 
	{
		refractionFrameBuffer = createFrameBuffer();
		refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
		refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	}

	/**
	* @brief
	*
	* @param void
	* @return void
	* @pre
	* @post
	*/
	void bindFrameBuffer(int frameBuffer, int width, int height) 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
	}

	/**
	* @brief
	*
	* @param void
	* @return void
	* @pre
	* @post
	*/
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

	/**
	* @brief creates a texture attachment
	*
	* @param int, int
	* @return int
	* @pre
	* @post
	*/
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

	/**
	* @brief creates a depth texture attachment
	*
	* @param int, int
	* @return int
	* @pre
	* @post
	*/
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

	/**
	* @brief creates a depth buffer attachment
	*
	* @param int, int
	* @return int
	* @pre
	* @post
	*/
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

	///Default constructor
	WaterFrameBuffer()
	{
		initialiseReflectionFrameBuffer();
		initialiseRefractionFrameBuffer();
	}

	/**
	* @brief binds the reflection frame buffer
	*
	* @param void
	* @return void
	* @pre 
	* @post
	*/
	void bindReflectionFrameBuffer()//call before rendering to this FBO
	{
		bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
	}

	/**
	* @brief binds the refraction frame buffer
	*
	* @param void
	* @return void
	* @pre
	* @post
	*/
	void bindRefractionFrameBuffer()
	{//call before rendering to this FBO
		bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
	}

	/**
	* @brief unbinds the current frame buffer
	*
	* @param void
	* @return void
	* @pre
	* @post
	*/
	void unbindCurrentFrameBuffer() 
	{//call to switch to default frame buffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, WIDTH, HEIGHT);
	}

	/**
	* @brief returns the reflection texture
	*
	* @param void
	* @return int
	* @pre
	* @post
	*/
	int getReflectionTexture() 
	{//get the resulting texture
		return reflectionTexture;
	}

	/**
	* @brief returns the refraction texture
	*
	* @param void
	* @return int
	* @pre
	* @post
	*/
	int getRefractionTexture() 
	{//get the resulting texture
		return refractionTexture;
	}

	/**
	* @brief returns the refraction depth texture
	*
	* @param void
	* @return int
	* @pre
	* @post
	*/
	int getRefractionDepthTexture() 
	{//get the resulting depth texture
		return refractionDepthTexture;
	}
	
	///Default destructor
	~WaterFrameBuffer();
};


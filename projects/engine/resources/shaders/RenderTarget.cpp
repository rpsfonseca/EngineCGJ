#include "RenderTarget.h"
#include "Texture.h"
#include "GL\glew.h"

RenderTarget::RenderTarget(unsigned int width, unsigned int height)
{
	mWidth = width;
	mHeight = height;

	glGenFramebuffers(1, &mRT_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, mRT_ID);

	Texture texture;
	texture.generateRTTexture();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.tex_id, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer not complete!" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


RenderTarget::~RenderTarget()
{
}

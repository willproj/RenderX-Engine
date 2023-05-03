#include "include/framebuffer.h"


namespace engine::openglcore
{
	Framebuffer::Framebuffer()
		:buffer(0)
	{
		glGenFramebuffers(1, &buffer);
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &buffer);
	}

	void Framebuffer::bindFramebuffer() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	}

	void Framebuffer::unbindFramebuffer() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}




}
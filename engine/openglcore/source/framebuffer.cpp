#include "include/framebuffer.h"


namespace engine::openglcore
{
	Framebuffer::Framebuffer()
		:framebuffer(0), renderBuffer(0), colorAttachment(0), framebufferSize({0,0})
	{

	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &framebuffer);
	}

	void Framebuffer::create(uint32_t width, uint32_t height)
	{
		if (framebuffer)
		{
			glDeleteFramebuffers(1, &framebuffer);
			glDeleteTextures(1, &colorAttachment);
			glDeleteRenderbuffers(1, &renderBuffer);
			glDeleteTextures(1, &redAttachment);
		}

		framebufferSize = { width, height };
		glGenFramebuffers(1, &framebuffer);
		
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		// create a color attachment texture
		glGenTextures(1, &colorAttachment);
		glBindTexture(GL_TEXTURE_2D, colorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);
		
		
		glGenTextures(1, &redAttachment);
		glBindTexture(GL_TEXTURE_2D, redAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, redAttachment, 0);

		GLenum buffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, buffers);

		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		glGenRenderbuffers(1, &renderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer); // now actually attach it
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		checkFramebuffer();
	
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		

	}

	void Framebuffer::bindFramebuffer() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glViewport(0, 0, framebufferSize.x, framebufferSize.y);

		
	}

	void Framebuffer::unbindFramebuffer() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t Framebuffer::getColorAttachment() const
	{
		return colorAttachment;
	}

	uint32_t Framebuffer::getDepthAttachment() const
	{
		return 0;
	}

	void Framebuffer::resize(uint32_t width, uint32_t height)
	{
		framebufferSize.x = width;
		framebufferSize.y = height;
		create(width, height);
	}

	void Framebuffer::Framebuffer::deleteFramebuffer()
	{
		glDeleteFramebuffers(1, &framebuffer);
	}

	bool Framebuffer::checkFramebuffer()
	{
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			return false;
		}
		return true;
	}

	int Framebuffer::readPixel(uint32_t index)
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
		int pixel;
		glReadPixels(screenPickerX, screenPickerY, 1, 1, GL_RED_INTEGER, GL_INT, &pixel);
		return pixel;
	}

	void Framebuffer::setScreenPickerPos(int32_t x, int32_t y)
	{
		screenPickerX = x;
		screenPickerY = y;
	}

	void Framebuffer::clearAttachmentForPicker()
	{
		int value = -1;
		glClearTexImage(redAttachment, 0, GL_RED_INTEGER, GL_INT, &value);
	}




}
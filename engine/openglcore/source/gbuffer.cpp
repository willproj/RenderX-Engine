#include "include/gbuffer.h"

namespace engine::openglcore
{
	GBuffer::GBuffer()
		:gPositionAttachment(0), gNormalAttachment(0), gAlbedoSpecAttachment(0)
	{

	}

	GBuffer::~GBuffer()
	{

	}

	void GBuffer::create(uint32_t width, uint32_t height)
	{
		if (framebuffer)
		{
			glDeleteFramebuffers(1, &framebuffer);
			glDeleteRenderbuffers(1, &renderBuffer);
			glDeleteTextures(1, &gPositionAttachment);
			glDeleteTextures(1, &gNormalAttachment);
			glDeleteTextures(1, &gAlbedoSpecAttachment);
		}

		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        // position color buffer
        glGenTextures(1, &gPositionAttachment);
        glBindTexture(GL_TEXTURE_2D, gPositionAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPositionAttachment, 0);
        // normal color buffer
        glGenTextures(1, &gNormalAttachment);
        glBindTexture(GL_TEXTURE_2D, gNormalAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormalAttachment, 0);
        // color + specular color buffer
        glGenTextures(1, &gAlbedoSpecAttachment);
        glBindTexture(GL_TEXTURE_2D, gAlbedoSpecAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpecAttachment, 0);
        // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
        unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
        glDrawBuffers(3, attachments);
        // create and attach depth buffer (renderbuffer)
        glGenRenderbuffers(1, &renderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
        // finally check if framebuffer is complete
        checkFramebuffer();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

    uint32_t GBuffer::getPositionAttachment() const
    {
        return gPositionAttachment;
    }

    uint32_t GBuffer::getNormalAttachment() const
    {
        return gNormalAttachment;
    }

    uint32_t GBuffer::getAlbedoSpecAttachment() const
    {
        return gAlbedoSpecAttachment;
    }

    void GBuffer::useGBuffer(uint32_t width, uint32_t height)
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
        // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
        // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
        // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
        glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}
#pragma once
#include "common.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>


namespace engine::openglcore
{
	class Framebuffer
	{
	public:
		Framebuffer();
		~Framebuffer();

		virtual void create(uint32_t width, uint32_t height);

		void bindFramebuffer() const;
		void unbindFramebuffer() const;

		uint32_t getColorAttachment() const;
		uint32_t getDepthAttachment() const;

		uint32_t getRedAttachment() { return redAttachment; }

		void resize(uint32_t width, uint32_t height);

		void deleteFramebuffer();
		int readPixel(uint32_t index);

		void setScreenPickerPos(int32_t x, int32_t y);
		void clearAttachmentForPicker();

	protected:

		bool checkFramebuffer();

		uint32_t framebuffer;
		uint32_t renderBuffer;
		glm::vec2 framebufferSize;

		int32_t screenPickerX;
		int32_t screenPickerY;

	private:
		uint32_t colorAttachment;
		uint32_t redAttachment;
		//uint32_t depthAttachment;

		std::vector<uint32_t> textureAttachments;

	};
}
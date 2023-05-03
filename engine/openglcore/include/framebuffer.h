#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>


namespace engine::openglcore
{
	class Framebuffer
	{
	public:
		Framebuffer();
		~Framebuffer();


		void bindFramebuffer() const;
		void unbindFramebuffer() const;

	protected:
		uint32_t buffer;
	private:

	};
}
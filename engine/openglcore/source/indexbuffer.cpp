#include "include/indexbuffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine::openglcore
{
	IndexBuffer::IndexBuffer()
		:EBO(0)
	{
		glGenBuffers(1, &EBO);
	}

	IndexBuffer::~IndexBuffer()
	{
		
	}

	void IndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}

	void IndexBuffer::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::addBufferData(int32_t size, const void* vertex)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertex, GL_STATIC_DRAW);
	}

	void IndexBuffer::draw(uint32_t size)
	{
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	}
}
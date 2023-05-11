#include "include/vertexbuffer.h"


namespace engine::openglcore
{
	VertexBuffer::VertexBuffer()
		:VBO(0)
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}

	VertexBuffer::~VertexBuffer()
	{

	}

	void VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::addBufferData(int64_t size, const void* vertex)
	{
		glBufferData(GL_ARRAY_BUFFER, size, vertex, GL_STATIC_DRAW);
	}


}
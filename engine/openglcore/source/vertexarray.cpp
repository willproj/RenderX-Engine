#include "include/vertexarray.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine::openglcore
{
	VertexArray::VertexArray()
		:VAO(0)
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
	}

	VertexArray::~VertexArray()
	{

	}

	void VertexArray::bind()
	{
		glBindVertexArray(VAO);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

}
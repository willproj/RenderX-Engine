#pragma once
#include <common.h>

namespace engine::openglcore
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void bind();
		void unbind();

	private:
		uint32_t VAO;
	};
}
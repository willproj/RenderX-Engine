#pragma once
#include <common.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine::openglcore
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		void bind();
		void unbind();

		void addBufferData(int64_t size, const void* vertex);

		template<typename Type, int32_t index, int32_t size>
		struct Func
		{
			static void bufferLayout(int32_t stride, int64_t offset)
			{
			}
		};
		

		template<int32_t index, int32_t size>
		struct Func<float, index, size>
		{
			static void bufferLayout(int32_t stride, int64_t offset)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
			}
		};

		template<typename Type, int32_t index, int32_t size>
		void addBufferLayout(int32_t stride, int64_t offset)
		{
			Func<Type, index, size>::bufferLayout(stride, offset);
		}

	private:
		uint32_t VBO;
	};
}
#pragma once
#include <common.h>

namespace engine::openglcore
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		void bind();
		void unbind();

		void addBufferData(int32_t size, const void* vertex);

		void draw(uint32_t size);
		
	private:
		uint32_t EBO;
	};
}
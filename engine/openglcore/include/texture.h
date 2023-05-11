#pragma once
#include <common.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine::openglcore
{
	enum class TextureType
	{
		DIFFUSE_TEXTURE,
		SPECULAR_TEXTURE,
		NORMAL_TEXTURE,
		HEIGHT_TEXTURE,
		AO_TEXTURE
	};

	struct Texture
	{
		uint32_t texture;
		TextureType type;
	};

	class TextureUtils
	{
	public:
		static uint32_t loadTexture(const std::string& path);
		static void useTexture(uint32_t index, uint32_t texture);
	private:
	};
}
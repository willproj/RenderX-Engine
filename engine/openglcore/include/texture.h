#pragma once
#include <common.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine::openglcore
{
	enum TextureType
	{
		DIFFUSE_TEXTURE,
		SPECULAR_TEXTURE,
		NORMAL_TEXTURE,
		HEIGHT_TEXTURE
	};

	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();
		void loadTexture(const std::string& path);

		void useTexture(uint32_t index) const;

	private:
		uint32_t texture;
		TextureType type;

	};
}
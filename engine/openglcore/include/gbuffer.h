#pragma once
#include "framebuffer.h"

namespace engine::openglcore
{
	class GBuffer :public Framebuffer
	{
	public:
		GBuffer();
		~GBuffer();

		void create(uint32_t width, uint32_t height) override;

		uint32_t getPositionAttachment() const;
		uint32_t getNormalAttachment() const;
		uint32_t getAlbedoSpecAttachment() const;

		void useGBuffer(uint32_t width, uint32_t height);

	private:
		uint32_t gPositionAttachment;
		uint32_t gNormalAttachment;
		uint32_t gAlbedoSpecAttachment;
		
	};
}
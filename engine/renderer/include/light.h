#pragma once
#include <glm/glm.hpp>

namespace engine::renderer
{
	class Light
	{
	public:
		Light();
		Light(float intensity, float radius, const glm::vec3& color);
		Light(const Light&) = default;
		Light& operator=(const Light&) = default;
		~Light();

		float getRadius()const;
		float getIntensity()const;
		const glm::vec3& getColor()const;

		void setIntensity(float intensity);
		void setRadius(float radius);
		void setColor(const glm::vec3& color);

	private:
		glm::vec3 color;
		float intensity;
		float radius;
		
	};
}
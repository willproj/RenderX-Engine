#pragma once
#include <glm/glm.hpp>

namespace engine::renderer
{
	class Camera
	{
	public:
		Camera();
		Camera(const glm::mat4& projection);
		
		virtual ~Camera();
		
		const glm::mat4& getProjection() const;

	protected:
		glm::mat4 projection;
	};
}
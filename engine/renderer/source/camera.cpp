#include "include/camera.h"

namespace engine::renderer
{
	Camera::Camera()
		:projection(glm::mat4(1.0f))
	{

	}

	Camera::Camera(const glm::mat4& projection)
		:projection(projection)
	{

	}

	Camera::~Camera()
	{

	}

	const glm::mat4& Camera::getProjection() const
	{
		return projection;
	}
}
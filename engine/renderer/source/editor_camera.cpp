#include "include/editor_camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "input/input_manager.h"

namespace engine::renderer
{
	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
		:FOV(fov), aspectRatio(aspectRatio), nearClip(nearClip), farClip(farClip), Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
	{
		updateView();
	}

	void EditorCamera::update()
	{
		auto s_keyboard = input::Keyboard::getInstance();
		if (s_keyboard->getKey(input::KeyCode::RX_KEY_LEFT_CONTROL))
		{

			if (isOnFocus)
			{
				auto s_mouse = input::Mouse::getInstance();
				auto pos = s_mouse->getMouseCurrentPosition();

				auto offsetMouse = s_mouse->getMousePositionOffset() * 0.003f;

				if (input::Mouse::getInstance()->isLeftButtonPressed())
				{
					mouseRotate(offsetMouse);

				}
				else if (input::Mouse::getInstance()->isRightButtonPressed())
				{
					mousePan(offsetMouse);
				}

				auto offsetScroll = input::Mouse::getInstance()->getMouseScrollOffset();
				mouseZoom(offsetScroll.y);

				input::Mouse::getInstance()->updateMouse();
			}
			updateView();

		}

	}

	void EditorCamera::setCameraAttributes(float fov, float aspectRatio, float nearClip, float farClip)
	{
		FOV = fov;
		this->aspectRatio = aspectRatio;
		this->nearClip = nearClip;
		this->farClip = farClip;

		projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
		updateView();
	}

	glm::vec3 EditorCamera::getUpDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 EditorCamera::getRightDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 EditorCamera::getForwardDirection() const
	{
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::quat EditorCamera::getOrientation() const
	{
		return glm::quat(glm::vec3(-pitch, -yaw, 0.0f));
	}

	void EditorCamera::updateProjection()
	{
		aspectRatio = viewportWidth / viewportHeight;
		projection = glm::perspective(glm::radians(FOV), aspectRatio, nearClip, farClip);
	}
	void EditorCamera::updateView()
	{
		// yaw = pitch = 0.0f; // Lock the camera's rotation
		position = calculatePosition();


		glm::quat orientation = getOrientation();
		viewMatrix = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(orientation);
		viewMatrix = glm::inverse(viewMatrix);
	}
	
	void EditorCamera::mousePan(const glm::vec2& delta)
	{
		auto [xSpeed, ySpeed] = panSpeed();
		focalPoint += -getRightDirection() * delta.x * xSpeed * distance;
		focalPoint += getUpDirection() * delta.y * ySpeed * distance;
	}

	void EditorCamera::mouseRotate(const glm::vec2& delta)
	{
		float yawSign = getUpDirection().y < 0 ? -1.0f : 1.0f;
		yaw += yawSign * delta.x * rotationSpeed();
		pitch += delta.y * rotationSpeed();
	}

	void EditorCamera::mouseZoom(float delta)
	{
		distance -= delta * zoomSpeed();
		if (distance < 1.0f)
		{
			focalPoint += getForwardDirection();
			distance = 1.0f;
		}
	}

	glm::vec3 EditorCamera::calculatePosition() const
	{
		return focalPoint - getForwardDirection() * distance;
	}

	std::pair<float, float> EditorCamera::panSpeed() const
	{
		float x = std::min(viewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(viewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float EditorCamera::rotationSpeed() const
	{
		return 0.8f;
	}

	float EditorCamera::zoomSpeed() const
	{
		float distance = this->distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f); // max speed = 100
		return speed;
	}

	void EditorCamera::setIsOnFocus(bool focus)
	{
		isOnFocus = focus;
	}

}
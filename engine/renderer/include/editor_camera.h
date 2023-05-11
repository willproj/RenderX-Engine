#pragma once
#include <common.h>
#include "camera.h"

namespace engine::renderer
{
	class EditorCamera :public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void update();

		void setCameraAttributes(float fov, float aspectRatio, float nearClip, float farClip);

		inline float getDistance() const { return distance; }
		inline void setDistance(float distance) { distance = distance; }

		inline void setViewportSize(float width, float height) { viewportWidth = width; viewportHeight = height; updateProjection(); }

		const glm::mat4& getViewMatrix() const { return viewMatrix; }
		glm::mat4 getViewProjection() const { return projection * viewMatrix; }

		glm::vec3 getUpDirection() const;
		glm::vec3 getRightDirection() const;
		glm::vec3 getForwardDirection() const;
		const glm::vec3& getPosition() const { return position; }
		glm::quat getOrientation() const;

		float getPitch() const { return pitch; }
		float getYaw() const { return yaw; }
		void setIsOnFocus(bool focus);

	private:
		void updateProjection();
		void updateView();

		void mousePan(const glm::vec2& delta);
		void mouseRotate(const glm::vec2& delta);
		void mouseZoom(float delta);

		glm::vec3 calculatePosition() const;

		std::pair<float, float> panSpeed() const;
		float rotationSpeed() const;
		float zoomSpeed() const;
	private:
		float FOV = 45.0f, aspectRatio = 1.778f,nearClip = 0.1f, farClip = 1000.0f;

		glm::mat4 viewMatrix;
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 focalPoint = { 0.0f, 0.0f, 0.0f };

		glm::vec2 initialMousePosition = { 0.0f, 0.0f };

		float distance = 10.0f;
		float pitch = 0.0f, yaw = 0.0f;

		float viewportWidth = 1280, viewportHeight = 720;

		bool isOnFocus = false;
	};
}
#include "include/viewport_gui.h"
#include "ImGuizmo.h"
#include "scene/component.h"
#include "input/keyboard.h"
#include "input/mouse.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

namespace engine::ui
{
	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale)
	{
		// From glm::decompose in matrix_decompose.inl

		using namespace glm;
		using T = float;

		mat4 LocalMatrix(transform);

		// Normalize the matrix.
		if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
			return false;

		// First, isolate perspective.  This is the messiest.
		if (
			epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
			epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
			epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
		{
			// Clear the perspective partition
			LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
			LocalMatrix[3][3] = static_cast<T>(1);
		}

		// Next take care of translation (easy).
		translation = vec3(LocalMatrix[3]);
		LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

		vec3 Row[3], Pdum3;

		// Now get scale and shear.
		for (length_t i = 0; i < 3; ++i)
			for (length_t j = 0; j < 3; ++j)
				Row[i][j] = LocalMatrix[i][j];

		// Compute X scale factor and normalize first row.
		scale.x = length(Row[0]);
		Row[0] = detail::scale(Row[0], static_cast<T>(1));
		scale.y = length(Row[1]);
		Row[1] = detail::scale(Row[1], static_cast<T>(1));
		scale.z = length(Row[2]);
		Row[2] = detail::scale(Row[2], static_cast<T>(1));

		// At this point, the matrix (in rows[]) is orthonormal.
		// Check for a coordinate system flip.  If the determinant
		// is -1, then negate the matrix and the scaling factors.
#if 0
		Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
		if (dot(Row[0], Pdum3) < 0)
		{
			for (length_t i = 0; i < 3; i++)
			{
				scale[i] *= static_cast<T>(-1);
				Row[i] *= static_cast<T>(-1);
			}
		}
#endif

		rotation.y = asin(-Row[0][2]);
		if (cos(rotation.y) != 0) {
			rotation.x = atan2(Row[1][2], Row[2][2]);
			rotation.z = atan2(Row[0][1], Row[0][0]);
		}
		else {
			rotation.x = atan2(-Row[2][0], Row[1][1]);
			rotation.z = 0;
		}


		return true;
	}

	ViewportGui::ViewportGui()
	{
		uiName = "viewport";
		isOpen = true;
	}

	ViewportGui::~ViewportGui()
	{

	}

	void ViewportGui::onEvent(const std::function<void()>& func)
	{
		func();
	}

	void ViewportGui::render()
	{
		if (isOpen)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin(uiName.c_str(), &isOpen);


			auto viewportCurrSize = ImGui::GetContentRegionAvail();
			
			if (viewportSize != *(glm::vec2*)&viewportCurrSize)
			{
				s_renderData->framebuffer.resize(viewportCurrSize.x, viewportCurrSize.y);
				viewportSize = { viewportCurrSize.x, viewportCurrSize.y };
				s_renderData->editorCameraOnUse->setViewportSize(viewportSize.x, viewportSize.y);
			}
			auto pos = ImGui::GetWindowPos();
			s_renderData->editorCameraOnUse->setIsOnFocus(ImGui::IsWindowFocused());
			s_renderData->isViewportOnFocus = ImGui::IsWindowFocused();

			auto mousePos = ImGui::GetMousePos();
			int rangex = mousePos.x - pos.x;
			int rangey = mousePos.y - pos.y;

			if (rangex >= 0 && rangey >= 0 && rangex < viewportSize.x && rangey < viewportSize.y)
			{
				auto [x, y] = ImGui::GetMousePos();
				x -= viewportBounds[0].x;
				y -= viewportBounds[0].y;
				y = viewportSize.y - y;
				s_renderData->framebuffer.setScreenPickerPos(x, y);

				s_renderData->framebuffer.bindFramebuffer();
				int pixelID = s_renderData->framebuffer.readPixel(1);

				if (pixelID >= 0 && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !input::Keyboard::getInstance()->getKey(input::RX_KEY_LEFT_CONTROL))
				{
					s_renderData->selectedEntity = { (entt::entity)pixelID,s_renderData->scene };
				}
				else if (pixelID < 0 && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					s_renderData->selectedEntity = {};
				}
				s_renderData->framebuffer.unbindFramebuffer();
			}

			//render screen to viewport
			auto tex = s_renderData->framebuffer.getColorAttachment();
			ImGui::Image((ImTextureID*)tex, { viewportSize.x, viewportSize.y } , ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
			
			//imguizmo
			renderImGuizmo();

			ImGui::End();
			ImGui::PopStyleVar();
		}

	}

	void ViewportGui::renderImGuizmo()
	{
		auto selectedEntity = s_renderData->selectedEntity;

		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		viewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		viewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		guizmoType = ImGuizmo::OPERATION::TRANSLATE;

		if (!selectedEntity.isEmptyEntity() && guizmoType != -1
			&& selectedEntity.hasComponent<scene::TransformComponent>()
			&& !input::Keyboard::getInstance()->getKey(input::RX_KEY_LEFT_CONTROL))
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			ImGuizmo::SetRect(viewportBounds[0].x, viewportBounds[0].y, viewportBounds[1].x - viewportBounds[0].x, viewportBounds[1].y - viewportBounds[0].y);

			// Editor camera
			const glm::mat4& cameraProjection = s_renderData->primaryEditorCamera.getProjection();
			glm::mat4 cameraView = s_renderData->primaryEditorCamera.getViewMatrix();
			// Entity transform
			auto& tc = selectedEntity.getComponent<scene::TransformComponent>();
			glm::mat4 transform = tc.getTransform();

			auto keyboard = input::Keyboard::getInstance();
			if (keyboard->getKey(input::RX_KEY_1))
			{
				guizmoType = ImGuizmo::OPERATION::TRANSLATE;
			}
			else if (keyboard->getKey(input::RX_KEY_2))
			{
				guizmoType = ImGuizmo::OPERATION::ROTATE;
			}
			else if (keyboard->getKey(input::RX_KEY_3))
			{
				guizmoType = ImGuizmo::OPERATION::SCALE;
			}
			// Snapping
			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)guizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform));

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translation, rotation, scale;
				DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.rotation;
				tc.translation = translation;
				tc.rotation += deltaRotation;
				tc.scale = scale;
			}
			
		}
	}

	
}
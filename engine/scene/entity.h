#pragma once
#include <entt/entt.hpp>
#include "scene.h"

namespace engine::scene
{
	class Entity
	{
	public:
		Entity();
		Entity(entt::entity entity, Scene* scene);
		~Entity();

		Entity(const Entity&) = default;
		Entity& operator=(const Entity&) = default;

		template<typename Component, typename ...Args>
		void addComponent(Args... args)
		{
			if (hasComponent<Component>())
			{
				return;
			}
			scene->enttRegister.emplace<Component>(entity, std::forward<Args>(args)...);
		}

		template<typename Component>
		Component& getComponent()
		{
			return scene->enttRegister.get<Component>(entity);
		}

		template<typename Component>
		bool hasComponent()
		{
			return scene->enttRegister.any_of<Component>(entity);
		}

		template<typename Component>
		void removeComponent()
		{
			if (!hasComponent<Component>())
			{
				std::cout << "entity doesn't have the component" << std::endl;
				return;
			}
			scene->enttRegister.remove<Component>(entity);
		}

		int32_t operator()();

		bool operator==(const Entity& other);
		bool isEmptyEntity();
		operator entt::entity() const;

	private:
		entt::entity entity;
		Scene* scene;
	};
}
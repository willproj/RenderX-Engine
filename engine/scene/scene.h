#pragma once
#include "common.h"
#include <entt/entt.hpp>
#include "utils/uuid.h"

namespace engine::scene
{
	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();
	
		Entity createEntity(const std::string& entityName = "Entity");
		void removeEntity(Entity entity);


		entt::registry& getRegisterRef();

	private:
		entt::registry enttRegister;
		utils::UUIDGenerator uuidGenerator;
		friend class Entity;
	};
}

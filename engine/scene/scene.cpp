#include "scene.h"
#include "entity.h"
#include "component.h"

namespace engine::scene
{
	Scene::Scene()
	{
		
	}

	Entity Scene::createEntity(const std::string& entityName)
	{
		Entity entity(enttRegister.create(),this);

		uint32_t uuid = uuidGenerator.generate();
		entity.addComponent<UUIDComponent>();
		auto& uuidComp = entity.getComponent<UUIDComponent>();
		uuidComp.uuid = uuid;

		entity.addComponent<LabelComponent>();
		auto& label = entity.getComponent<LabelComponent>();
		label.label = entityName;

		return entity;
	}

	void Scene::removeEntity(Entity entity)
	{
		enttRegister.destroy(entity);
	}

	entt::registry& Scene::getRegisterRef()
	{
		return enttRegister;
	}
}
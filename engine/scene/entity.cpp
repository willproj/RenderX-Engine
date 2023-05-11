#include "entity.h"

namespace engine::scene
{
	Entity::Entity()
		:entity(entt::null), scene(nullptr)
	{

	}

	Entity::Entity(entt::entity entity, Scene* scene)
		:entity(entity),scene(scene)
	{

	}

	

	Entity::~Entity()
	{
	
	}

	bool Entity::operator==(const Entity& other)
	{
		return other.entity == entity;
	}

	int32_t Entity::operator()()
	{
		return (uint32_t)entity;
	}

	Entity::operator entt::entity() const
	{
		return entity;
	}

	bool Entity::isEmptyEntity()
	{
		return entity == entt::null;
	}


}
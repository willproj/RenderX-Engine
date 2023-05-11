#include "serializer.h"
#include "scene/entity.h"
#include "scene/component.h"
#include <yaml-cpp/yaml.h>

namespace YAML {

	template<>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};


}

namespace engine::utils
{
	


	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	Serializer::Serializer(scene::Scene* scene)
		:scenePtr(scene)
	{

	}

	static void SerializeEntity(YAML::Emitter& out, scene::Entity entity)
	{
		out << YAML::BeginMap;
		
		if (entity.hasComponent<scene::UUIDComponent>())
		{
			out << YAML::Key << "UUID Component";
			out << YAML::BeginMap;

			auto& uuidComp = entity.getComponent<scene::UUIDComponent>();
			out << YAML::Key << "Entity UUID" << YAML::Value << uuidComp.uuid;
			out << YAML::EndMap;
		}

		if (entity.hasComponent<scene::LabelComponent>())
		{
			out << YAML::Key << "Label Component";
			out << YAML::BeginMap;

			auto& labelComp = entity.getComponent<scene::LabelComponent>();
			out << YAML::Key << "Label" << YAML::Value << labelComp.label;

			out << YAML::EndMap;
		}

		if (entity.hasComponent<scene::TransformComponent>())
		{
			out << YAML::Key << "Transform Component";
			out << YAML::BeginMap;

			auto& transformComp = entity.getComponent<scene::TransformComponent>();
			out << YAML::Key << "Translation" << YAML::Value << transformComp.translation;
			out << YAML::Key << "Rotation" << YAML::Value << transformComp.rotation;
			out << YAML::Key << "Scale" << YAML::Value << transformComp.scale;
			
			out << YAML::EndMap;
		}

		if (entity.hasComponent<scene::ModelComponent>())
		{
			out << YAML::Key << "Model Component";
			out << YAML::BeginMap;
			auto& modelComp = entity.getComponent<scene::ModelComponent>();
			out << YAML::Key << "Mesh Path" << YAML::Value << modelComp.model.getPath();
			
			out << YAML::EndMap;
		}

		if (entity.hasComponent<scene::MaterialComponent>())
		{
			out << YAML::Key << "Material Component";
			out << YAML::BeginMap;
			auto& meterialComp = entity.getComponent<scene::MaterialComponent>();
			out << YAML::Key << "Color" << YAML::Value << meterialComp.albedo;
			out << YAML::Key << "Roughness" << YAML::Value << meterialComp.roughness;
			out << YAML::Key << "Metallic" << YAML::Value << meterialComp.metallic;

			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	void Serializer::serialize(const std::string& path)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "unknow";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		scenePtr->getRegisterRef().each([&](auto entityID) 
		{
			scene::Entity entity = { entityID, scenePtr };
			if (entity.isEmptyEntity())
			{
				return;
			}
			SerializeEntity(out, entity);
		});

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fileOut(path);
		fileOut << out.c_str();

	}

	bool Serializer::deSerialize(const std::string& path)
	{
		YAML::Node data;
		try
		{
			data = YAML::LoadFile(path);
		}
		catch (YAML::ParserException e)
		{
			std::cout << "YAML failed to load .rx file" << std::endl;
			return false;
		}

		if (!data["Scene"])
		{
			return false;
		}

		auto entities = data["Entities"];

		if (entities)
		{
			for (auto entity : entities)
			{
				std::string label;
				auto labelComp = entity["Label Component"];
				if (labelComp)
				{
					label = labelComp["Label"].as<std::string>();
				}

				scene::Entity deserializedEntity = scenePtr->createEntity(label);

				auto uuidComp = entity["UUID Component"];
				if (uuidComp)
				{
					deserializedEntity.addComponent<scene::UUIDComponent>();
					auto& uuid = deserializedEntity.getComponent<scene::UUIDComponent>();
					uuid.uuid = uuidComp["Entity UUID"].as<uint64_t>();
				}

				auto transformComp = entity["Transform Component"];
				if (transformComp)
				{
					// Entities always have transforms
					deserializedEntity.addComponent<scene::TransformComponent>();
					auto& tansform = deserializedEntity.getComponent<scene::TransformComponent>();
					tansform.translation = transformComp["Translation"].as<glm::vec3>();
					tansform.rotation = transformComp["Rotation"].as<glm::vec3>();
					tansform.scale = transformComp["Scale"].as<glm::vec3>();
				}

				auto modelComp = entity["Model Component"];
				if (modelComp)
				{
					deserializedEntity.addComponent<scene::ModelComponent>();
					auto& model = deserializedEntity.getComponent<scene::ModelComponent>();
					std::string path = modelComp["Mesh Path"].as<std::string>();
					model.model.loadModel(path);

				}

				auto materialComp = entity["Material Component"];
				if (materialComp)
				{
					deserializedEntity.addComponent<scene::MaterialComponent>();
					auto& material = deserializedEntity.getComponent<scene::MaterialComponent>();
					glm::vec3 color = materialComp["Color"].as<glm::vec3>();
					material.albedo = color;
					float roughness = materialComp["Roughness"].as<float>();
					material.roughness = roughness;
					float metallic = materialComp["Metallic"].as<float>();
					material.metallic = metallic;
				}
			}
		}

		
		return true;
	}
}
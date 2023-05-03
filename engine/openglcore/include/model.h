#pragma once
#include "mesh.h"

namespace engine::openglcore
{
	class Model
	{
	public:
		Model();
	protected:
		std::vector<std::shared_ptr<Mesh>> meshes;
	};
}
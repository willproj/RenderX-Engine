#include "include/mesh.h"

namespace engine::openglcore
{
	Mesh::Mesh()
	{
		
	}

	Mesh::~Mesh()
	{

	}

	void Mesh::setup(const std::function<void()>& layoutFunc)
	{
		layoutFunc();
	}

}
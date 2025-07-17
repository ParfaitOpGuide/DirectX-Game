#include "MeshManager.h"
#include "Texture.h"
#include <iostream>
#include "Mesh.h"

MeshManager::MeshManager() : ResourceManager()
{
}

MeshManager::~MeshManager()
{
}

MeshPtr MeshManager::createMeshFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<Mesh>(createResourceFromFile(file_path));
}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* file_path)
{

	Mesh* m = nullptr;
	try
	{
		m = new Mesh(file_path);
	}
	catch (...)
	{

	}

	return m;
}

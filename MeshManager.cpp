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

MeshPtr MeshManager::createMeshFromFile(const wchar_t* file_path, bool hastc, bool hasn)
{
	return std::static_pointer_cast<Mesh>(createResourceFromFile(file_path, hastc, hasn));
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

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* file_path, bool hastc, bool hasn)
{

	Mesh* m = nullptr;
	try
	{
		m = new Mesh(file_path, hastc, hasn);
	}
	catch (...)
	{

	}

	return m;
}

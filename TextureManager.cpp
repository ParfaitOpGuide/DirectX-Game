#include "TextureManager.h"
#include "Texture.h"
#include <iostream>

TextureManager::TextureManager() : ResourceManager()
{
}

TextureManager::~TextureManager()
{
}

TexturePtr TextureManager::createTextureFromFile(const wchar_t* file_path)
{
	//std::cout << "\n" << file_path << "\n";
	return std::static_pointer_cast<Texture>(createResourceFromFile(file_path));
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* file_path)
{

	Texture* tex = nullptr;
	try
	{
		tex = new Texture(file_path);
	}
	catch (...)
	{

	}

	return tex;
}

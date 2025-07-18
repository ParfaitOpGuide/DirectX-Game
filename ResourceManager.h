#pragma once
#include <unordered_map>
#include <string>
#include "Prerequisites.h"

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	ResourcePtr createResourceFromFile(const wchar_t* file_path);
	ResourcePtr createResourceFromFile(const wchar_t* file_path, bool hastc, bool hasn);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) = 0;
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path, bool hastc, bool hasn) = 0;

private:
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;
};


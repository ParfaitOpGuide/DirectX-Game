#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "Prerequisites.h"
 
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	RenderSystem* getRenderSystem();

	//singleton
	static GraphicsEngine* get();
	static void create();
	static void release();

private:


private:
	RenderSystem* m_render_system = nullptr;
	static GraphicsEngine* m_engine;
};


#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "Prerequisites.h"
 
class GraphicsEngine
{
public:
	bool init();
	bool release();

	RenderSystem* getRenderSystem();

	//singleton
	static GraphicsEngine* get();

private:


private:
	RenderSystem* m_render_system = nullptr;
};


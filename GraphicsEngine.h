#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "Prerequisites.h"
#include "TextureManager.h"
 
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();

	//singleton
	static GraphicsEngine* get();
	static void create();
	static void release();

private:


private:
	RenderSystem* m_render_system = nullptr;
	TextureManager* m_tex_manager = nullptr;
	static GraphicsEngine* m_engine;
};


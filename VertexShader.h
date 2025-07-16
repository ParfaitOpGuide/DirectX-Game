#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include "Prerequisites.h"


class VertexShader
{
public:
	VertexShader(RenderSystem* system, const void* shader_byte_code, size_t byte_code_size);
	~VertexShader();

private:

	ID3D11VertexShader* m_vs;
	RenderSystem* m_system = nullptr;

	friend class GraphicsEngine;
	friend class DeviceContext;
	friend class RenderSystem;
};


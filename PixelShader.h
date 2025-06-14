#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

class GraphicsEngine;
class DeviceContext;


class PixelShader
{
public:
	void release();

private:
	bool init(const void* shader_byte_code, size_t byte_code_size);

	ID3D11PixelShader* m_ps;

	friend class GraphicsEngine;
	friend class DeviceContext;
};


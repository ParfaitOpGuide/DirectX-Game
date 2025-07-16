#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include "Prerequisites.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);
	~DeviceContext();
	bool clearRenderTargetColor(SwapChainPtr swap_chain, float red, float green, float blue, float alpha);
	bool setVertexBuffer(VertexBufferPtr vertex_buffer);
	bool setIndexBuffer(IndexBufferPtr index_buffer);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location, int viewNum);
	void drawIndexedTriangleStrip(UINT index_count, UINT start_vertex_index, UINT start_index_location, int viewNum);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void setViewportSize(UINT width, UINT height);
	void setVertexShader(VertexShaderPtr vertex_shader);
	void setPixelShader(PixelShaderPtr pixel_shader);

	void setConstantBuffer(VertexShaderPtr vertex_shader, ConstantBufferPtr buffer);
	void setConstantBuffer(PixelShaderPtr pixel_shader, ConstantBufferPtr buffer);

	

private:
	ID3D11DeviceContext* m_device_context;
	RenderSystem* m_system = nullptr;
	D3D11_VIEWPORT vps[3];
	friend class ConstantBuffer;
};


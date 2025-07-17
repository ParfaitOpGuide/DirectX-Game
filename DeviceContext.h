#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include "Prerequisites.h"


class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);
	~DeviceContext();
	bool clearRenderTargetColor(const SwapChainPtr& swap_chain, float red, float green, float blue, float alpha);
	bool setVertexBuffer(const VertexBufferPtr& vertex_buffer);
	bool setIndexBuffer(const IndexBufferPtr& index_buffer);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location, int viewNum);
	void drawIndexedTriangleStrip(UINT index_count, UINT start_vertex_index, UINT start_index_location, int viewNum);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void setViewportSize(UINT width, UINT height);
	void setVertexShader(const VertexShaderPtr& vertex_shader);
	void setPixelShader(const PixelShaderPtr& pixel_shader);

	void setTexture(const VertexShaderPtr& vertex_shader, const TexturePtr& texture);
	void setTexture(const PixelShaderPtr& pixel_shader, const TexturePtr& texture);

	void setConstantBuffer(const VertexShaderPtr& vertex_shader, const ConstantBufferPtr& buffer);
	void setConstantBuffer(const PixelShaderPtr& pixel_shader, const ConstantBufferPtr& buffer);

private:
	ID3D11DeviceContext* m_device_context;
	RenderSystem* m_system = nullptr;
	D3D11_VIEWPORT vps[3];
	friend class ConstantBuffer;
};


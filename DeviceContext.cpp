#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "RenderSystem.h"
#include "Texture.h"
#include <exception>

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system) : m_device_context(device_context), m_system(system)
{

}

DeviceContext::~DeviceContext()
{
	m_device_context->Release();
}

bool DeviceContext::clearRenderTargetColor(const SwapChainPtr& swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red,green,blue,alpha };

	ID3D11RenderTargetView* renderView = swap_chain->getRenderTargetView();
	ID3D11DepthStencilView* depthView = swap_chain->getDepthStencilView();

	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);
	m_device_context->ClearDepthStencilView(swap_chain->m_dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	m_device_context->OMSetRenderTargets(1, &swap_chain->m_rtv, swap_chain->m_dsv);

	return false;
}

bool DeviceContext::setVertexBuffer(const VertexBufferPtr& vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex;
	UINT offset = 0;
	m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);

	m_device_context->IASetInputLayout(vertex_buffer->m_layout);
	return true;
}

bool DeviceContext::setIndexBuffer(const IndexBufferPtr& index_buffer)
{
	m_device_context->IASetIndexBuffer(index_buffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
	return true;
}

void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location, int viewNum)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->RSSetViewports(1, &vps[viewNum]);
	m_device_context->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::drawIndexedTriangleStrip(UINT index_count, UINT start_vertex_index, UINT start_index_location, int viewNum)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_device_context->RSSetViewports(1, &vps[viewNum]);
	m_device_context->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_device_context->Draw(vertex_count, start_vertex_index);
}


void DeviceContext::setViewportSize(UINT width, UINT height)
{

	vps[0].Width = width;
	vps[0].Height = height;
	vps[0].MinDepth = 0.0f;
	vps[0].MaxDepth = 1.0f;
	vps[0].TopLeftX = 0;
	vps[0].TopLeftY = 0.0f;
/*
	vps[1].Width = width/2;
	vps[1].Height = height/2;
	vps[1].MinDepth = 0.0f;
	vps[1].MaxDepth = 1.0f;
	vps[1].TopLeftX = width / 2;
	vps[1].TopLeftY = 0.0f;

	vps[2].Width = width;
	vps[2].Height = height/2;
	vps[2].MinDepth = 0.0f;
	vps[2].MaxDepth = 1.0f;
	vps[2].TopLeftX = 0;
	vps[2].TopLeftY = height / 2;

*/
}

void DeviceContext::setVertexShader(const VertexShaderPtr& vertex_shader)
{
	m_device_context->VSSetShader(vertex_shader->m_vs, nullptr, 0);
}
void DeviceContext::setPixelShader(const PixelShaderPtr& pixel_shader)
{
	m_device_context->PSSetShader(pixel_shader->m_ps, nullptr, 0);
}

void DeviceContext::setTexture(const VertexShaderPtr& vertex_shader, const TexturePtr& texture)
{
	m_device_context->VSSetShaderResources(0, 1, &texture->m_shader_res_view);
}

void DeviceContext::setTexture(const PixelShaderPtr& pixel_shader, const TexturePtr& texture)
{
	m_device_context->PSSetShaderResources(0, 1, &texture->m_shader_res_view);
}

void DeviceContext::setConstantBuffer(const VertexShaderPtr& vertex_shader, const ConstantBufferPtr& buffer)
{
	m_device_context->VSSetConstantBuffers(0, 1, &buffer->m_buffer);
}

void DeviceContext::setConstantBuffer(const PixelShaderPtr& pixel_shader, const ConstantBufferPtr& buffer)
{
	m_device_context->PSSetConstantBuffers(0, 1, &buffer->m_buffer);
}


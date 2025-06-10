#include "RasterState.h"
#include <iostream>;

RasterState::RasterState()
{
	createRasterStateSolid();
	createRasterStateWireframe();
}

RasterState::~RasterState()
{
}

void RasterState::use()
{
	ID3D11DeviceContext* context = GraphicsEngine::get()->m_imm_context;
	
	if (m_RenderWireframe)
	{
		context->RSSetState(m_RasterStateWireframe.Get());
	}
	else
	{
		context->RSSetState(m_RasterStateSolid.Get());
	}
}

void RasterState::toggleWireframe()
{
	m_RenderWireframe = !m_RenderWireframe;
}

void RasterState::createRasterStateSolid()
{

	D3D11_RASTERIZER_DESC rasterizerState = {};
	rasterizerState.AntialiasedLineEnable = true;
	rasterizerState.CullMode = D3D11_CULL_BACK;
	rasterizerState.FillMode = D3D11_FILL_SOLID;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.FrontCounterClockwise = true;
	rasterizerState.MultisampleEnable = true;
	rasterizerState.DepthBias = 0;
	rasterizerState.DepthBiasClamp = 1.0f;
	rasterizerState.SlopeScaledDepthBias = 1.0f;

	ID3D11Device* device = GraphicsEngine::get()->m_d3d_device;
	HRESULT res;
	res = device->CreateRasterizerState(&rasterizerState, m_RasterStateWireframe.ReleaseAndGetAddressOf());
	if (FAILED(res))
	{
		std::cout << "failed to make raterizerstate\n";
	}
}

void RasterState::createRasterStateWireframe()
{
	D3D11_RASTERIZER_DESC rasterizerState = {};
	rasterizerState.AntialiasedLineEnable = true;
	rasterizerState.CullMode = D3D11_CULL_NONE;
	rasterizerState.FillMode = D3D11_FILL_WIREFRAME;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.FrontCounterClockwise = true;
	rasterizerState.MultisampleEnable = true;
	rasterizerState.DepthBias = 0;
	rasterizerState.DepthBiasClamp = 1.0f;
	rasterizerState.SlopeScaledDepthBias = 1.0f;

	ID3D11Device* device = GraphicsEngine::get()->m_d3d_device;
	HRESULT res;
	res = device->CreateRasterizerState(&rasterizerState, m_RasterStateWireframe.ReleaseAndGetAddressOf());
	if (FAILED(res))
	{
		std::cout << "failed to make raterizerstate\n";
	}

}
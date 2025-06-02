#include "StencilBuffer.h"
#include <iostream>

StencilBuffer::StencilBuffer()
{
}

bool StencilBuffer::load(UINT w, UINT h, SwapChain* swap_chain)
{
	D3D11_TEXTURE2D_DESC depthDesc;
	depthDesc.Width = w;
	depthDesc.Height = h;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;

	HRESULT res = GraphicsEngine::get()->getDevice()->CreateTexture2D(&depthDesc, NULL, &depthStencilBuffer);

	if (FAILED(res))
	{
		std::cout << "fail";
		return false;
	}

	res = GraphicsEngine::get()->getDevice()->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

	if (FAILED(res)) return false;

	GraphicsEngine::get()->getDeviceContext()->OMSetRenderTargets(1, &swap_chain->m_rtv, depthStencilView);

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	res = GraphicsEngine::get()->getDevice()->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
	if (FAILED(res))
	{
		std::cout << "fail";
		return false;
	}

}

void StencilBuffer::clearView()
{
	GraphicsEngine::get()->getDeviceContext()->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void StencilBuffer::setDepthStencilState()
{
	GraphicsEngine::get()->getDeviceContext()->OMSetDepthStencilState(depthStencilState, 0);
}


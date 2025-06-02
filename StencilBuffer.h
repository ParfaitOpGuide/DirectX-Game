#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SwapChain.h"
class SwapChain;

#pragma once
class StencilBuffer
{
public:
	StencilBuffer();

	bool load(UINT w, UINT h, SwapChain* swap_chain);
	void clearView();
	void setDepthStencilState();

private:
	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilState* depthStencilState;

	D3D11_TEXTURE2D_DESC depthDesc;
};


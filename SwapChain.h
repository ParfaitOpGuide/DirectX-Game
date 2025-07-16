#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include "Prerequisites.h"

class SwapChain
{
public:
	SwapChain(RenderSystem* system, HWND hwnd, UINT width, UINT height);
	bool present(bool vsync);

	ID3D11RenderTargetView* getRenderTargetView();
	ID3D11DepthStencilView* getDepthStencilView();

	~SwapChain();

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;
	RenderSystem* m_system = nullptr;

private:
	friend class DeviceContext;
};


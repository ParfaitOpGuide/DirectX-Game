#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

class DeviceContext;

class SwapChain
{
public:
	bool init(HWND hwnd, UINT width, UINT height);

	bool present(bool vsync);

	ID3D11RenderTargetView* getRenderTargetView();
	ID3D11DepthStencilView* getDepthStencilView();

		bool release();

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;

private:
	friend class DeviceContext;
};


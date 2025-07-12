#pragma once
#include <wrl.h>
#include <d3d11.h>
#include "GraphicsEngine.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
using namespace Microsoft::WRL;
class RasterState
{

public:
	RasterState();
	~RasterState();

	void use();
	void toggleWireframe();
	void toggleWireframe(bool b);

private:
	bool m_RenderWireframe = true;

	ComPtr<ID3D11RasterizerState> m_RasterStateSolid = nullptr;
	void createRasterStateSolid();

	ComPtr<ID3D11RasterizerState> m_RasterStateWireframe = nullptr;
	void createRasterStateWireframe();

	ID3D11DeviceContext* context;
};


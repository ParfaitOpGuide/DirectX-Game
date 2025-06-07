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

	// Bind the raster state to the pipeline
	void Use();

	// Toggle between solid and wireframe
	void ToggleWireframe();

private:
	bool m_RenderWireframe = false;

	ComPtr<ID3D11RasterizerState> m_RasterStateSolid = nullptr;
	void CreateRasterStateSolid();

	ComPtr<ID3D11RasterizerState> m_RasterStateWireframe = nullptr;
	void CreateRasterStateWireframe();
};


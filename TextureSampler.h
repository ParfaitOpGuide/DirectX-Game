#pragma once
#include <wrl.h>
#include <d3d11.h>
#include "GraphicsEngine.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace Microsoft::WRL;
class TextureSampler
{
	

public:
	TextureSampler();
	virtual ~TextureSampler() = default;

	// Bind texture sampler to pipeline
	void Use();

private:
	ComPtr<ID3D11SamplerState> m_SamplerState;
	void CreateSamplerState();
};


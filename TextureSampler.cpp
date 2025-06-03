#include "TextureSampler.h"

void TextureSampler::CreateSamplerState()
{
	ID3D11Device* device = GraphicsEngine::get()->getDevice();

	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = D3D11_FILTER_ANISOTROPIC;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias = 0;
	desc.MaxAnisotropy = D3D11_REQ_MAXANISOTROPY;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.MinLOD = 0;
	desc.MaxLOD = 1000.0f;
}

void TextureSampler::Use()
{
	ID3D11DeviceContext* context = GraphicsEngine::get()->getDeviceContext();

	const int sampler_slot = 0;
	context->PSSetSamplers(sampler_slot, 1, m_SamplerState.GetAddressOf());
}
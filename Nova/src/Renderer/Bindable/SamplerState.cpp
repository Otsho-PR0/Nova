#include <Renderer/Bindable/SamplerState.hpp>

using namespace Nova;

SamplerState::SamplerState(RendererContext& context)
{
	D3D11_SAMPLER_DESC sd = {};
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	context.GetDevice()->CreateSamplerState(&sd, m_SamplerState.GetAddressOf());
}

void SamplerState::Bind(RendererContext& context)
{
	context.GetContext()->PSSetSamplers(0u, 1u, m_SamplerState.GetAddressOf());
}

#pragma once

#include <Renderer/Bindable/Bindable.hpp>

class SamplerState : public IBindable
{
public:
	SamplerState(SamplerState const&) = delete;
	SamplerState() = default;
	SamplerState(Nova::RendererContext& context);

	void Bind(Nova::RendererContext& context);

private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_SamplerState;
};

#pragma once

#include <Renderer/Bindable/Bindable.hpp>

class Texture2D : public IBindable
{
public:
	Texture2D(Texture2D const&) = delete;
	Texture2D() = default;
	Texture2D(Nova::RendererContext& context, const char* path);

	void Bind(Nova::RendererContext& context);

private:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_Texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
};

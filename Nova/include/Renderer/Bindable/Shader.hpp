#pragma once

#include <Renderer/Bindable/Bindable.hpp>

namespace Nova
{
	class NOVA_API VertexShader : public IBindable
	{
	public:
		VertexShader(VertexShader const&) = delete;
		VertexShader() = default;
		VertexShader(RendererContext& context, const wchar_t* path);

		void Bind(RendererContext& context);

	private:
		friend class InputLayout;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_Shader;
		Microsoft::WRL::ComPtr<ID3DBlob> m_Blob;
	};

	class NOVA_API PixelShader : public IBindable
	{
	public:
		PixelShader(PixelShader const&) = delete;
		PixelShader(RendererContext& context, const wchar_t* path);

		void Bind(RendererContext& context);

	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_Shader;
	};
}
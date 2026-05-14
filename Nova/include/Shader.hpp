#pragma once

#include <Renderer.hpp>

class NOVA_API VertexShader
{
public:
	VertexShader(const VertexShader&) = delete;
	VertexShader() = default;
	VertexShader(RendererContext& context, const wchar_t* path);
	~VertexShader();

	void Bind(RendererContext& context);

private:
	friend class InputLayout;
	ID3D11VertexShader* m_Shader = nullptr;
	ID3DBlob* m_Blob = nullptr;
};

class NOVA_API PixelShader
{
public:
	PixelShader(const PixelShader&) = delete;
	PixelShader() = default;
	PixelShader(RendererContext& context, const wchar_t* path);
	~PixelShader();

	void Bind(RendererContext& context);

private:
	ID3D11PixelShader* m_Shader = nullptr;
};
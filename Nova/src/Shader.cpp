#include <Shader.hpp>

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include <filesystem>

VertexShader::VertexShader(RendererContext& context, const wchar_t* path)
{
	ID3DBlob* error = nullptr;
	if (std::filesystem::exists(path))
	{
		D3DCompileFromFile(path, nullptr, nullptr, "main", "vs_4_1", 0u, 0u, &m_Blob, &error);
		if (error)
			MessageBox(nullptr, (LPCSTR)error->GetBufferPointer(), "Failed compiling Vertex Shader", MB_ICONERROR);
		context.GetDevice()->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_Shader);
	}
	else
	{
		MessageBoxW(nullptr, path, L"Failed load Vertex Shader", MB_ICONERROR);
	}
}

VertexShader::~VertexShader()
{
	m_Blob->Release();
	m_Shader->Release();
}

void VertexShader::Bind(RendererContext& context)
{
	context.GetContext()->VSSetShader(m_Shader, nullptr, 0u);
}

PixelShader::PixelShader(RendererContext& context, const wchar_t* path)
{
	ID3DBlob* m_Blob;
	ID3DBlob* error;
	if (std::filesystem::exists(path))
	{
		D3DCompileFromFile(path, nullptr, nullptr, "main", "ps_4_1", 0u, 0u, &m_Blob, &error);
		if (error)
			MessageBox(nullptr, (LPCSTR)error->GetBufferPointer(), "Failed compiling Pixel Shader", MB_ICONERROR);
		context.GetDevice()->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_Shader);
	}
	else
	{
		MessageBoxW(nullptr, path, L"Failed load Pixel Shader", MB_ICONERROR);
	}
}

PixelShader::~PixelShader()
{
	m_Shader->Release();
}

void PixelShader::Bind(RendererContext& context)
{
	context.GetContext()->PSSetShader(m_Shader, nullptr, 0u);
}
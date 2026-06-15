#include <Renderer/Bindable/Shader.hpp>

#include <d3dcompiler.h>
#include <Core/Exception.hpp>
#include <filesystem>

using namespace Nova;

VertexShader::VertexShader(RendererContext& context, const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3DBlob> error;
	if (std::filesystem::exists(path))
	{
		D3DCompileFromFile(path, nullptr, nullptr, "main", "vs_4_1", 0u, 0u, &m_Blob, error.GetAddressOf());
		if (error)
			throw Exception("DirectX", std::string("Failed to compile Vertex Shader: '").append((char*)error->GetBufferPointer()).append("'").c_str());
		context.GetDevice()->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, m_Shader.GetAddressOf());
	}
	else
		throw ExceptionW(L"DirectX", std::wstring(L"Failed to load Vertex Shader: '").append(path).append(L"'").c_str());
}

void VertexShader::Bind(RendererContext& context)
{
	context.GetContext()->VSSetShader(m_Shader.Get(), nullptr, 0u);
}

PixelShader::PixelShader(RendererContext& context, const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3DBlob> m_Blob;
	Microsoft::WRL::ComPtr<ID3DBlob> error;
	if (std::filesystem::exists(path))
	{
		D3DCompileFromFile(path, nullptr, nullptr, "main", "ps_4_1", 0u, 0u, m_Blob.GetAddressOf(), error.GetAddressOf());
		if (error)
			MessageBox(nullptr, (LPCSTR)error->GetBufferPointer(), "Failed compiling Pixel Shader", MB_ICONERROR);
		context.GetDevice()->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, m_Shader.GetAddressOf());
	}
	else
		MessageBoxW(nullptr, path, L"Failed load Pixel Shader", MB_ICONERROR);
}

void PixelShader::Bind(RendererContext& context)
{
	context.GetContext()->PSSetShader(m_Shader.Get(), nullptr, 0u);
}

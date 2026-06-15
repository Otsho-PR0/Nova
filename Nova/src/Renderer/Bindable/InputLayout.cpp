#include <Renderer/Bindable/InputLayout.hpp>

using namespace Nova;

InputLayout::InputLayout(RendererContext& context, D3D11_INPUT_ELEMENT_DESC* elements, size_t size, VertexShader& shader)
{
	context.GetDevice()->CreateInputLayout(elements, (UINT)size / (UINT)sizeof(D3D11_INPUT_ELEMENT_DESC), shader.m_Blob->GetBufferPointer(), shader.m_Blob->GetBufferSize(), m_InputLayout.GetAddressOf());
}

void InputLayout::Bind(RendererContext& context)
{
	context.GetContext()->IASetInputLayout(m_InputLayout.Get());
}

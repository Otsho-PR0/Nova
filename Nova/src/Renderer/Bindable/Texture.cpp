#include <Renderer/Bindable/Texture.hpp>

#include <stb_image.h>

using namespace Nova;

Texture2D::Texture2D(RendererContext& context, const char* path)
{
	int width, height, channels;
	unsigned char* data = stbi_load(path, &width, &height, &channels, 4);

	if (data)
	{
		D3D11_TEXTURE2D_DESC td = {};
		td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		td.Width = width;
		td.Height = height;
		td.Usage = D3D11_USAGE_DEFAULT;
		td.CPUAccessFlags = 0u;
		td.SampleDesc.Count = 1u;
		td.SampleDesc.Quality = 0u;
		td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		td.ArraySize = 1u;
		td.MipLevels = 1u;

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = data;
		sd.SysMemPitch = width * sizeof(unsigned char) * 4;

		context.GetDevice()->CreateTexture2D(&td, &sd, m_Texture.GetAddressOf());

		if (m_Texture)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvd = {};
			srvd.Texture2D.MipLevels = 1u;
			srvd.Texture2D.MostDetailedMip = 0u;
			srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvd.Format = td.Format;

			context.GetDevice()->CreateShaderResourceView(m_Texture.Get(), &srvd, m_ShaderResourceView.GetAddressOf());
		}
	}
	else
		MessageBox(nullptr, path, "Can't load texture", MB_OK);
}

void Texture2D::Bind(RendererContext& context)
{
	context.GetContext()->PSSetShaderResources(0u, 1u, m_ShaderResourceView.GetAddressOf());
}

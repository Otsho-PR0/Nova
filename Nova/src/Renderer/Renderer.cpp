#include <Renderer/Renderer.hpp>

#include <Core/Window.hpp>
#include <Core/Exception.hpp>
#include <Renderer/Drawable/Mesh.hpp>
#include <Renderer/Bindable/Texture.hpp>
#include <Renderer/Bindable/SamplerState.hpp>
#include <Core/Input.hpp>
#include <Math/Math.hpp>
#include <utility>

using namespace Nova;

RendererContext::RendererContext(HWND& hWnd) :
	m_Window(reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA)))
{
	RECT rect = {};
	GetClientRect(hWnd, &rect);
	DXGI_SWAP_CHAIN_DESC scd = {};

	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = rect.right - rect.left;
	scd.BufferDesc.Height = rect.bottom - rect.top;
	scd.BufferCount = 1u;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.Windowed = TRUE;
	scd.SampleDesc.Count = 1u;
	scd.SampleDesc.Quality = 0u;

#ifdef DEBUG
	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0u, D3D11_SDK_VERSION, &scd, m_SwapChain.GetAddressOf(), m_Device.GetAddressOf(), nullptr, m_Context.GetAddressOf());
#else
	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 0u, nullptr, 0u, D3D11_SDK_VERSION, &scd, m_SwapChain.GetAddressOf(), m_Device.GetAddressOf(), nullptr, m_Context.GetAddressOf());
#endif

	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	m_SwapChain->GetBuffer(0u, __uuidof(ID3D11Resource), (void**)backBuffer.GetAddressOf());

	m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_RenderTargetView.GetAddressOf());

	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState;

	m_Device->CreateDepthStencilState(&dsd, m_DepthStencilState.GetAddressOf());
	m_Context->OMSetDepthStencilState(m_DepthStencilState.Get(), 1u);

	D3D11_TEXTURE2D_DESC depthTexDesc = {};
	depthTexDesc.Width = rect.right - rect.left;
	depthTexDesc.Height = rect.bottom - rect.top;
	depthTexDesc.MipLevels = 1u;
	depthTexDesc.ArraySize = 1u;
	depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthTexDesc.SampleDesc.Count = 1u;
	depthTexDesc.SampleDesc.Quality = 0u;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilTexture;
	m_Device->CreateTexture2D(&depthTexDesc, nullptr, depthStencilTexture.GetAddressOf());

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	m_Device->CreateDepthStencilView(depthStencilTexture.Get(), &dsvDesc, m_DepthStencilView.GetAddressOf());
	m_Context->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());

	m_Context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Viewport.TopLeftX = 0.0f;
	m_Viewport.TopLeftY = 0.0f;
	m_Viewport.Width = (float)rect.right - rect.left;
	m_Viewport.Height = (float)rect.bottom - rect.top;
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;
	m_Context->RSSetViewports(1, &m_Viewport);
#ifdef DEBUG
	m_Device->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)m_InfoQueue.GetAddressOf());
#endif

	D3D11_INPUT_ELEMENT_DESC desc[] =
	{
		{ "POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ "NORMAL", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, offsetof(Vertex, normal), D3D11_INPUT_PER_VERTEX_DATA, 0u },
		{ "TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, offsetof(Vertex, texCoords), D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	VertexShader vs(*this, L"../../../res/Shaders/DummyShader.hlsl");

	Mesh::il = std::move(InputLayout(*this, desc, sizeof(desc), vs));
	reinterpret_cast<Window*>(m_Window)->m_Context = this;
}

void RendererContext::Clear(float r, float g, float b, float a)
{
	FLOAT color[4] =
	{
		r, g, b, a
	};
	m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), color);
	m_Context->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void RendererContext::Swap(unsigned int syncInterval)
{
	m_SwapChain->Present(syncInterval, 0u);
}

#ifdef DEBUG
void RendererContext::PollInfo()
{
	UINT64 n = m_InfoQueue->GetNumStoredMessages();

	for (UINT64 i = 0u; i < n; i++)
	{
		SIZE_T length = 0u;
		m_InfoQueue->GetMessage(i, nullptr, &length);
		D3D11_MESSAGE* message = nullptr;
		message = reinterpret_cast<D3D11_MESSAGE*>(malloc(length));
		m_InfoQueue->GetMessage(i, message, &length);

		if (message)
			switch (message->Severity)
			{
			case D3D11_MESSAGE_SEVERITY_INFO:
				MessageBox(*reinterpret_cast<Window*>(m_Window), message->pDescription, "DirectX Info", MB_ICONERROR);
				break;
			case D3D11_MESSAGE_SEVERITY_WARNING:
				if (MessageBox(*reinterpret_cast<Window*>(m_Window), message->pDescription, "DirectX Warning", MB_ICONERROR | MB_OKCANCEL) == IDCANCEL)
					SendMessage(*reinterpret_cast<Window*>(m_Window), WM_CLOSE, 0, 0);
				break;
			case D3D11_MESSAGE_SEVERITY_ERROR:
				throw Exception("Nova", message->pDescription);
				break;
			}
	}

	m_InfoQueue->ClearStoredMessages();
}
#else
void RendererContext::PollInfo()
{
}
#endif

LRESULT RendererContext::PollEvents(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_SIZE:
	{
		if (m_SwapChain != nullptr)
		{
			UINT width  = LOWORD(lParam);
			UINT height = HIWORD(lParam);

			m_Context->OMSetRenderTargets(0u, nullptr, nullptr);
			m_RenderTargetView.Reset();
			m_DepthStencilView.Reset();
			m_Context->Flush();

			m_SwapChain->ResizeBuffers(0u, width, height, DXGI_FORMAT_UNKNOWN, 0u);

			Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
			m_SwapChain->GetBuffer(0u, __uuidof(ID3D11Resource), (void**)backBuffer.GetAddressOf());
			m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_RenderTargetView.GetAddressOf());

			D3D11_TEXTURE2D_DESC depthTexDesc = {};
			depthTexDesc.Width = width;
			depthTexDesc.Height = height;
			depthTexDesc.MipLevels = 1;
			depthTexDesc.ArraySize = 1;
			depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
			depthTexDesc.SampleDesc.Count = 1;
			depthTexDesc.SampleDesc.Quality = 0;
			depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
			depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilTexture;
			m_Device->CreateTexture2D(&depthTexDesc, nullptr, depthStencilTexture.GetAddressOf());
			D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
			dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
			dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			m_Device->CreateDepthStencilView(depthStencilTexture.Get(), &dsvDesc, m_DepthStencilView.GetAddressOf());

			m_Context->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());

			m_Viewport.Width  = (float)width;
			m_Viewport.Height = (float)height;
			m_Context->RSSetViewports(1, &m_Viewport);
		}
	} break;
	case WM_SIZING:
		Clear(0.0f, 0.0f, 0.0f, 1.0f);
		Swap();
		break;
	}

	return 0;
}

ID3D11Device* RendererContext::GetDevice()
{
	return m_Device.Get();
}

ID3D11DeviceContext* RendererContext::GetContext()
{
	return m_Context.Get();
}

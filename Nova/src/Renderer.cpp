#include <Renderer.hpp>

#include <InputLayout.hpp>
#include <Buffer.hpp>

RendererContext::RendererContext(HWND& hWnd)
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

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0u, D3D11_SDK_VERSION, &scd, &m_SwapChain, &m_Device, nullptr, &m_Context);

	ID3D11Resource* backBuffer = nullptr;
	m_SwapChain->GetBuffer(0u, __uuidof(ID3D11Resource), (void**)&backBuffer);
	m_Device->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTargetView);
	m_Context->OMSetRenderTargets(1u, &m_RenderTargetView, nullptr);
	backBuffer->Release();

	m_Viewport.TopLeftX = 0.0f;
	m_Viewport.TopLeftY = 0.0f;
	m_Viewport.Width = (float)rect.right - rect.left;
	m_Viewport.Height = (float)rect.bottom - rect.top;
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;
	m_Context->RSSetViewports(1, &m_Viewport);

	m_Device->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&m_InfoQueue);
}

void RendererContext::Clear(float r, float g, float b, float a)
{
	FLOAT color[4] =
	{
		r, g, b, a
	};
	m_Context->ClearRenderTargetView(m_RenderTargetView, color);
}

RendererContext::~RendererContext()
{
	m_InfoQueue->Release();
	m_RenderTargetView->Release();
	m_Context->Release();
	m_Device->Release();
	m_SwapChain->Release();
}

void RendererContext::DrawTestTriangle()
{
	Vertex vertices[] =
	{
		{  0.0f,  0.5f, 1.0f, 0.0f, 0.0f },
		{  0.5f, -0.5f, 0.0f, 1.0f, 0.0f },
		{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f }
	};

	unsigned int indices[] = { 0u, 1u, 2u };

	VertexShader vs(*this, L"res/Shaders/VertexShader.hlsl");
	PixelShader  ps(*this, L"res/Shaders/PixelShader.hlsl");

	VertexBuffer vb(*this, vertices, sizeof(vertices));
	IndexBuffer  ib(*this, indices,  sizeof(indices));

	D3D11_INPUT_ELEMENT_DESC desc[] =
	{
		{ "POSITION", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA,0u },
		{ "COLOR", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, offsetof(Vertex, r), D3D11_INPUT_PER_VERTEX_DATA,0u},
	};

	InputLayout il(*this, desc, sizeof(desc), vs);

	vs.Bind(*this);
	ps.Bind(*this);
	il.Bind(*this);
	vb.Bind(*this);
	ib.Bind(*this);
	GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GetContext()->DrawIndexed(3u, 0u, 0);
}

void RendererContext::Swap()
{
	m_SwapChain->Present(1u, 0u);
}

void RendererContext::Info()
{
	UINT64 n = m_InfoQueue->GetNumStoredMessages();

	for (UINT64 i = 0u; i < n; i++)
	{
		SIZE_T length = 0u;
		m_InfoQueue->GetMessage(i, nullptr, &length);
		D3D11_MESSAGE* message = (D3D11_MESSAGE*)malloc(length);
		m_InfoQueue->GetMessage(i, message, &length);
		MessageBox(nullptr, message->pDescription, "DirectX Error", MB_ICONERROR);
	}
	m_InfoQueue->ClearStoredMessages();
}

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

			m_RenderTargetView->Release();
			m_Context->OMSetRenderTargets(0u, nullptr, nullptr);
			m_Context->Flush();

			m_SwapChain->ResizeBuffers(0u, width, height, DXGI_FORMAT_UNKNOWN, 0u);

			ID3D11Resource* backBuffer = nullptr;
			m_SwapChain->GetBuffer(0u, __uuidof(ID3D11Resource), (void**)&backBuffer);
			m_Device->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTargetView);
			m_Context->OMSetRenderTargets(1u, &m_RenderTargetView, nullptr);
			backBuffer->Release();

			m_Viewport.Width  = (float)width;
			m_Viewport.Height = (float)height;
			m_Context->RSSetViewports(1, &m_Viewport);
		}
		return DefWindowProc(hWnd, Msg, wParam, lParam);
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
	return m_Device;
}

ID3D11DeviceContext* RendererContext::GetContext()
{
	return m_Context;
}
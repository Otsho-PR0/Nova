#pragma once

#include <Nova.hpp>
#include <d3d11.h>

struct NOVA_API RendererContext
{
public:
	RendererContext(HWND&);
	~RendererContext();

	void Clear(float r, float g, float b, float a);
	void DrawTestCube();
	void Swap();

	void Info();

	LRESULT CALLBACK PollEvents(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

private:
	IDXGISwapChain* m_SwapChain = nullptr;
	ID3D11Device* m_Device = nullptr;
	ID3D11DeviceContext* m_Context = nullptr;
	ID3D11RenderTargetView* m_RenderTargetView = nullptr;
	ID3D11InfoQueue* m_InfoQueue = nullptr;
	D3D11_VIEWPORT m_Viewport = {};
};
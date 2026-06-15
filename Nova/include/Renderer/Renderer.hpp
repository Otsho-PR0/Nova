#pragma once

#include <Nova.hpp>
#include <d3d11.h>
#include <wrl/client.h>

namespace Nova
{
	class NOVA_API RendererContext
	{
	public:
		RendererContext(const RendererContext&) = delete;
		RendererContext(HWND&);

		void Clear(float r, float g, float b, float a);
		void Swap(unsigned int syncInterval = 0u);

		void PollInfo();

		LRESULT CALLBACK PollEvents(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetContext();

	private:
		void* m_Window;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView;
	#ifdef DEBUG
		Microsoft::WRL::ComPtr<ID3D11InfoQueue> m_InfoQueue;
	#endif
		D3D11_VIEWPORT m_Viewport = {};
	};
}
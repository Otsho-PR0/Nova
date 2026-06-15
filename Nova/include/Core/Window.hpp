#pragma once

#include <Nova.hpp>
#include <functional>

LRESULT CALLBACK DefWinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

namespace Nova
{
	class NOVA_API Window
	{
	public:
		Window(Window const&) = delete;
		Window() = delete;
		Window(const char* title, int width, int height, HMENU hMenu = nullptr);
		~Window();

		Window& operator=(const Window&) = delete;

		operator HWND&();

		void Show() const;
		void Hide() const;
		void Maximize() const;
		void Normalize() const;
		void Minimize() const;
		void Close();

		void SetTitle(const char* title) const;
		void SetMenu(LPCSTR menu);
		void SetMenu(HMENU hMenu);
		void SetCustomWindowProc(std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>);

		long GetWidth() const;
		long GetHeight() const;

		bool CursorVisible = true;

		void PollEvents();
		bool ShouldClose();

		friend LRESULT CALLBACK Setup(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
		friend int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	
	private:
		friend class RendererContext;
		HWND hWnd;
		bool m_ShouldClose = false;
		void* m_Context = nullptr;
		std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> m_WndProc;
	
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK HandleMessages(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	};
}
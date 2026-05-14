#pragma once

#include <Nova.hpp>

#include <Windows.h>

#include <Renderer.hpp>

LRESULT CALLBACK DefWinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

class NOVA_API Window
{
public:
	Window(const Window&) = delete;
	Window() = delete;
	Window(const char* title, int width, int height);
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

	void PollEvents(RendererContext* context = nullptr);
	bool ShouldClose();

	friend LRESULT CALLBACK DefWinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	friend int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	
private:
	HWND hWnd;
	bool m_ShouldClose = false;
	RendererContext* context = nullptr;
	
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK HandleMessages(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
};
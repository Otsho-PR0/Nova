#pragma once


//#ifdef Nova_EXPORTS
//#define NOVA_API __declspec(dllexport)
//#else
//#define NOVA_API __declspec(dllimport)
//#endif


#define NOVA_API

#include <Windows.h>

namespace Nova
{
	extern WNDCLASS NOVA_API wc;
	NOVA_API LRESULT CALLBACK Setup(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	NOVA_API void Init(HINSTANCE hInstance, LPCSTR menu = 0, HICON hIcon = NULL);
	NOVA_API void Destroy();
};

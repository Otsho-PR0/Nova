#pragma once

#ifdef NOVA_EXPORTS
#define NOVA_API __declspec(dllexport)
#else
#define NOVA_API __declspec(dllimport)
#endif

#include <Windows.h>

namespace Nova
{
	extern WNDCLASS NOVA_API wc;
	NOVA_API void Init(HINSTANCE);
	NOVA_API void Destroy();
};
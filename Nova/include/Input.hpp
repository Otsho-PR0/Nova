#pragma once

#include <Nova.hpp>

class NOVA_API Input
{
public:
	Input() = delete;
	Input& operator=(const Input&) = delete;
	
	static bool GetKey(unsigned char key);
	static bool GetKeyDown(unsigned char key);
	static bool GetKeyUp(unsigned char key);

	static void Reset();

private:
	friend class Window;
	static unsigned char keyboard[256];
};
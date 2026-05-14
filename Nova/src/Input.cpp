#include <Input.hpp>

unsigned char Input::keyboard[256] = {};

bool Input::GetKey(unsigned char key)
{
	return keyboard[key] & 0b111100;
}

bool Input::GetKeyDown(unsigned char key)
{
	return keyboard[key] == 0b111100;
}

bool Input::GetKeyUp(unsigned char key)
{
	return keyboard[key] == 0b000011;
}

void Input::Reset()
{
	for (unsigned char& key : keyboard)
		key &= 0b110000;
}
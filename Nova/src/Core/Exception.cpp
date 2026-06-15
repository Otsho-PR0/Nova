#include <Core/Exception.hpp>

using namespace Nova;

Exception::Exception(const char* caption, const char* message) :
	std::exception(message),
	m_Caption(caption)
{ }

const char* Exception::Caption() noexcept
{
	return m_Caption;
}

ExceptionW::ExceptionW(const wchar_t* caption, const wchar_t* message) :
	m_Message(message),
	m_Caption(caption)
{
}

const wchar_t* ExceptionW::Caption() noexcept
{
	return m_Caption.c_str();
}

const wchar_t* ExceptionW::Message() noexcept
{
	return m_Message.c_str();
}
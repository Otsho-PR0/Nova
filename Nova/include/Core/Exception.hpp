#pragma once

#include <Nova.hpp>
#include <exception>
#include <string>

namespace Nova
{
	class NOVA_API Exception : public std::exception
	{
	public:
		Exception(const char* caption, const char* message);

		const char* Caption() noexcept;

	private:
		const char* m_Caption;
	};

	class NOVA_API ExceptionW
	{
	public:
		ExceptionW(const wchar_t* caption, const wchar_t* message);

		const wchar_t* Caption() noexcept;
		const wchar_t* Message() noexcept;

	private:
		std::wstring m_Caption;
		std::wstring m_Message;
	};
}
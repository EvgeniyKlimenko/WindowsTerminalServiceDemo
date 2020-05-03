#include "stdafx.h"
#include "Exception.h"

CWindowsException::CWindowsException(const CWindowsException& other)
{
	m_code = other.m_code;
	if (other.m_description.empty())
		ResolveDescription();
	else
		m_description = other.m_description;
}

CWindowsException& CWindowsException::operator = (const CWindowsException& other)
{
	if (this != &other)
	{
		m_code = other.m_code;
		if (other.m_description.empty())
			ResolveDescription();
	}

	return *this;
}

const char* CWindowsException::what() const
{
	return m_description.c_str();
}

std::string CWindowsException::GetErrorDescription(ULONG code)
{
	_TCHAR* msg = nullptr;
	std::string descr;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<_TCHAR*>(&msg), 0, nullptr);
	if (msg)
	{
		_tstringstream stm;
		stm << _T("Windows error ") << code << _T(" - ") << msg;
		_tstring str = stm.str();
		descr.assign(std::begin(str), std::end(str));
		LocalFree(msg);
	}

	return descr;
}

void CWindowsException::ResolveDescription()
{
	m_description = GetErrorDescription(m_code);
}
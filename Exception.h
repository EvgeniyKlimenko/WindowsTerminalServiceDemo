#pragma once

class CWindowsException final : public std::exception
{
public:
	CWindowsException(ULONG code) : m_code(code)
	{
		ResolveDescription();
	}

	CWindowsException(const CWindowsException& other);
	virtual ~CWindowsException() = default;

	CWindowsException& operator = (const CWindowsException& other);
	const char* what() const override;

	static std::string GetErrorDescription(ULONG code);

private:
	void ResolveDescription();

private:
	ULONG m_code;
	std::string m_description;
};

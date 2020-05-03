#include "stdafx.h"
#include "WtsObjects.h"
#include "Exception.h"

CWtsServers::CWtsServers()
{
	if (!WTSEnumerateServers(nullptr, 0, 1, &m_entries, &m_count))
		throw CWindowsException(GetLastError());
}

CWtsSessions::CWtsSessions()
{
	if (!WTSEnumerateSessions(nullptr, 0, 1, &m_entries, &m_count))
		throw CWindowsException(GetLastError());
}

CWtsProcesses::CWtsProcesses()
{
	if (!WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE, 0, 1, &m_entries, &m_count))
		throw CWindowsException(GetLastError());
}

CUserInfo::CUserInfo(PSID sid)
	: m_sid(sid)
{
	if (!ConvertSidToStringSid(m_sid, &m_stringSid)) return;

	ULONG nameSize = 0;
	ULONG domainSize = 0;
	SID_NAME_USE sidNameUse;

	LookupAccountSid(nullptr, m_sid, nullptr, &nameSize, nullptr, &domainSize, &sidNameUse);
	if (!nameSize || !domainSize) return;

	m_domainName = (LPTSTR)LocalAlloc(LPTR, domainSize * sizeof(_TCHAR));
	if (!m_domainName) return;

	m_userName = (LPTSTR)LocalAlloc(LPTR, nameSize * sizeof(_TCHAR));
	if (!m_userName) return;

	LookupAccountSid(nullptr, m_sid, m_userName, &nameSize, m_domainName, &domainSize, &sidNameUse);
}

CUserInfo::~CUserInfo()
{
	if (m_userName) LocalFree(m_userName);
	if (m_domainName) LocalFree(m_domainName);
	if (m_stringSid) LocalFree(m_stringSid);
}
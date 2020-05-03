#pragma once

template <typename Derived, typename Entry>
class CWtsEnumeration
{
protected:
	ULONG m_count;
	Entry* m_entries;

public:
	template <typename T>
	class Iter_t : public std::iterator<std::forward_iterator_tag, T>
	{
		T* m_entries;
		ULONG& m_count;
		ULONG m_index;
	public:
		Iter_t(T* entries, ULONG count, ULONG index = 0)
			: m_entries(entries)
			, m_count(count)
			, m_index(index)
		{}

		Iter_t(const iterator& other)
			: m_entries(other.m_entries)
			, m_count(other.m_count)
			, m_index(other.m_index)
		{}

		Iter_t& operator++()
		{
			m_entries[++m_index];
			assert(m_index <= m_count);
			return *this;
		}

		Iter_t operator++(int)
		{
			Iter_t tmp(*this);
			operator++();
			return tmp;
		}

		bool operator==(const Iter_t& other) const
		{
			return m_index == other.m_index;
		}

		bool operator!=(const Iter_t& other) const
		{
			return !operator==(other);
		}

		T& operator*() { return m_entries[m_index]; }
	};

	using iterator = Iter_t<Entry>;

	CWtsEnumeration()
		: m_count(0)
		, m_entries(nullptr)
	{}

	~CWtsEnumeration()
	{
		if (m_entries) LocalFree(m_entries);
	}

	ULONG GetCount() const { return m_count; }

	iterator begin() { return iterator(m_entries, m_count); }

	iterator end() { return iterator(m_entries, m_count, m_count); }
};


class CWtsServers : public CWtsEnumeration<CWtsServers, WTS_SERVER_INFO>
{
public:
	CWtsServers();
};

class CWtsSessions : public CWtsEnumeration<CWtsSessions, WTS_SESSION_INFO>
{
public:
	CWtsSessions();
};

class CWtsProcesses : public CWtsEnumeration<CWtsProcesses, WTS_PROCESS_INFO>
{
public:
	CWtsProcesses();
};

class CUserInfo final
{
	PSID m_sid;
	LPTSTR m_stringSid = nullptr;
	LPTSTR m_userName = nullptr;
	LPTSTR m_domainName = nullptr;

public:
	CUserInfo(PSID sid);
	~CUserInfo();

	_tstring GetDomainName() { return m_domainName ? m_domainName : _T(""); }
	_tstring GetUserName() { return m_userName ? m_userName : _T(""); }
	_tstring GetUserSid() { return m_stringSid ? m_stringSid : _T(""); }
};


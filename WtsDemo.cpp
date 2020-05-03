// WtsDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WtsObjects.h"

using namespace std;

void Run()
{
	try
	{
		_tsetlocale(LC_ALL, _T(".866"));

		_tprintf_s(_T("Enumarating sessions of the current server. \n"));

		CWtsSessions sessions;

		_tprintf_s(_T("Current server has got %d sessions. \n"), sessions.GetCount());

		for (auto session : sessions)
		{
			_tprintf_s(_T("Session %d - state %d, name: %s. \n"), session.SessionId,
				session.State, session.pWinStationName);
		}

		_tprintf_s(_T("Enumarating processes of the current server. \n"));

		CWtsProcesses processes;

		_tprintf_s(_T("Current server has got %d processes. \n"), processes.GetCount());

		for (auto process : processes)
		{
			CUserInfo userInfo(process.pUserSid);
			_tprintf_s(_T("Process %s(%d) - session %d, user: %s/%s(%s). \n"), process.pProcessName,
				process.ProcessId, process.SessionId, userInfo.GetDomainName().c_str(),
				userInfo.GetUserName().c_str(), userInfo.GetUserSid().c_str());
		}

	}
	catch (std::exception& ex)
	{
		cerr << ex.what() << endl;
	}
	catch (...)
	{
		cerr << "Unknown error occurred." << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	Run();
	_getch();
	return 0;
}


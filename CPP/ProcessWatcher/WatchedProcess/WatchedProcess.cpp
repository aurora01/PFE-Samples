// WatchedProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

static LPCWSTR g_szStartEventName = L"{7418DA70-C365-443C-85C6-34E27BB053EF}_Start";
static LPCWSTR g_szProcessMutexName = L"{7418DA70-C365-443C-85C6-34E27BB053EF}_Mutex";

static void SignalProcessStartEvent()
{
	HANDLE hEvent = CreateEvent(NULL, TRUE, TRUE, g_szStartEventName);
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		SetEvent(hEvent);
		CloseHandle(hEvent);
	}
}

static HANDLE GetProcessMutex()
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, g_szProcessMutexName);
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		WaitForSingleObject(hMutex, INFINITE);
	}

	return hMutex;
}

static DWORD WINAPI ProcessSyncProc(LPVOID lpParam)
{
	HANDLE *phMutex = (HANDLE*)lpParam;
	*phMutex = GetProcessMutex();
	SignalProcessStartEvent();

	return 0;
}

static HANDLE ProcessSyncInit()
{
	HANDLE hMutex = GetProcessMutex();
	SignalProcessStartEvent();

	return hMutex;
}


int main()
{
	HANDLE hMutex = ProcessSyncInit();
	int ch = 0;

	printf("Watched process - Starting....\n");

	do {
		printf("Press 'x' to quit:");
		ch = getchar();
	} while (ch != 'x' && ch != 'X');

    return 0;
}


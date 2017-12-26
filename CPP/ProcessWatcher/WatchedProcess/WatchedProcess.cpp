// WatchedProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

static LPCWSTR g_szStartEventName = L"{7418DA70-C365-443C-85C6-34E27BB053EF}_Start";
static LPCWSTR g_szProcessMutexName = L"{7418DA70-C365-443C-85C6-34E27BB053EF}_Mutex";

int main()
{
	int ch = 0;
	HANDLE hStartEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, g_szStartEventName);
	HANDLE hMutex = NULL;

	if (NULL != hStartEvent)
	{
		hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, g_szProcessMutexName);
		WaitForSingleObject(hMutex, INFINITE);
		SetEvent(hStartEvent);

		CloseHandle(hStartEvent);
	}

	printf("Watched process - Starting....\n");

	do {
		printf("Press 'x' to quit:");
		ch = getchar();
	} while (ch != 'x' && ch != 'X');

	//if (NULL != hMutex)
	//{
	//	ReleaseMutex(hMutex);
	//	CloseHandle(hMutex);
	//}

    return 0;
}


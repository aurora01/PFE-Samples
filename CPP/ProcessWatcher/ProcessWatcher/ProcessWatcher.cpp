// ProcessWatcher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

static LPCWSTR g_szStartEventName = L"{7418DA70-C365-443C-85C6-34E27BB053EF}_Start";
static LPCWSTR g_szProcessMutexName = L"{7418DA70-C365-443C-85C6-34E27BB053EF}_Mutex";

static HANDLE FindWatchedProcess(LPCWSTR pszProcessName);

static DWORD WINAPI ProcessWatcherProc(LPVOID);
static DWORD WINAPI ProcessWatcherProc2(LPVOID);


int main()
{
	int ch = 0;

	printf("ProcessWatcher..............\n");
	CloseHandle(CreateThread(NULL, 0, ProcessWatcherProc, NULL, 0, NULL));

	Sleep(1000);
	do {
		printf("\nPress 'x' to quit:");
		ch = getchar();
	} while (ch != 'x' && ch != 'X');

	return 0;
}

static DWORD WINAPI ProcessWatcherProc(LPVOID)
{
	HANDLE hStartEvent = CreateEvent(NULL, TRUE, FALSE, g_szStartEventName);
	HANDLE hMutex = CreateMutex(NULL, FALSE, g_szProcessMutexName);

	printf("Waitting for WatchedProcess start!\n");
	while (true)
	{
		WaitForSingleObject(hStartEvent, INFINITE);
		printf("Application Started!\n");
		ResetEvent(hStartEvent);
		WaitForSingleObject(hMutex, INFINITE);
		ReleaseMutex(hMutex);
		printf("Application Exited!\n");

		// TODO: Send singal to main thread
	}

	return 0;
}

//static HANDLE FindWatchedProcess(LPCWSTR pszProcessName)
//{
//	HANDLE hProcess = NULL;
//	PROCESSENTRY32 pe32;
//
//	// Take a snapshot of all processes in the system.
//	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//	if (hProcessSnap != INVALID_HANDLE_VALUE)
//	{
//		// Set the size of the structure before using it.
//		pe32.dwSize = sizeof(PROCESSENTRY32);
//
//		// Retrieve information about the first process,
//		// and exit if unsuccessful
//		if (Process32First(hProcessSnap, &pe32))
//		{
//			do
//			{
//				if (0 == lstrcmpi(pe32.szExeFile, pszProcessName))
//				{
//					hProcess = OpenProcess(SYNCHRONIZE, FALSE, pe32.th32ProcessID);
//					break;
//				}
//			} while (Process32Next(hProcessSnap, &pe32));
//		}
//
//		CloseHandle(hProcessSnap);
//	}
//
//	return hProcess;
//}
//
//static DWORD WINAPI ProcessWatcherProc(LPVOID)
//{
//
//	// Check WatchedProcess already stared
//	HANDLE hWatchedProcess = FindWatchedProcess(L"WatchedProcess.exe");
//	
//	if (NULL != hWatchedProcess)
//	{
//		printf("Application ready Started!\n");
//		WaitForSingleObject(hWatchedProcess, INFINITE);
//		printf("Application Exited!\n");
//		CloseHandle(hWatchedProcess);
//	}
//
//	CloseHandle(CreateThread(NULL, 0, ProcessWatcherProc2, NULL, 0, NULL));
//
//	return 0;
//}

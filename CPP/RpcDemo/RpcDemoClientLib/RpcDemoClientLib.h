// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RPCDEMOCLIENTLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RPCDEMOCLIENTLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#include <Windows.h>

#ifdef RPCDEMOCLIENTLIB_EXPORTS
#define RPCDEMOCLIENTLIB_API __declspec(dllexport)
#else
#define RPCDEMOCLIENTLIB_API __declspec(dllimport)
#endif

RPCDEMOCLIENTLIB_API DWORD RpcDemo_OpenSession(unsigned long* handle);
RPCDEMOCLIENTLIB_API DWORD RpcDemo_CloseSession(unsigned long handle);
RPCDEMOCLIENTLIB_API void RpcDemo_HelloProc(unsigned long handle, wchar_t * pszString, long * longOut);

typedef void(WINAPI *PCALLBACK1_PROC)(wchar_t * pszString);
RPCDEMOCLIENTLIB_API void RpcDemo_SetCallback1(unsigned long handle, PCALLBACK1_PROC pfnCallback);

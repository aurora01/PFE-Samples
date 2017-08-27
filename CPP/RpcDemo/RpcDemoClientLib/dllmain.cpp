// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "SessionInfo.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
        return (RPC_S_OK == SessionInfo::Initialize());
        break;
	case DLL_PROCESS_DETACH:
        SessionInfo::Uninitialize();
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
	return TRUE;
}

/******************************************************/
/*         MIDL allocate and free                     */
/******************************************************/

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}

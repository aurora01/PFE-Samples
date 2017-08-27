// RpcServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RpcDemo_h.h"

handle_t IRpcDemo_IfHandle = NULL;

static WCHAR g_pszProtocolSequence[] = L"ncacn_np";
static WCHAR g_pszEndpoint[] = L"\\pipe\\hello";

int main()
{
    RPC_STATUS status;
    RPC_WSTR pszSecurity = NULL;
    unsigned int    cMinCalls = 1;
    unsigned int    fDontWait = FALSE;

    status = RpcServerUseProtseqEp(
                        (RPC_WSTR)g_pszProtocolSequence,    // _In_ RPC_WSTR Protseq
                        RPC_C_LISTEN_MAX_CALLS_DEFAULT,     // _In_ unsigned int MaxCalls
                        (RPC_WSTR)g_pszEndpoint,            // _In_ RPC_WSTR Endpoint        
                        pszSecurity);                       // _In_opt_ void __RPC_FAR * SecurityDescriptor

    if (status) exit(status);

    status = RpcServerRegisterIf(IRpcDemo_IfHandle, NULL, NULL);

    if (status)
        exit(status);

    status = RpcServerListen(cMinCalls,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        fDontWait);

    if (status) exit(status);

    return 0;
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


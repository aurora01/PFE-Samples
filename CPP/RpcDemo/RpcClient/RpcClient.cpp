// RpcClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\RpcServer\RpcDemo_h.h"


static WCHAR g_pszProtocolSequence[] = L"ncacn_np";
static WCHAR g_pszEndpoint[] = L"\\pipe\\hello";

int main()
{
    handle_t IRpcDemo_IfHandle = NULL;
    RPC_STATUS status;
    RPC_WSTR pszUuid = NULL;
    RPC_WSTR pszNetworkAddress = NULL;
    RPC_WSTR pszOptions = NULL;
    RPC_WSTR pszStringBinding = NULL;
    PWSTR pszString = L"hello, world..............................";
    unsigned long ulCode;

    status = RpcStringBindingCompose(
                            pszUuid,
                            (RPC_WSTR)g_pszProtocolSequence,
                            pszNetworkAddress,
                            (RPC_WSTR)g_pszEndpoint,
                            pszOptions,
                            &pszStringBinding);
    if (status) exit(status);

    status = RpcBindingFromStringBinding(pszStringBinding, &IRpcDemo_IfHandle);

    if (status)
        exit(status);

    RpcTryExcept
    {
        HelloProc(pszString);
    Shutdown();
    }
        RpcExcept(1)
    {
        ulCode = RpcExceptionCode();
        wprintf(L"\nRuntime reported exception 0x%lx = %ld\n", ulCode, ulCode);
    }
    RpcEndExcept

        status = RpcStringFree(&pszStringBinding);

    if (status) exit(status);

    status = RpcBindingFree(&IRpcDemo_IfHandle);

    if (status)
        exit(status);

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

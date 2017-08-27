#include "stdafx.h"

#include "SessionInfo.h"

RPC_WSTR SessionInfo::s_pszStringBinding = NULL;
std::map<unsigned long, SessionInfo*> SessionInfo::s_HandlMap;
unsigned long SessionInfo::s_handle_id = 0;

static WCHAR g_pszProtocolSequence[] = L"ncacn_np";
static WCHAR g_pszEndpoint[] = L"\\pipe\\hello";

#define HANDLE_STEP     4

RPC_STATUS SessionInfo::Initialize()
{
    RPC_STATUS status;
    RPC_WSTR pszUuid = NULL;
    RPC_WSTR pszNetworkAddress = NULL;
    RPC_WSTR pszOptions = NULL;

    status = RpcStringBindingCompose(
        pszUuid,
        (RPC_WSTR)g_pszProtocolSequence,
        pszNetworkAddress,
        (RPC_WSTR)g_pszEndpoint,
        pszOptions,
        &s_pszStringBinding);
    if (RPC_S_OK == status)
    {
        status = RpcBindingFromStringBinding(s_pszStringBinding, &IRpcDemo_IfHandle);
    }

    return status;
}

RPC_STATUS SessionInfo::Uninitialize()
{
    RPC_STATUS status = RPC_S_OK;
    RPC_STATUS result = RPC_S_OK;

    CloseAllSession();

    status = RpcStringFree(&s_pszStringBinding);
    if (RPC_S_OK != status)
    {
        result = status;
    }

    status = RpcBindingFree(&IRpcDemo_IfHandle);
    if (RPC_S_OK != status && RPC_S_OK == result)
    {
        result = status;
    }

    s_pszStringBinding = NULL;
    IRpcDemo_IfHandle = NULL;

    return result;
}

SessionMap::iterator SessionInfo::FindSession(unsigned long handle)
{
    return s_HandlMap.find(handle);
}

SessionInfo* SessionInfo::GetSession(unsigned long handle)
{
    SessionInfo* pResult = NULL;
    auto pIter = FindSession(handle);
    if (s_HandlMap.end() != pIter)
    {
        pResult = pIter->second;
    }

    return pResult;
}

DWORD SessionInfo::OpenSession(unsigned long* handle)
{
    if (NULL == handle)
    {
        return ERROR_INVALID_PARAMETER;
    }

    SessionInfo* pSession = new(std::nothrow) SessionInfo();
    if (NULL == pSession)
    {
        return ERROR_NOT_ENOUGH_MEMORY;
    }
    else if(!pSession->IsValid())
    {
        return ERROR_INVALID_HANDLE;
    }

    *handle = pSession->GetHandle();

    return ERROR_SUCCESS;
}

DWORD SessionInfo::CloseSession(unsigned long handle)
{
    auto pSession = GetSession(handle);
    if (NULL == pSession)
    {
        return ERROR_INVALID_HANDLE;
    }

    delete pSession;

    return ERROR_SUCCESS;
}

void SessionInfo::CloseAllSession()
{
    while (!s_HandlMap.empty())
    {
        auto pSession = s_HandlMap.begin()->second;
        delete pSession;
    }
}

SessionInfo::SessionInfo()
    : m_handle(0)
    , m_pfnCallback1(NULL)
{
    while (0 == s_handle_id || s_HandlMap.end() != FindSession(s_handle_id))
    {
        s_handle_id += HANDLE_STEP;
    }

    s_HandlMap[s_handle_id] = this;
    m_handle = s_handle_id;
    s_handle_id += HANDLE_STEP;
}


SessionInfo::~SessionInfo()
{
    m_pfnCallback1 = NULL;

    auto pIter = FindSession(m_handle);
    if (s_HandlMap.end() != pIter)
    {
        s_HandlMap.erase(pIter);
    }
}

void SessionInfo::Callback_1(wchar_t * pszString)
{
    if (NULL != m_pfnCallback1)
    {
        m_pfnCallback1(pszString);
    }
}

void CallbackProc_1(/* [in] */unsigned long handle, /* [string][in] */ wchar_t * pszString)
{
    auto pSession = SessionInfo::GetSession(handle);

    if (NULL != pSession)
    {
        pSession->Callback_1(pszString);
    }
}

#pragma region API
void SessionInfo::API_HelloProc(wchar_t * pszString, long *lData)
{
    ::RPC_HelloProc(m_handle, pszString, lData);
}

void SessionInfo::API_SetCallback1(PCALLBACK1_PROC pfnCallback)
{
    m_pfnCallback1 = pfnCallback;
}

#pragma endregion API

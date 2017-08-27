#pragma once

#include <windows.h>
#include <map>
#include <rpc.h>

class SessionInfo;

typedef std::map<unsigned long, SessionInfo*> SessionMap;

class SessionInfo
{
public:
    static RPC_STATUS Initialize();
    static RPC_STATUS Uninitialize();
    static SessionMap::iterator FindSession(unsigned long handle);
    static SessionInfo* GetSession(unsigned long handle);
    static DWORD OpenSession(unsigned long* handle);
    static DWORD CloseSession(unsigned long handle);
    static void CloseAllSession();

private:

    static RPC_WSTR s_pszStringBinding;
    static SessionMap s_HandlMap;
    static unsigned long s_handle_id;

public:
    SessionInfo();
    ~SessionInfo();
    unsigned long GetHandle()
    {
        return m_handle;
    }
    bool IsValid()
    {
        return 0 != m_handle;
    }
    void Callback_1(wchar_t * pszString);

#pragma region API
    void API_HelloProc(wchar_t * pszString, long *lData);
    void API_SetCallback1(PCALLBACK1_PROC pfnCallback);
#pragma endregion API

private:
    unsigned long m_handle;
    PCALLBACK1_PROC m_pfnCallback1;

};


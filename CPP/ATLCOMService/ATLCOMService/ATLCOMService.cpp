// ATLCOMService.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "ATLCOMService_i.h"


using namespace ATL;

#include <stdio.h>

class CATLCOMServiceModule : public ATL::CAtlServiceModuleT< CATLCOMServiceModule, IDS_SERVICENAME >
{
public :
	DECLARE_LIBID(LIBID_ATLCOMServiceLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLCOMSERVICE, "{FE29DA2C-D44F-4AD1-9CEB-42756A65FD5F}")
		HRESULT InitializeSecurity() throw()
	{
		// TODO : Call CoInitializeSecurity and provide the appropriate security settings for your service
		// Suggested - PKT Level Authentication, 
		// Impersonation Level of RPC_C_IMP_LEVEL_IDENTIFY 
		// and an appropriate Non NULL Security Descriptor.

		return S_OK;
	}

		// Called when the service is started
		void ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
	};

CATLCOMServiceModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

// manwoo
void CATLCOMServiceModule::ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	// TODO: Add your specialized code here and/or call the base class
	CAtlServiceModuleT<CATLCOMServiceModule, 100>::ServiceMain(dwArgc, lpszArgv);
}

#include "activepp.h"

#include "Helper.h"
#include "Session.h"

#include <stdio.h>
#include <iostream>
#include <future>
#include <unistd.h> // usleep

APISession* APISession::s_pInstance = NULL;
APISession::APISession()
: m_hSession(0)
, m_hLastRequest(0)
{
	bool init = ATInitAPI();
	m_hSession = ATCreateSession();
	s_pInstance = this;
}

APISession::~APISession(void)
{
	Destroy();
	ATDestroySession(m_hSession);
	s_pInstance = NULL;
}

bool APISession::Init(const ATGUID& apiUserid, const std::string& serverIpAddress, uint32_t serverPort, const wchar16_t* userid, const wchar16_t* password)
{
	std::future<int> future = APISession::s_pInstance->_promise.get_future();
	// Destroy();

	Helper::CopyString(m_userid, userid);
	Helper::CopyString(m_password, password);

	bool rc = ATSetAPIUserId(m_hSession, (LPATGUID)&apiUserid);

	if(rc == true) {
		rc = ATInitSession(m_hSession, serverIpAddress.c_str(), serverIpAddress.c_str(), serverPort, ATSessionStatusChangeCallback, true);
	}
	int val = future.get();
	return val;
}

bool APISession::Destroy()
{
	ATShutdownSession(m_hSession);
	return true;
}

/*static*/ void APISession::ATSessionStatusChangeCallback(uint64_t hSession, ATSessionStatusType statusType)
{
	std::string strStatusType;
	switch(statusType)
	{
	case SessionStatusConnected: strStatusType = "SessionStatusConnected"; break;
	case SessionStatusDisconnected: strStatusType = "SessionStatusDisconnected"; break;
	case SessionStatusDisconnectedDuplicateLogin: strStatusType = "SessionStatusDisconnectedDuplicateLogin"; break;
	default: break;
	}

	printf("RECV Status change [%s]\n", strStatusType.c_str());

	if(statusType == SessionStatusConnected)
	{
		APISession::s_pInstance->m_hLastRequest = ATCreateLoginRequest(hSession, APISession::s_pInstance->m_userid, APISession::s_pInstance->m_password, APISession::ATLoginResponseCallback);
		bool rc = ATSendRequest(hSession, APISession::s_pInstance->m_hLastRequest, DEFAULT_REQUEST_TIMEOUT, APISession::ATRequestTimeoutCallback);

		printf("SEND (%llu): Login request [%s] (rc=%d)\n", APISession::s_pInstance->m_hLastRequest, Helper::ConvertString(APISession::s_pInstance->m_userid,
			Helper::StringLength(APISession::s_pInstance->m_userid)).c_str(), rc);
	}
}

/*static*/ void	APISession::ATLoginResponseCallback(uint64_t hSession, uint64_t hRequest, LPATLOGIN_RESPONSE pResponse)
{
	std::string strLoginResponseType;
	switch(pResponse->loginResponse)
	{
	case LoginResponseSuccess: strLoginResponseType = "LoginResponseSuccess"; break;
	case LoginResponseInvalidUserid: strLoginResponseType = "LoginResponseInvalidUserid"; break;
	case LoginResponseInvalidPassword: strLoginResponseType = "LoginResponseInvalidPassword"; break;
	case LoginResponseInvalidRequest: strLoginResponseType = "LoginResponseInvalidRequest"; break;
	case LoginResponseLoginDenied: strLoginResponseType = "LoginResponseLoginDenied"; break;
	case LoginResponseServerError: strLoginResponseType = "LoginResponseServerError"; break;
	default: strLoginResponseType = "unknown"; break;
	}
	APISession::s_pInstance->_promise.set_value(5);
	printf("RECV (%llu): Login response [%s]\n", hRequest, strLoginResponseType.c_str());
}

/*static*/ void	APISession::ATServerTimeUpdateCallback(LPATTIME pServerTime)
{
	printf("RECV: Server time update [%0.2d:%0.2d:%0.2d %0.2d/%0.2d/%0.4d\n",
		pServerTime->hour, pServerTime->minute, pServerTime->second,
		pServerTime->month, pServerTime->day, pServerTime->year);
}

/*static*/ void	APISession::ATRequestTimeoutCallback(uint64_t hOrigRequest)
{
	printf("(%I64u): Request timed-out\n", hOrigRequest);
}

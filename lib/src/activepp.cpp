#include "activepp.h"

#include "calendar.h"
#include "Helper.h"
#include "Requestor.h"
#include "Session.h"
#include "Streamer.h"

#include <iostream>
#include <string>
#include <fstream>
#include <future>
#include <tuple>
#include <unistd.h> // usleep
#include <vector>


#include "ActiveTickServerAPI/ActiveTickServerAPI.h"


activepp::activepp(const std::string& _dataFolder) {
dataFolder = _dataFolder;
}
activepp::~activepp() {
  bool shut = ATShutdownAPI();
}

bool activepp::login( const std::string& username, const std::string& password, const std::string& apiUserId ) {

  std::string serverIpAddress = "activetick1.activetick.com";
  uint32_t serverPort = 443;

  ATGUID guidApiUserid = Helper::StringToATGuid(apiUserId);

  bool rc = m_session.Init(guidApiUserid, serverIpAddress, serverPort, &Helper::ConvertString(username).front(), &Helper::ConvertString(password).front());

  return true;
}


bool activepp::download( std::string& symbol, std::string& dateRange, std::string& type, std::string& time ) {

  std::cout << dateRange << std::endl;
  auto dates = calendar::parseDateRange(dateRange);

  ATTIME atBeginTime = Helper::StringToATTime("20170922000000");
  ATTIME atEndTime =   Helper::StringToATTime("20170922235959");
  ATSYMBOL atSymbol = Helper::StringToSymbol(symbol);

  {

  Requestor requestor(m_session, dataFolder);
  Streamer streamer(m_session);

  std::future<bool> future;
  bool success;
  requestor.setDate("20170922");
  future = requestor._promise.get_future();
  uint64_t request = requestor.SendATTickHistoryDbRequest(atSymbol, true, false, atBeginTime, atEndTime, 3000000);
  future.wait();
  }
  // {
  //
  // Requestor requestor(m_session, dataFolder);
  // Streamer streamer(m_session);
  //
  // std::future<bool> future;
  // bool success;
  // requestor.setDate("20170921");
  // future = requestor._promise.get_future();
  // uint64_t request = requestor.SendATTickHistoryDbRequest(atSymbol, true, false, atBeginTime, atEndTime, 3000000);
  // future.wait();
  // }


  return true;
}

void call(uint64_t origRequest, LPATSYMBOL pSymbols, uint32_t symbolsCount) {
  std::cout << symbolsCount << std::endl;
}

void callback(uint64_t origRequest, LPATSECTORLIST_RECORD pRecords, uint32_t recordsCount) {
  std::cout << sizeof(pRecords->sector) << " " << sizeof(pRecords->industry) << std::endl;
}

void timeout(uint64_t origRequest) {

}

bool activepp::constituent( ) {
	wchar16_t ye = 67;
  uint64_t request = ATCreateConstituentListRequest(m_session.GetSessionHandle(), ATConstituentListSector , &ye, call);
  ATSendRequest(m_session.GetSessionHandle(), request, DEFAULT_REQUEST_TIMEOUT, timeout);
  // uint64_t request = ATCreateSectorListRequest(m_session.GetSessionHandle(), callback);
  // ATSendRequest(m_session.GetSessionHandle(), request, DEFAULT_REQUEST_TIMEOUT, timeout);
  int seconds = 10;
  int microseconds = seconds * 1000000;
  usleep(microseconds);
}
bool activepp::download( std::string& symbol, std::string& date, std::string& type ) {
}

#include <string>
#include "Session.h"
#include <iostream>
#include <tuple>

class activepp {
public:
  activepp(const std::string&);
  ~activepp();
  bool login(const std::string&, const std::string&, const std::string&);
  bool download(std::string&, std::string&, std::string&, std::string&);
  bool download(std::string&, std::string&, std::string&);
  bool constituent( );
private:
  APISession m_session;
  std::string dataFolder;
};

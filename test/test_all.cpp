#include "activepp.h"
#include "calendar.h"
#include "config.h"

#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE( "Login to activetick.com servers") {


    SECTION(" login is successful ") {
      {
        activepp activepp(config::DATAFOLDER);
        REQUIRE( activepp.login(config::USERNAME, config::PASSWORD, config::APIUSERID) == true );
        std::string symbol{"IZEA"};
        std::string date{"20170101-20170102"};
        std::string type{"AAPL"};
        std::string timeRange{"AAPL"};
        // activepp.constituent();
        activepp.download(symbol, date, type, timeRange);
      }
    }
}
TEST_CASE( " calendar ") {



    SECTION(" single valid date returns array of single date ") {
      {
        std::vector<std::string> date{"20170101"};
        REQUIRE( date == calendar::parseDateRange("20170101") );
      }
    }
    SECTION(" single non-trading day date returns empty array ") {
      {
        std::vector<std::string> date{"20170101"};
        // REQUIRE(  );
      }
    }
    SECTION(" download data ") {
    }

}

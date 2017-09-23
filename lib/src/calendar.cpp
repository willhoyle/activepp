#include <map>
#include <string>
#include <vector>

#include <iostream>

namespace calendar {
  namespace dates {
    const std::map<std::string, std::map<std::string, std::vector<std::string> > > tradingDays{
      {"2017",
        {
          {"01", {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10"}},
          {"02", {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10"}}
        }
      }
    };
  }

  std::vector<std::string> parseDateRange(const std::string& dateRange) {
    std::vector<std::string> dates;

    // Match: YYYYMMDD-YYYYMMDD
    if (dateRange.length() == 17) {
      auto year_start = dateRange.substr(0, 4);
      auto month_start = dateRange.substr(4, 2);
      auto day_start = dateRange.substr(6, 2);

      auto year_end = dateRange.substr(9, 4);
      auto month_end = dateRange.substr(13, 2);
      auto day_end = dateRange.substr(15, 2);

      // std::cout << dates::tradingDays[year_start][month_start][0] << std::endl;
    } else if (dateRange.length() == 8) {
      auto year_start = dateRange.substr(0, 4);
      auto month_start = dateRange.substr(4, 2);
      auto day_start = dateRange.substr(6, 2);
      if (dates::tradingDays.count(year_start) > 0) {
        if (dates::tradingDays.at(year_start).count(month_start) > 0) {
          for (size_t i = 0; i < dates::tradingDays.at(year_start).at(month_start).size(); i++) {
            if (day_start == dates::tradingDays.at(year_start).at(month_start).at(i)) {
              dates.push_back(dateRange);
              break;
            }
          }
        }
      }
    }

    return dates;
  }
}

# activetick includes
INCLUDE_DIRECTORIES(${ACTIVETICK_FOLDER_PATH}/include)
INCLUDE_DIRECTORIES(${ACTIVETICK_FOLDER_PATH}/include/ActiveTickServerAPI)
INCLUDE_DIRECTORIES(${ACTIVETICK_FOLDER_PATH}/include/Shared)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}/src)


SET(LIB_SOURCES
  "${CMAKE_CURRENT_LIST_DIR}/src/activepp.cpp;"
  "${CMAKE_CURRENT_LIST_DIR}/src/calendar.cpp;"
  "${CMAKE_CURRENT_LIST_DIR}/src/Helper.cpp;"
  "${CMAKE_CURRENT_LIST_DIR}/src/Requestor.cpp;"
  "${CMAKE_CURRENT_LIST_DIR}/src/Session.cpp;"
  "${CMAKE_CURRENT_LIST_DIR}/src/Streamer.cpp;"
)

# Slowly going to remove code that triggers this error type.
# It's all caused by the included activetick code
# Uncomment the following if it's annoying to see these errors every build
# REMOVE_DEFINITIONS(-Wformat)

ADD_LIBRARY(activepp ${LIB_SOURCES})

TARGET_LINK_LIBRARIES(activepp ${ACTIVETICK_FOLDER_PATH}/bin/libActiveTickServerAPI.so)

TARGET_INCLUDE_DIRECTORIES(activepp PUBLIC ${PROJECT_SOURCE_DIR}/lib/src)
TARGET_INCLUDE_DIRECTORIES(activepp PUBLIC ${ACTIVETICK_FOLDER_PATH}/include/ActiveTickServerAPI)
TARGET_INCLUDE_DIRECTORIES(activepp PUBLIC ${ACTIVETICK_FOLDER_PATH}/include/Shared)
TARGET_COMPILE_OPTIONS(activepp PUBLIC -std=c++11)

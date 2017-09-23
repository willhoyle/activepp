CMAKE_MINIMUM_REQUIRED(VERSION 3.2)


# Catch.cpp - Testing library included in external libs
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/external/catch/include")

# Activetick - Not included, must be added to source at external/atfeed-cppsdk
# or at compile time add -DACTIVETICK_FOLDER_PATH=/path/to/lib
INCLUDE_DIRECTORIES("${ACTIVETICK_FOLDER_PATH}/include")
INCLUDE_DIRECTORIES("${ACTIVETICK_FOLDER_PATH}/include/Shared")
INCLUDE_DIRECTORIES("${ACTIVETICK_FOLDER_PATH}/include/ActiveTickServerAPI")

ADD_EXECUTABLE(activepp_test "${PROJECT_SOURCE_DIR}/test/test_all.cpp")
TARGET_LINK_LIBRARIES(activepp_test activepp)
TARGET_COMPILE_OPTIONS(activepp_test PUBLIC -std=c++11)

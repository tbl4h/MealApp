cmake_minimum_required(VERSION 3.16)
project(MyApplication LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CheckPIESupported)
#Instead of use conan manager possible to use CMake module called FetchContent 
#Not tested.
# @START UNCOMMENT SECTION
#include(FetchContent)
#FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY "https://github.com/google/googletest.git"
#   GIT_TAG "main"
#) 
#FetchContent_Declare(
#   libcurl
#   GIT_REPOSITORY "https://github.com/curl/curl.git"
#   GIT_TAG "master"
#) 
#FetchContent_MakeAvailable(googletest libcurl)
# @END UNCOMMENT SECTION
include(FindCURL)
include(FindGTest)
include(FindSQLite3)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#Set C++ compiler insted C
#set(CMAKE_CPP_COMPILER gcc)
#Set sanitizer flags

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer  -fsanitize=address -fsanitize=address  -fsanitize=undefined -lubsan -g")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fsanitize=address  -fsanitize=undefined -lubsan -g")

#Set libmpc path
set (LIBMPC_PATH "/usr/lib/x86_64-linux-gnu/libmpc.so.3")

message(STATUS "Cxx compiler version: " ${CMAKE_CXX_COMPILER_VERSION})
#Check if libCurl is installed on the system.
if(NOT CURL_FOUND)
  message(WARNING "libCurl is not installed on the system.\n")
else()
  message(STATUS "libCurl version: " ${CURL_VERSION_STRING})
endif()
#Check if googletest is installed on the system.
if(NOT GTEST_FOUND)
  message(WARNING "googletests is not installed on the system.\n")
else()
  message(STATUS "googltests found in: " ${GTEST_INCLUDE_DIRS})
endif()
#Check if HDF5 is installed on the system.
find_package (SQLite3)
if(NOT SQLite3_FOUND)
  message(WARNING "SQLite3 is not installed on thesystem.\n")
else()
  message(STATUS "SQLite3 version: " ${SQLite3_VERSION} ${SQLite3_INCLUDE_DIRS})
endif()
enable_testing()
find_package(GTest REQUIRED)

#Build source lib.
file(GLOB_RECURSE MY_APP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp)
file(GLOB_RECURSE MY_APP_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/headers/*.h)
add_library(my_app_src SHARED ${MY_APP_SRC} ${MY_APP_HEADERS})
target_include_directories(my_app_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source)
target_include_directories(my_app_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)
if (SQLite3_FOUND)
  include_directories(${SQLite3_INCLUDE_DIRS})
  target_link_libraries (my_app_src ${SQLite3_LIBRARIES})
endif (SQLite3_FOUND)
#Use C++ not C linker properties
#set_target_properties(my_app_src PROPERTIES LINKER_LANGUAGE CXX)
add_compile_options(
    "$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,CXX>:-std=c++17>"
)
#Enable warning for specified compiler (should finaly add -Werror to get all possible errors.)
target_compile_options(my_app_src PUBLIC
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wfatal-errors -pedantic -fPIC -Wconversion>
)

add_executable(my_app ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp )
# Check if  PIE (position independent executable) is supported by linker and enable it.
# By default it is enable for ubuntu binary
check_pie_supported(OUTPUT_VARIABLE output LANGUAGES CXX)
set_property(TARGET my_app PROPERTY POSITION_INDEPENDENT_CODE TRUE)
if(NOT CMAKE_CXX_LINK_PIE_SUPPORTED)
  message(WARNING "PIE is not supported at link time: ${output}.\n"
                  "PIE link options will not be passed to linker.")
endif()
target_link_libraries(my_app my_app_src)
target_link_libraries(my_app ${LIBMPC_PATH})
if (SQLite3_FOUND)
  include_directories(${SQLite3_INCLUDE_DIRS})
  target_link_libraries (my_app ${SQLite3_LIBRARIES})
endif (SQLite3_FOUND)
# @START UNCOMMENT SECTION
#target_link_libraries(my_app googletest libcurl)
# @END UNCOMMENT SECTION
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer  -fsanitize=address -fsanitize=address  -fsanitize=undefined -lubsan -g")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fsanitize=address  -fsanitize=undefined -lubsan -g")

file(GLOB_RECURSE MY_APP_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
add_executable(tests ${MY_APP_TEST_SRC})
check_pie_supported(OUTPUT_VARIABLE output LANGUAGES CXX)
set_property(TARGET tests PROPERTY POSITION_INDEPENDENT_CODE TRUE)
if(NOT CMAKE_CXX_LINK_PIE_SUPPORTED)
  message(WARNING "PIE is not supported at link time: ${output}.\n"
                  "PIE link options will not be passed to linker.")
endif()
target_link_libraries(tests my_app_src)
target_link_libraries(tests ${LIBMPC_PATH})
if (SQLite3_FOUND)
  include_directories(${SQLite3_INCLUDE_DIRS})
  target_link_libraries (tests ${SQLite3_LIBRARIES})
endif (SQLite3_FOUND)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(tests ${GTEST_LIBRARIES})
# @START UNCOMMENT SECTION
#target_link_libraries(tests googletest libcurl)
# @END UNCOMMENT SECTION
target_link_libraries(tests ${CONAN_LIBS})
#Enable warning for specified compiler
target_compile_options(tests PUBLIC
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wfatal-errors -pedantic -fPIC -fstack-protector-all  >
)

#if(CMAKE_BUILD_TYPE STREQUAL DEBUG)
#   target_sources(hello PRIVATE helper_debug.cpp)
#else()
#   target_sources(hello PRIVATE helper_release.cpp)
#endif()
cmake_minimum_required(VERSION 3.16)
project(MyApplication)
set(CMAKE_CXX_STANDARD 11)
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
include(FindHDF5)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#Set sanitizer flags
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer  -fsanitize=address -g")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -g")

#Set libmpc path
set (LIBMPC_PATH "/usr/lib/x86_64-linux-gnu/libmpc.so.3")

#Check if libCurl is installed on the system.
if(NOT CURL_FOUND)
  message(WARNING "libCurl is not installed on the system.\n")
else()
  message(STATUS "libCurl version: "${CURL_VERSION_STRING})
endif()
#Check if googletest is installed on the system.
if(NOT GTEST_FOUND)
  message(WARNING "googletests is not installed on the system.\n")
else()
  message(STATUS "googltests found in: "${GTEST_INCLUDE_DIRS})
endif()
#Check if HDF5 is installed on the system.
if(NOT HDF5_FOUND)
  message(WARNING "HDF5 is not installed on thesystem.\n"${HDF5_FOUND}${HDF5_VERSION})
else()
  message(STATUS "HDF5 version: "${HDF5_VERSION})
endif()

#Build source lib.
file(GLOB_RECURSE MY_APP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp)
file(GLOB_RECURSE MY_APP_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/headers/*.h)
add_library(my_app_src SHARED ${MY_APP_SRC} ${MY_APP_HEADERS})
target_include_directories(my_app_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source)
target_include_directories(my_app_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)
set_target_properties(my_app_src PROPERTIES LINKER_LANGUAGE CXX)

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
# @START UNCOMMENT SECTION
#target_link_libraries(my_app googletest libcurl)
# @END UNCOMMENT SECTION

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
# @START UNCOMMENT SECTION
#target_link_libraries(tests googletest libcurl)
# @END UNCOMMENT SECTION
target_link_libraries(tests ${CONAN_LIBS})

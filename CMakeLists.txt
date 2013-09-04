cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(bomberman)
set(VERSION "0.1")
add_definitions(-D"VERSION=\\"${VERSION}\\"")

# CMAKE_CURRENT_LIST_DIR cmake 2.6 compatibility
if(${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} EQUAL 6)
	get_filename_component(CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)
endif(${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} EQUAL 6)

option(USE_STATIC_LIBS "Don't use shared libraries" OFF)
if(USE_STATIC_LIBS)
	if (__COMPILER_GNU)
		set(CMAKE_C_LINK_FLAGS "-static-libgcc")
	endif()
	message(STATUS "Link to static libraries: ON")
else()
	message(STATUS "Link to static libraries: OFF")
endif()

# default build type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

# gcc compile flags
set(WARNS_FLAGS 		   "-Wall -Wno-unused-result -Wno-sign-compare ")
set(CMAKE_CXX_FLAGS		   "-std=c++11 ${CMAKE_CXX_FLAGS} ${WARNS_FLAGS} -pipe")
set(CMAKE_CXX_FLAGS_DEBUG	   "-O0 -g3 -ggdb")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O1 -g3 -ggdb -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE	   "-O2")
set(CMAKE_CXX_FLAGS_PERFORMANCE	   "-Ofast -mmmx -msse -msse2")
set(CMAKE_CXX_FLAGS_MINSIZEREL	   "-Os")

message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})
add_definitions(-D"BUILD_TYPE=\\\"${CMAKE_BUILD_TYPE}\\\"")

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -Wl,--no-as-needed")
	message(STATUS "Debug information: ON")
else()
	message(STATUS "Debug information: OFF")
	set(bomberman_DEFINITIONS ${bomberman_DEFINITIONS} -DNDEBUG) # NDEBUG disable asserations
	set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -Wl,--as-needed -Wl,-s") # strip all debug information
endif()

add_definitions(${bomberman_DEFINITIONS})
include(net/CMakeLists.txt)
include(util/CMakeLists.txt)
include(server/CMakeLists.txt)

add_executable(${PROJECT_NAME} ${net_SOURCES} ${server_SOURCES})
target_link_libraries(${PROJECT_NAME} ${net_LIBRARIES})


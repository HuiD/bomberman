#
# Copyright (c) 2013 Ahmed Samy <f.fallen45@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

set(net_LIBRARIES "")
set(net_DEFINITIONS "")
set(net_INCLUDE_DIRS "${CMAKE_CXXURRENT_LIST_DIR}/..")
set(net_SOURCES ${csnippets_SOURCES}
	${CMAKE_CURRENT_LIST_DIR}/connection.cpp
	${CMAKE_CURRENT_LIST_DIR}/listener.cpp
	${CMAKE_CURRENT_LIST_DIR}/inputmessage.cpp
	${CMAKE_CURRENT_LIST_DIR}/outputmessage.cpp
)

# default build type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

# gcc compile flags
set(WARNS_FLAGS 		   "-Wall -Wno-unused-result -Wno-sign-compare ")
set(CMAKE_CXX_FLAGS		    "${CMAKE_C_FLAGS} ${WARNS_FLAGS} ${ARCH_FLAGS} -pipe -include ${net_PRE_INCLUDE}")
set(CMAKE_CXX_FLAGS_DEBUG		    "-O0 -g3 -ggdb")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO    "-O1 -g3 -ggdb -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE	    "-O2")
set(CMAKE_CXX_FLAGS_PERFORMANCE	    "-Ofast -mmmx -msse -msse2")
set(CMAKE_CXX_FLAGS_MINSIZEREL	    "-Os")

message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})
add_definitions(-D"BUILD_TYPE=\\\"${CMAKE_BUILD_TYPE}\\\"")
message(STATUS "Build commit: ${BUILD_COMMIT}")
add_definitions(-D"BUILD_COMMIT=\\\"${BUILD_COMMIT}\\\"")
message(STATUS "Build revision: ${BUILD_REVISION}")
add_definitions(-D"BUILD_REVISION=\\\"${BUILD_REVISION}\\\"")

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -mthreads")
	set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--large-address-aware") # strip all debug information
	set(net_LIBRARIES "-lws2_32")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--no-as-needed")
	message(STATUS "Debug information: ON")
else()
	message(STATUS "Debug information: OFF")
	set(net_DEFINITIONS ${csnippets_DEFINITIONS} -DNDEBUG) # NDEBUG disable asserations
	set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--as-needed -Wl,-s") # strip all debug information
endif()

set(REQUIRED_BOOST_COMPONENTS system)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ${USE_STATIC_LIBS})
find_package(Boost 1.48.0 COMPONENTS ${REQUIRED_BOOST_COMPONENETS} REQUIRED)

set(net_LIBRARIES ${net_LIBRARIES}
	${Boost_LIBRARIES}
)
set(net_INCLUDE_DIRS ${net_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)


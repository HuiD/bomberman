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
set(net_SOURCES ${net_SOURCES}
	${CMAKE_CURRENT_LIST_DIR}/connection.cpp
	${CMAKE_CURRENT_LIST_DIR}/listener.cpp
	${CMAKE_CURRENT_LIST_DIR}/server.cpp
	${CMAKE_CURRENT_LIST_DIR}/inputmessage.cpp
	${CMAKE_CURRENT_LIST_DIR}/outputmessage.cpp
	${CMAKE_CURRENT_LIST_DIR}/protocol.cpp
	${CMAKE_CURRENT_LIST_DIR}/protocolchat.cpp
	${CMAKE_CURRENT_LIST_DIR}/protocolgame.cpp
)

set(REQUIRED_BOOST_COMPONENTS system)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ${USE_STATIC_LIBS})
find_package(Boost COMPONENTS ${REQUIRED_BOOST_COMPONENTS} REQUIRED)

set(net_LIBRARIES ${net_LIBRARIES}
	${Boost_LIBRARIES}
)
set(net_INCLUDE_DIRS ${net_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)

if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthreads")
	set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -Wl,--large-address-aware")
	set(net_LIBRARIES "${net_LIBRARIES} -lws2_32")
else()
	set(net_LIBRARIES ${net_LIBRARIES} -pthread)
endif()


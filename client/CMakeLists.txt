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

set(client_LIBRARIES "")
set(client_DEFINITIONS "")
set(client_SOURCES ${client_SOURCES}
	# GUI
	${CMAKE_CURRENT_LIST_DIR}/gui/mainwindow.cpp
	${CMAKE_CURRENT_LIST_DIR}/main.cpp

	# OpenGL
	${CMAKE_CURRENT_LIST_DIR}/opengl/texture.cpp
	${CMAKE_CURRENT_LIST_DIR}/opengl/texturemanager.cpp
	${CMAKE_CURRENT_LIST_DIR}/opengl/shader.cpp
	${CMAKE_CURRENT_LIST_DIR}/opengl/shaderprogram.cpp
)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SOIL REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
set(client_LIBRARIES ${client_LIBRARIES}
	${wxWidgets_LIBRARIES}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARY}
	${SOIL_LIBRARY}
	${SDL2_LIBRARY}
)


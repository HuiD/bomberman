set(server_SOURCES ${server_SOURCES}
	${CMAKE_CURRENT_LIST_DIR}/server.cpp
	${CMAKE_CURRENT_LIST_DIR}/chatserver.cpp
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

include_directories("${CMAKE_CURRENT_LIST_DIR}/..")

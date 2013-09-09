set(game_SOURCES ${server_SOURCES}
	${CMAKE_CURRENT_LIST_DIR}/game.cpp
	${CMAKE_CURRENT_LIST_DIR}/map.cpp
	${CMAKE_CURRENT_LIST_DIR}/player.cpp
	${CMAKE_CURRENT_LIST_DIR}/tile.cpp
	${CMAKE_CURRENT_LIST_DIR}/item.cpp
)

include_directories("${CMAKE_CURRENT_LIST_DIR}/..")

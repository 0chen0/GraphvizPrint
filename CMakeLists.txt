cmake_minimum_required(VERSION 2.8)
project( GraphvizPrintTree )

function(LOG description)
	message(STATUS "+----------------------------- ${description} ")
	foreach(arg IN LISTS ARGN)
		message(STATUS "|    ${arg} : ${${arg}}")
	endforeach()
	message(STATUS "+--------------------------------------------------------------------------------\n")
endfunction(LOG)
# LOG(${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} )

set(PROJ_SOURCES
	example.cpp
	GraphvizPrintTree.hpp
)

add_executable(${PROJECT_NAME} ${PROJ_SOURCES})
# .\build\GraphvizPrintTree.exe && dot -Tpng .\print_tree.gv -o print_tree.png
cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC)
set(INCL)
set(LINKLIBS)
set(COMPILE_OPTION)

project(ClearSenseProcessor)

set(PATH_PROCESSOR  ${CMAKE_CURRENT_LIST_DIR}/../../../../../)
include(${PATH_PROCESSOR}/ALGO.cmake)

if(ANDROID)
	
endif()

add_library(${CMAKE_PROJECT_NAME} SHARED
		native-ALGO.cpp
		${SRC}
		)
target_include_directories(${PROJECT_NAME}    PRIVATE
		${CMAKE_CURRENT_LIST_DIR}
		${INCL}
		${PATH_PROCESSOR}/include
)
target_link_libraries(
		${CMAKE_PROJECT_NAME}
		android
		log
		${LINKLIBS}
)
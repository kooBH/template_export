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

set(PATH_ASSET ${${CMAKE_CURRENT_LIST_DIR}/../assets})


list(APPEND COMPILE_OPTION
		# openMP
		#	  -fopenmp
		# debugging
		-g
		# -O3 : maximize performace
		# -O2 : maximize performance as long as not increasing size of executable
		# -O1 : minimize compile time and others are secondary
		# -Os : minimize size of executable
		-O3
)

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
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )
set_target_properties(${PROJECT_NAME} PROPERTIES  CXX_STANDARD 17)
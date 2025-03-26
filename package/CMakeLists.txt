cmake_minimum_required(VERSION 3.10)
project(test)

set(LINKLIBS)
set(COMPILE_OPTION)
set(SRC)
set(INCL)

list(APPEND INCL
	${CMAKE_CURRENT_LIST_DIR}
)

if(NOT MSVC)
	list(APPEND LINKLIBS
	# <math.h>
	m
	# openMP
    -fopenmp
	)
else()
	list(APPEND LINKLIBS
    
	)	
endif()


if(NOT MSVC)
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
	
else()
list(APPEND COMPILE_OPTION
# Visual Studio uses '/' for compile option

	  /openmp
	  # /MP - compiled in mult-process : faster build time
	  /MP
	)
endif()

display_elements(COMPILE_OPTION "${COMPILE_OPTION}")
display_elements(LINKLIBS "${LINKLIBS}")

add_executable(${PROJECT_NAME} 
	test.cpp
	WAV.cpp
	${SRC}
	)

target_include_directories(${PROJECT_NAME}	PRIVATE	${INCL}  )
target_link_libraries(${PROJECT_NAME} ${LINKLIBS})
if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )
else()
	target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES  CXX_STANDARD 17)



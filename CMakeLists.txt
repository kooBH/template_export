# CMAKE version of Ubuntu 16.04 LTS is 3.5.
cmake_minimum_required(VERSION 3.5)
project(library_name)

#find_package(MKL CONFIG REQUIRED)

set(LINKLIBS)
set(COMPILE_OPTION)
set(SRC)
set(INCL)

include(${CMAKE_CURRENT_LIST_DIR}/lib/WAV/WAV.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/lib/STFT/cpp/STFT_cpp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/lib/ExpirationTimer/chrono/exp_chrono.cmake)

macro(display_elements
	DISPLAY_MESSAGE
	LIST_TO_DISPLAY)
    message("[ ${DISPLAY_MESSAGE} ]")
    foreach(_DISPLAY_ELEMENT ${LIST_TO_DISPLAY})
		message(STATUS ${_DISPLAY_ELEMENT})
    endforeach()
endmacro()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/package/include)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/package/bin)

####### COPY ##########

# copy lib files
file(COPY 
	# TODO
DESTINATION 
	${CMAKE_CURRENT_LIST_DIR}/package/include
)
# copy lib files
file(COPY 
	# TODO
	DESTINATION 
	${CMAKE_CURRENT_LIST_DIR}/package/bin/
)

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/build/Release/mpAB.dll)
file(COPY 
	# TODO
	${CMAKE_CURRENT_LIST_DIR}/build/Release/.lib
	${CMAKE_CURRENT_LIST_DIR}/build/Release/.dll
	DESTINATION 
	${CMAKE_CURRENT_LIST_DIR}/package/bin/)
endif()

file(COPY
	${CMAKE_CURRENT_LIST_DIR}/test.cpp
	${CMAKE_CURRENT_LIST_DIR}/README.md
	
	DESTINATION
${CMAKE_CURRENT_LIST_DIR}/package/)

#############################


list(APPEND SRC
)

list(APPEND INCL
	${CMAKE_CURRENT_LIST_DIR}/package/include
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



add_library(${PROJECT_NAME} SHARED ${SRC})
add_executable(test_${PROJECT_NAME} 
	${CMAKE_CURRENT_LIST_DIR}/test.cpp
	${CMAKE_CURRENT_LIST_DIR}/lib/WAV/WAV.cpp
	)


target_include_directories(${PROJECT_NAME}	PRIVATE	${INCL}  )
target_include_directories(test_${PROJECT_NAME}	PRIVATE	${INCL}  )


target_link_libraries(${PROJECT_NAME} ${LINKLIBS})
if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} /D_EXPORT_ )
	target_link_libraries(test_${PROJECT_NAME} ${LINKLIBS} ${CMAKE_CURRENT_LIST_DIR}/build/Debug/${PROJECT_NAME}.lib)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} -D_EXPORT_ )
	target_link_libraries(test_${PROJECT_NAME} ${LINKLIBS} ${CMAKE_CURRENT_LIST_DIR}/build/${PROJECT_NAME}.so)
endif()
target_compile_options(test_${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )

set_target_properties(${PROJECT_NAME} PROPERTIES  CXX_STANDARD 17)
set_target_properties(test_${PROJECT_NAME} PROPERTIES  CXX_STANDARD 11 )



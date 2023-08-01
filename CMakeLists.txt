# CMAKE version of Ubuntu 16.04 LTS is 3.5.
cmake_minimum_required(VERSION 3.5)
project(library_name)

#find_package(MKL CONFIG REQUIRED)

set(LINKLIBS)
set(COMPILE_OPTION)
set(SRC)
set(INCL)

include(lib/WAV/WAV.cmake)
include(lib/STFT/cpp/STFT_cpp.cmake)  
include(lib/ExpirationTimer/chrono/exp_chrono.cmake)  
  
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

list(APPEND SRC	
	# TODO : Add path to algorithm source here.
	#

)

	
list(APPEND INCL
	src
)

include (submodule/WAV/WAV.cmake)
include (submodule/STFT/cpp/STFT_cpp.cmake)

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


message("-- using MPDLL")
message("-- copying headers")
# do the copying
set(DLL_HEADERS ${SRC})
list(FILTER DLL_HEADERS INCLUDE REGEX "^.*\.(h|H)$")
file(GLOB RM_FILES ${CMAKE_CURRENT_LIST_DIR}/package/include/*)
list(LENGTH RM_FILES RM_LENS)
if(RM_LENS EQUAL 0)
else()
	file(REMOVE ${RM_FILES})
endif()

file(COPY 
${DLL_HEADERS}   
${CMAKE_CURRENT_LIST_DIR}/lib/WAV/WAV.h
${CMAKE_CURRENT_LIST_DIR}/lib/WAV/WAV.cpp
DESTINATION
${CMAKE_CURRENT_LIST_DIR}/package/include/
)


file(COPY 
${CMAKE_CURRENT_LIST_DIR}/test.cpp
${CMAKE_CURRENT_LIST_DIR}/README.md
DESTINATION
${CMAKE_CURRENT_LIST_DIR}/package/
)

file(COPY 
${CMAKE_CURRENT_LIST_DIR}/build/Release/${PROJECT_NAME}.lib
${CMAKE_CURRENT_LIST_DIR}/build/Release/${PROJECT_NAME}.dll
DESTINATION
${CMAKE_CURRENT_LIST_DIR}/package/
)

add_executable(${PROJECT_NAME}_test ${SRC} ${CMAKE_CURRENT_LIST_DIR}/test.cpp)
target_include_directories(${PROJECT_NAME}_test	PRIVATE	${CMAKE_CURRENT_LIST_DIR}/package/include/  )
#target_link_libraries(${PROJECT_NAME}_test ${LINKLIBS}  ${CMAKE_CURRENT_LIST_DIR}/build/RelWithDebInfo/${PROJECT_NAME}.lib )
target_link_libraries(${PROJECT_NAME}_test ${LINKLIBS}  ${CMAKE_CURRENT_LIST_DIR}/build/Release/${PROJECT_NAME}.lib )
target_compile_options(${PROJECT_NAME}_test PRIVATE ${COMPILE_OPTION}  )
set_target_properties(${PROJECT_NAME}_test PROPERTIES  CXX_STANDARD 14 )


add_library(${PROJECT_NAME} SHARED ${SRC})
target_include_directories(${PROJECT_NAME}	PRIVATE	${INCL}  )
target_link_libraries(${PROJECT_NAME} ${LINKLIBS} )
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )
set_target_properties(${PROJECT_NAME} PROPERTIES  CXX_STANDARD 14 )



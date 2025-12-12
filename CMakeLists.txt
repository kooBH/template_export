cmake_minimum_required(VERSION 3.10)
project(MYLIB)

#find_package(MKL CONFIG REQUIRED)

set(LINKLIBS)
set(COMPILE_OPTION)
set(SRC_ALGO)
set(SRC)
set(INCL)

include(${CMAKE_CURRENT_LIST_DIR}/lib/WAV/WAV.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/lib/STFT/cpp/STFT_cpp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/lib/ExpirationTimer/chrono/exp_chrono.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/lib/RtAudioWrapper/RtAudio.cmake)

macro(display_elements
	DISPLAY_MESSAGE
	LIST_TO_DISPLAY)
    message("[ ${DISPLAY_MESSAGE} ]")
    foreach(_DISPLAY_ELEMENT ${LIST_TO_DISPLAY})
		message(STATUS ${_DISPLAY_ELEMENT})
    endforeach()
endmacro()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/package/bin)

if(APPLE)
 set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
 set(CMAKE_SKIP_BUILD_RPATH FALSE)
 set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
 set(CMAKE_INSTALL_RPATH "@loader_path")

endif()

####### COPY ##########

# Copy dependency files
file(COPY 
	${CMAKE_CURRENT_LIST_DIR}/ALGO.h
	${CMAKE_CURRENT_LIST_DIR}/lib/WAV/WAV.h
	${CMAKE_CURRENT_LIST_DIR}/lib/WAV/WAV.cpp	

DESTINATION 
	${CMAKE_CURRENT_LIST_DIR}/package
)

# Copy  other dependency binaries
file(COPY 
	# TODO
	
	DESTINATION 
	${CMAKE_CURRENT_LIST_DIR}/package/bin/
)

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/build/Release/${PROJECT_NAME}.dll)
file(COPY 
	# TODO
	${CMAKE_CURRENT_LIST_DIR}/build/Release/${PROJECT_NAME}.dll
	DESTINATION 
	${CMAKE_CURRENT_LIST_DIR}/package/bin/)
endif()

# copy docs
file(COPY

	${CMAKE_CURRENT_LIST_DIR}/README.md
	
	DESTINATION
${CMAKE_CURRENT_LIST_DIR}/package/)

#############################

list(APPEND SRC_ALGO
	src/ALGO_impl.cpp
	src/ALGO_wrap.cpp
	src/ALGO_decl.h
	ALGO.h
)

list(APPEND INCL
	${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/src
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


add_library(${PROJECT_NAME} SHARED ${SRC_ALGO})
add_executable(test_${PROJECT_NAME} 
	${SRC}
	${CMAKE_CURRENT_LIST_DIR}/test.cpp
	)


target_include_directories(${PROJECT_NAME}	PRIVATE	${INCL}  )
target_include_directories(test_${PROJECT_NAME}	PRIVATE	${INCL}  )
if(APPLE)
	set_target_properties(${PROJECT_NAME} PROPERTIES
		INSTALL_NAME_DIR "@rpath"
	)
endif()

target_link_libraries(${PROJECT_NAME} ${LINKLIBS})
if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} /D_EXPORT_ )
	target_link_libraries(test_${PROJECT_NAME} ${LINKLIBS} 
	debug ${CMAKE_CURRENT_LIST_DIR}/build/Debug/${PROJECT_NAME}.lib
    optimized ${CMAKE_CURRENT_LIST_DIR}/build/Release/${PROJECT_NAME}.lib
	
	${CMAKE_CURRENT_LIST_DIR}/build/Debug/${PROJECT_NAME}.lib)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} -D_EXPORT_ )
	target_link_libraries(test_${PROJECT_NAME} ${LINKLIBS} ${CMAKE_CURRENT_LIST_DIR}/build/lib${PROJECT_NAME}.so)
endif()
target_compile_options(test_${PROJECT_NAME} PRIVATE ${COMPILE_OPTION} )

set_target_properties(${PROJECT_NAME} PROPERTIES  CXX_STANDARD 17)
set_target_properties(test_${PROJECT_NAME} PROPERTIES  CXX_STANDARD 11 )





include(${CMAKE_CURRENT_LIST_DIR}/lib/WAV/WAV.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/lib/STFT/cpp/STFT_cpp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/lib/ExpirationTimer/chrono/exp_chrono.cmake)

list(APPEND SRC
   ${CMAKE_CURRENT_LIST_DIR}/ALGO.h
   ${CMAKE_CURRENT_LIST_DIR}/src/ALGO_decl.h
   ${CMAKE_CURRENT_LIST_DIR}/src/ALGO_impl.cpp
   ${CMAKE_CURRENT_LIST_DIR}/src/ALGO_wrap.cpp
  )
list(APPEND INCL
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src
 )
  
if(ANDROID)
endif()
  
list(APPEND LINKLIBS
  )
  
if(MSVC)
  list(APPEND COMPILE_OPTION
    )
else()
  list(APPEND COMPILE_OPTION
    )
endif()

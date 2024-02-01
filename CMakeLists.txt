include(./.env.cmake OPTIONAL RESULT_VARIABLE LOCAL_ENV)
message(STATUS "Local .env.cmake: ${LOCAL_ENV}")
 
cmake_minimum_required(VERSION 3.11.0)
 
set(NAME Moryx_Engine)
 
message(STATUS "using ${CMAKE_GENERATOR}")
if (CMAKE_GENERATOR STREQUAL "MinGW Makefiles")
    if (NOT MINGW_PATH) 
      message(FATAL_ERROR "MINGW_PATH not set in .env.cmake")
    endif()
    set(USE_MINGW "True")
    set(CMAKE_C_COMPILER ${MINGW_PATH}/bin/gcc.exe)
    set(CMAKE_CXX_COMPILER  ${MINGW_PATH}/bin/g++.exe)
endif()
 
project(${NAME} VERSION 0.23.0)
 
include_directories(include)
 
# 3. set fast noise paths

set(FASTNOISE2_NOISETOOL OFF CACHE BOOL "Build Noise Tool" FORCE) #example if don't need the graph tool
add_subdirectory(lib/FastNoise2)
#add_library(${PROJECT_NAME} ${SOURCES})

# If TINYOBJ_PATH not specified in .env.cmake, try fetching from git repo
if (NOT TINYOBJ_PATH)
  message(STATUS "TINYOBJ_PATH not specified in .env.cmake, using include/tinyobjloader")
  set(TINYOBJ_PATH include/tinyobjloader)
endif()
 
set(STB_IMAGE_PATH include/STB_Image)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
 
add_executable(${PROJECT_NAME} ${SOURCES})
 
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
 
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
 
if (WIN32)
  message(STATUS "CREATING BUILD FOR WINDOWS")
 
  if (USE_MINGW)
    target_include_directories(${PROJECT_NAME} PUBLIC
      ${MINGW_PATH}/include
    )
    target_link_directories(${PROJECT_NAME} PUBLIC
      ${MINGW_PATH}/lib
    )
  endif()
 
  target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${TINYOBJ_PATH}
    ${FASTNOISE2_NOISETOOL}
    ${STB_IMAGE_PATH}
    )
 
  target_link_directories(${PROJECT_NAME} PUBLIC
    ${FASTNOISE2_NOISETOOL}
  )
 
  target_link_libraries(${PROJECT_NAME} FastNoise)
elseif (UNIX)
    message(STATUS "CREATING BUILD FOR UNIX")
    target_include_directories(${PROJECT_NAME} PUBLIC
      ${PROJECT_SOURCE_DIR}/src
      ${TINYOBJ_PATH}
      ${STB_IMAGE_PATH}
      ${FASTNOISE2_NOISETOOL}
    )
    target_link_libraries(${PROJECT_NAME} FastNoise)
endif()
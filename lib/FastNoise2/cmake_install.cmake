# Install script for directory: /mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/libFastNoise.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FastSIMD" TYPE FILE FILES
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastSIMD/FastSIMD.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastSIMD/FastSIMD_Config.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastSIMD/FastSIMD_Export.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastSIMD/FunctionList.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastSIMD/InlInclude.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastSIMD/SIMDTypeList.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FastNoise" TYPE FILE FILES
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/FastNoise.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/FastNoise_C.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/FastNoise_Config.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/FastNoise_Export.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/Metadata.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/SmartNode.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FastNoise/Generators" TYPE FILE FILES
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/Generators/BasicGenerators.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/Generators/Blends.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/Generators/Cellular.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/Generators/DomainWarp.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/Generators/DomainWarpFractal.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/Generators/Fractal.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/Generators/Generator.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/Generators/Modifiers.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/Generators/Perlin.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/Generators/Simplex.h"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/../include/FastNoise/Generators/Value.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FastNoise2" TYPE FILE FILES
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/generated/FastNoise2Config.cmake"
    "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/generated/FastNoise2ConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FastNoise2/FastNoise2Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FastNoise2/FastNoise2Targets.cmake"
         "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/CMakeFiles/Export/lib/cmake/FastNoise2/FastNoise2Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FastNoise2/FastNoise2Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FastNoise2/FastNoise2Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FastNoise2" TYPE FILE FILES "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/CMakeFiles/Export/lib/cmake/FastNoise2/FastNoise2Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FastNoise2" TYPE FILE FILES "/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/CMakeFiles/Export/lib/cmake/FastNoise2/FastNoise2Targets-noconfig.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/mnt/c/Users/zachm/OneDrive/Desktop/Moryx_engine/lib/FastNoise2/src/cmake_install.cmake")

endif()


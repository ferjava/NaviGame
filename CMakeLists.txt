# /****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).
#
# https://axmol.dev/
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.22...4.1)

set(APP_NAME NaviGame)
project(${APP_NAME}
VERSION 0.0.01)
#NOTE: Mis Cambios
#->
# En tu CMakeLists.txt
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configurando AddressSanitizer para Debug...")
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g)
    add_link_options(-fsanitize=address)
endif()
include(FetchContent)

FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG v3.13.0 # Aquí puedes poner la versión o el hash que desees
)
FetchContent_MakeAvailable(entt)

set(AX_ENABLE_PCH ON CACHE BOOL "Enable  precompiled headers" FORCE)
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/External/entt/src/)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/Version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/Generated/Version.h"
)
#<-
if(XCODE)
    set(CMAKE_XCODE_GENERATE_TOP_LEVEL_PROJECT_ONLY TRUE)
endif()

set(_is_axmol_embed FALSE)
set(AX_USE_PREBUILT FALSE)

set(CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
)

# NOTE: The order of the cmake module "include(AXGame...)" statements matters
include(AXGameEngineOptions)
include(AXGameEngineSetup)

# The common cross-platforms source files and header files
file(GLOB_RECURSE GAME_HEADER
  Source/*.h Source/*.hpp
)

file(GLOB_RECURSE GAME_SOURCE
  Source/*.cpp Source/*.c
)

set(GAME_INC_DIRS
  "${CMAKE_CURRENT_SOURCE_DIR}/Source"
)

set(content_folder
  "${CMAKE_CURRENT_SOURCE_DIR}/Content"
)

if(APPLE)
    ax_mark_multi_resources(common_content_files RES_TO "Resources" FOLDERS ${content_folder})
elseif(WINDOWS)
    ax_mark_multi_resources(common_content_files RES_TO "Content" FOLDERS ${content_folder})
endif()

include(AXGameSourceSetup)

# mark app complie info and libs info
set(APP_SOURCES
  ${GAME_HEADER}
  ${GAME_SOURCE}
)

include(AXGameTargetSetup)
#NOTE: Mis Añadidos

# ... después de definir tu APP_NAME ...
target_link_libraries(${APP_NAME} EnTT::EnTT)

# Asegúrate de incluir la carpeta donde se genera el archivo
target_include_directories(${APP_NAME} PRIVATE
"${CMAKE_CURRENT_BINARY_DIR}/Generated")
#<---


# mark app resources, resource will be copy auto after mark
ax_setup_app_config(${APP_NAME})
# Add any libraries you need to link to the project after this point

# Default Platform-specific setup
include(AXGamePlatformSetup)

# Make sure the AXGameFinalSetup is included at the end of this file
include(AXGameFinalSetup)

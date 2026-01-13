# Copyright(c)	2024 Christopher Taylor
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 3.29)

project(tt_edsl)

set(CMAKE_CXX_STANDARD 17)

include("./cmake")

option(ENABLE_BERKELEYDB_SUPPORT "add berkeleydb support" OFF)
option(BUILD_EXAMPLES "build example programs" OFF)

if(FALSE)

if(DEFINED TT_METAL_DIR)
  set(TT_METAL_DIR_STRLEN 0)
  string(LENGTH "${TT_METAL_DIR}" TT_METAL_DIR_STRLEN)

  if( TT_METAL_DIR_STRLEN LESS 1 )
    message(FATAL_ERROR "Set -DTT_METAL_DIR")
  endif()

  if(EXISTS "${TT_METAL_DIR}")
    message(STATUS "tt-metal found! ${TT_METAL_DIR}")
  else()
    message(FATAL_ERROR "Invalid -DTT_METAL_DIR=${TT_METAL_DIR}")
  endif()
endif()

set(TT_METAL_INCDIR "${TT_METAL_DIR}/include")
set(TT_METAL_LIBDIR "${TT_METAL_DIR}/lib")

endif()

find_package(fmt)

if(ENABLE_BERKELEYDB_SUPPORT)
  find_package(BerkeleyDB)

  if(NOT BerkeleyDB_FOUND)
    if(NOT DEFINED BerkeleyDB_LIBRARIES)
      set(BerkeleyDB_LIBRARIES libdb.dylib libdb_cxx.dylib)
    endif()

    if(NOT DEFINED BerkeleyDB_ROOT_DIR)
      message(FATAL_ERROR "BerkeleyDB support enabled; cmake configuration not found and -DBerkeleyDB_ROOT_DIR not defined")
    endif()
  endif()
endif()

add_subdirectory(include)

if(BUILD_EXAMPLES)
   add_subdirectory(examples)
endif()

# Copyright(c)	2024 Christopher Taylor
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

set(EXAMPLE_FILES
  reader_unary.cpp
)

set(EXAMPLE_INCLUDES
   ../../include
   fmt::fmt
)

set(EXAMPLE_LIBRARIES
   fmt::fmt
)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(reader_unary
  ${EXAMPLE_FILES}
)

target_compile_definitions(reader_unary PRIVATE -DUSE_METALLIUM)

if(ENABLE_BERKELEYDB_SUPPORT)

  target_compile_definitions(reader_unary PRIVATE -DENABLE_BERKELEY_DB_SUPPORT)

  set(EXAMPLE_INCLUDES
    ${EXAMPLE_INCLUDES}
    ${BerkeleyDB_ROOT_DIR}/include
  )

  set(EXAMPLE_LIBRARIES
    ${EXAMPLE_LIBRARIES}
    ${BerkeleyDB_LIBRARIES}
  )
  
  target_link_directories(reader_unary PRIVATE
    ${BerkeleyDB_ROOT_DIR}/lib
  )

endif()

target_include_directories(reader_unary PRIVATE
   ${EXAMPLE_INCLUDES}
)

target_link_libraries(reader_unary PRIVATE
   ${EXAMPLE_LIBRARIES}
)

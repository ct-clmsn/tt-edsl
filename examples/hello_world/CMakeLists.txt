# Copyright(c)	2024 Christopher Taylor
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

set(EXAMPLE_FILES
  hello_world.cpp
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

add_executable(hello_world
  ${EXAMPLE_FILES}
)

target_compile_definitions(hello_world PRIVATE -DUSE_METALLIUM)

if(ENABLE_BERKELEYDB_SUPPORT)

  target_compile_definitions(hello_world PRIVATE -DENABLE_BERKELEY_DB_SUPPORT)

  set(EXAMPLE_INCLUDES
    ${EXAMPLE_INCLUDES}
    ${BerkeleyDB_ROOT_DIR}/include
  )

  set(EXAMPLE_LIBRARIES
    ${EXAMPLE_LIBRARIES}
    ${BerkeleyDB_LIBRARIES}
  )
  
  target_link_directories(hello_world PRIVATE
    ${BerkeleyDB_ROOT_DIR}/lib
  )

endif()

target_include_directories(hello_world PRIVATE
   ${EXAMPLE_INCLUDES}
)

target_link_libraries(hello_world PRIVATE
   ${EXAMPLE_LIBRARIES}
)

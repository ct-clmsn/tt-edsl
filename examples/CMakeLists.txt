# Copyright(c)	2024 Christopher Taylor
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

set(example_DIRECTORIES
  test
  loopback
)

#  hello_world
#  reader_unary

foreach(example_DIR IN LISTS example_DIRECTORIES)
  add_subdirectory(${example_DIR})
endforeach()

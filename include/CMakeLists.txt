# Copyright(c)	2024 Christopher Taylor
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

set(TT_EDSL_FILES
  recursive_wrapper.hpp
  variant.hpp
  dsl.hpp
  api.hpp
  tt.hpp
)

set(TT_EDSL_INCLUDES
   .
   fmt::fmt
)

add_library(tt_edsl INTERFACE)

if(ENABLE_BERKELEYDB_SUPPORT)

  set(TT_EDSL_INCLUDES
    ${TT_EDSL_INCLUDES}
    ${BerkeleyDB_ROOT_DIR}/include
  )

  set(TT_EDSL_FILES
    ${TT_EDSL_FILES}
    cache.hpp
  )

  add_definitions(tt_edsl -DENABLE_BERKELEY_DB_SUPPORT)

endif()

target_include_directories(tt_edsl INTERFACE
  ${TT_EDSL_INCLUDES}
)

install(
  FILES ${TT_EDSL_FILES}
  DESTINATION include/tt_edsl
)

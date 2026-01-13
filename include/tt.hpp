/*
* Copyright(c)	2024 Christopher Taylor

* SPDX-License-Identifier: BSL-1.0
* Distributed under the Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once
#ifndef __TT_EDSL_TTMODEL_HPP__
#define __TT_EDSL_TTMODEL_HPP__

#include "dsl.hpp"

using namespace tt::dsl;

#if defined(USE_METALLIUM)

#include "api.hpp"

using namespace tt::api::kernel::kernel_argument;
using namespace tt::api::kernel::circular_buffer;
using namespace tt::api::kernel::data_movement;
using namespace tt::api::kernel::dataflow;
using namespace tt::api::kernel::compute;

#endif

#define host_location() std::string{__FILE__}

#if defined(ENABLE_BERKELEY_DB_SUPPORT)

#include "cache.hpp"

#endif

#endif

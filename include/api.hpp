/*
* Copyright(c)	2024 Christopher Taylor

* SPDX-License-Identifier: BSL-1.0
* Distributed under the Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once
#ifndef __TT_EDSL_API_BASE_HPP__
#define __TT_EDSL_API_BASE_HPP__

#include "dsl.hpp"

using namespace tt::dsl;

namespace tt { namespace api { namespace kernel {

static inline function_decl DPRINT_decl =
   function_decl{"DPRINT", std::vector<variable_type>{}};

static inline function_call DPRINT =
   function_call{DPRINT_decl, {}};

namespace kernel_argument {

static inline function_decl get_arg_addr_decl =
   function_decl{"get_arg_addr", std::vector<variable_type>{scalar<i32>{}} };

static inline function_call get_arg_addr =
   function_call{get_arg_addr_decl, {}};

static inline function_decl get_arg_val_decl =
   function_decl{"get_arg_val", std::vector<variable_type>{scalar<i32>{}} };

static inline function_call get_arg_val =
   function_call{get_arg_val_decl, {}};

static inline function_decl get_common_arg_addr_decl =
   function_decl{"get_common_arg_addr", std::vector<variable_type>{scalar<i32>{}} };

static inline function_call get_common_arg_addr =
   function_call{get_common_arg_addr_decl, {}};

static inline function_decl get_common_arg_val_decl =
   function_decl{"get_common_arg_val", std::vector<variable_type>{scalar<i32>{}} };

static inline function_call get_common_arg_val =
   function_call{get_common_arg_val_decl, {}};

static inline function_decl get_compile_time_arg_val_decl =
   function_decl{"get_compile_time_arg_val", std::vector<variable_type>{scalar<i32>{}} };

static inline function_call get_compile_time_arg_val =
   function_call{get_compile_time_arg_val_decl, {}};

} /* namespace kernel_argument */

namespace circular_buffer {

static inline function_decl cb_pages_reservable_at_back_decl =
   function_decl{"cb_pages_reservable_at_back", std::vector<variable_type>{scalar<i32>{}, scalar<i32>{}} };

static inline function_call cb_pages_reservable_at_back =
   function_call{cb_pages_reservable_at_back_decl, {}};

static inline function_decl cb_pages_available_at_front_decl =
   function_decl{"cb_pages_available_at_front", std::vector<variable_type>{scalar<i32>{}, scalar<i32>{}} };

static inline function_call cb_pages_available_at_front =
   function_call{cb_pages_available_at_front_decl, {}};

static inline function_decl cb_pop_front_decl =
   function_decl{"cb_pop_front", std::vector<variable_type>{scalar<i32>{}, scalar<i32>{}} };

static inline function_call cb_pop_front =
   function_call{cb_pop_front_decl, {}};

static inline function_decl cb_push_back_decl =
   function_decl{"cb_push_back", std::vector<variable_type>{scalar<i32>{}, scalar<i32>{}} };

static inline function_call cb_push_back =
   function_call{cb_push_back_decl, {}};

static inline function_decl cb_reserve_back_decl =
   function_decl{"cb_reserve_back", std::vector<variable_type>{scalar<i32>{}, scalar<i32>{}} };

static inline function_call cb_reserve_back =
   function_call{cb_reserve_back_decl, {}};

static inline function_decl cb_wait_front_decl =
   function_decl{"cb_wait_front", std::vector<variable_type>{scalar<i32>{}, scalar<i32>{}} };

static inline function_call cb_wait_front =
   function_call{cb_wait_front_decl, {}};

} /* namespace circular buffer */

namespace data_movement {

static inline scalar<u32> NOC0{"NOC0"};
static inline scalar<u32> NOC1{"NOC1"};
static inline scalar<u32> RD_CMD_BUF{"RD_CMD_BUF"};
static inline scalar<u32> WR_CMD_BUF{"WR_CMD_BUF"};
static inline scalar<u32> WR_REG_CMD_BUF{"WR_REG_CMD_BUF"};
static inline scalar<u32> AT_CMD_BUF{"AT_CMD_BUF"};
static inline scalar<u32> VC1{"VC1"};
static inline scalar<u32> VC2{"VC2"};
static inline scalar<u32> VC3{"VC3"};
static inline scalar<u32> VC4{"VC4"};
static inline scalar<u32> VC5{"VC5"};
static inline scalar<u32> VC6{"VC6"};

static inline function_decl noc_semaphore_inc_decl =
   function_decl{"noc_semaphore_inc", std::vector<variable_type>{scalar<u64>{}, scalar<u32>{}, scalar<u8>{}} };

static inline function_call noc_semaphore_inc =
   function_call{noc_semaphore_inc_decl, {}};

static inline function_decl noc_semaphore_wait_decl =
   function_decl{"noc_semaphore_wait", std::vector<variable_type>{pointer<scalar<u32>>{}, scalar<u32>{}} };

static inline function_call noc_semaphore_wait =
   function_call{noc_semaphore_wait_decl, {}};

static inline function_decl noc_semaphore_set_decl =
   function_decl{"noc_semaphore_set", std::vector<variable_type>{pointer<scalar<u32>>{}, scalar<u32>{}} };

static inline function_call noc_semaphore_set =
   function_call{noc_semaphore_set_decl, {}};

static inline function_decl noc_semaphore_set_multicast_decl =
   function_decl{"noc_semaphore_set_multicast", std::vector<variable_type>{scalar<u32>{}, scalar<u64>{}, scalar<u32>{}, scalar<boolean>{}, scalar<boolean>{}, scalar<u8>{}} };

static inline function_call noc_semaphore_set_multicast =
   function_call{noc_semaphore_set_multicast_decl, {}};

static inline function_decl noc_async_write_multicast_decl =
   function_decl{"noc_async_write_multicast", std::vector<variable_type>{scalar<u32>{}, scalar<u64>{}, scalar<u32>{}, scalar<u32>{}, scalar<boolean>{}, scalar<boolean>{}, scalar<u8>{}} };

static inline function_call noc_async_write_multicast =
   function_call{noc_async_write_multicast_decl, {}};

static inline function_decl noc_async_write_barrier_decl =
   function_decl{"noc_async_write_barrier", std::vector<variable_type>{scalar<u8>{}} };

static inline function_call noc_async_write_barrier =
   function_call{noc_async_write_barrier_decl, {}};

static inline function_decl noc_async_read_barrier_decl =
   function_decl{"noc_async_read_barrier", std::vector<variable_type>{scalar<u8>{}} };

static inline function_call noc_async_read_barrier =
   function_call{noc_async_read_barrier_decl, {}};

static inline function_decl noc_async_write_decl =
   function_decl{"noc_async_write", std::vector<variable_type>{scalar<u32>{}, scalar<u64>{}, scalar<u32>{}, scalar<u8>{}} };

static inline function_call noc_async_write =
   function_call{noc_async_write_decl, {}};

static inline function_decl noc_async_read_decl =
   function_decl{"noc_async_read", std::vector<variable_type>{scalar<u64>{}, scalar<u32>{}, scalar<u32>{}, scalar<u8>{}} };

static inline function_call noc_async_read =
   function_call{noc_async_read_decl, {}};

} /* namespace data movement */

namespace dataflow {

static inline function_decl get_noc_addr_from_bank_id_decl =
   function_decl{"get_noc_addr_from_bank_id<false>", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u8>{}} };

static inline function_call get_noc_addr_from_bank_id =
   function_call{get_noc_addr_from_bank_id_decl, {}};

static inline function_decl get_noc_addr_from_bank_id_dram_decl =
   function_decl{"get_noc_addr_from_bank_id<true>", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u8>{}} };

static inline function_call get_noc_addr_from_bank_id_dram =
   function_call{get_noc_addr_from_bank_id_dram_decl, {}};

} /* namespace dataflow */

namespace compute {

static inline function_decl copy_tile_decl =
   function_decl{"copy_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}} };

static inline function_call copy_tile =
   function_call{copy_tile_decl, {}};

static inline function_decl copy_tile_to_dst_init_short_with_dt_decl =
   function_decl{"copy_tile_to_dst_init_short_with_dt", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}} };

static inline function_call copy_tile_to_dst_init_short_with_dt =
   function_call{copy_tile_to_dst_init_short_with_dt_decl, {}};

static inline function_decl copy_tile_to_dst_init_short_decl =
   function_decl{"copy_tile_to_dst_init_short", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}} };

static inline function_call copy_tile_to_dst_init_short =
   function_call{copy_tile_to_dst_init_short_decl, {}};

static inline function_decl copy_tile_init_decl =
   function_decl{"copy_tile_init", std::vector<variable_type>{} };

static inline function_call copy_tile_init =
   function_call{copy_tile_init_decl, {}};

static inline function_decl acquire_dst_decl =
   function_decl{"acquire_dst", std::vector<variable_type>{} };

static inline function_call acquire_dst =
   function_call{acquire_dst_decl, {}};

static inline function_decl release_dst_decl =
   function_decl{"release_dst", std::vector<variable_type>{} };

static inline function_call release_dst =
   function_call{release_dst_decl, {}};

static inline function_decl tile_regs_acquire_decl =
   function_decl{"tile_regs_acquire", std::vector<variable_type>{}};

static inline function_call tile_regs_acquire =
   function_call{tile_regs_acquire_decl, {}};

static inline function_decl tile_regs_wait_decl =
   function_decl{"tile_regs_wait", std::vector<variable_type>{}};

static inline function_call tile_regs_wait =
   function_call{tile_regs_wait_decl, {}};

static inline function_decl tile_regs_commit_decl =
   function_decl{"tile_regs_commit", std::vector<variable_type>{}};

static inline function_call tile_regs_commit =
   function_call{tile_regs_commit_decl, {}};

static inline function_decl tile_regs_release_decl =
   function_decl{"tile_regs_release", std::vector<variable_type>{}};

static inline function_call tile_regs_release =
   function_call{tile_regs_release_decl, {}};

static inline function_decl abs_tile_decl =
   function_decl{"abs_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call abs_tile =
   function_call{abs_tile_decl, {}};

static inline function_decl add_tiles_init_nof_decl =
   function_decl{"add_tiles_init_nof", std::vector<variable_type>{}};

static inline function_call add_tiles_init_nof =
   function_call{add_tiles_init_nof_decl, {}};

static inline function_decl add_tiles_init_decl =
   function_decl{"add_tiles_init", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<boolean>{}}};

static inline function_call add_tiles_init =
   function_call{add_tiles_init_decl, {}};

static inline function_decl add_tiles_decl =
   function_decl{"add_tiles", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call add_tiles =
   function_call{add_tiles_decl, {}};

static inline function_decl sub_tiles_init_nof_decl =
   function_decl{"sub_tiles_init_nof", std::vector<variable_type>{}};

static inline function_call sub_tiles_init_nof =
   function_call{sub_tiles_init_nof_decl, {}};

static inline function_decl sub_tiles_init_decl =
   function_decl{"sub_tiles_init", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<boolean>{}}};

static inline function_call sub_tiles_init =
   function_call{sub_tiles_init_decl, {}};

static inline function_decl sub_tiles_decl =
   function_decl{"sub_tiles", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call sub_tiles =
   function_call{sub_tiles_decl, {}};

static inline function_decl mul_tiles_init_f_decl =
   function_decl{"mul_tiles_init_f", std::vector<variable_type>{}};

static inline function_call mul_tiles_init_f =
   function_call{mul_tiles_init_f_decl, {}};

static inline function_decl mul_tiles_init_decl =
   function_decl{"mul_tiles_init", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call mul_tiles_init =
   function_call{mul_tiles_init_decl, {}};

static inline function_decl mul_tiles_decl =
   function_decl{"mul_tiles", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call mul_tiles =
   function_call{mul_tiles_decl, {}};

static inline function_decl add_bcast_cols_init_short_decl =
   function_decl{"add_bcast_cols_init_short", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call add_bcast_cols_init_short =
   function_call{add_bcast_cols_init_short_decl, {}};

static inline function_decl add_bcast_rows_init_short_decl =
   function_decl{"add_bcast_rows_init_short", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call add_bcast_rows_init_short =
   function_call{add_bcast_rows_init_short_decl, {}};

// last argument is tBcastDim
//
static inline scalar<u32> BroadCastType_Col{"BroadcastType::COL"};
static inline scalar<u32> BroadCastType_Row{"BroadcastType::ROW"};

static inline function_decl add_tiles_bcast_r_decl =
   function_decl{"add_tiles_bcast<BroadcastType::ROW>", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call add_tiles_bcast_r =
   function_call{add_tiles_bcast_r_decl, {}};

static inline function_decl add_tiles_bcast_c_decl =
   function_decl{"add_tiles_bcast<BroadcastType::COL>", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call add_tiles_bcast_c =
   function_call{add_tiles_bcast_c_decl, {}};

static inline function_decl sub_bcast_cols_init_short_decl =
   function_decl{"sub_bcast_colss_init_short", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call sub_bcast_cols_init_short =
   function_call{sub_bcast_cols_init_short_decl, {}};

static inline function_decl sub_bcast_rows_init_short_decl =
   function_decl{"sub_bcast_rows_init_short", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call sub_bcast_rows_init_short =
   function_call{sub_bcast_rows_init_short_decl, {}};

static inline function_decl sub_tiles_bcast_r_decl =
   function_decl{"sub_tiles_bcast<BroadcastType::ROW>", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call sub_tiles_bcast_r =
   function_call{sub_tiles_bcast_r_decl, {}};

static inline function_decl sub_tiles_bcast_c_decl =
   function_decl{"sub_tiles_bcast<BroadcastType::COL>", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call sub_tiles_bcast_c =
   function_call{sub_tiles_bcast_c_decl, {}};

static inline function_decl mul_bcast_cols_init_short_decl =
   function_decl{"mul_bcast_cols_init_short", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call mul_bcast_cols_init_short =
   function_call{mul_bcast_cols_init_short_decl, {}};

static inline function_decl mul_bcast_rows_init_short_decl =
   function_decl{"mul_bcast_rows_init_short", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call mul_bcast_rows_init_short =
   function_call{mul_bcast_rows_init_short_decl, {}};

static inline function_decl mul_tiles_bcast_r_decl =
   function_decl{"mul_tiles_bcast<BroadcastType::ROW>", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call mul_tiles_bcast_r =
   function_call{mul_tiles_bcast_r_decl, {}};

static inline function_decl mul_tiles_bcast_c_decl =
   function_decl{"mul_tiles_bcast<BroadcastType::COL>", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call mul_tiles_bcast_c =
   function_call{mul_tiles_bcast_c_decl, {}};

static inline function_decl mul_tiles_bcast_scalar_init_short_decl =
   function_decl{"mul_tiles_bcast_scalar_init_short", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call mul_tiles_bcast_scalar =
   function_call{mul_tiles_bcast_scalar_init_short_decl, {}};

static inline function_decl mm_init_decl =
   function_decl{"mm_init", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call mm_init =
   function_call{mm_init_decl, {}};

static inline function_decl mm_init_short_with_dt_decl =
   function_decl{"mm_init_short_with_dt", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call mm_init_short_with_dt =
   function_call{mm_init_short_with_dt_decl, {}};

static inline function_decl mm_init_short_decl =
   function_decl{"mm_init_short", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call mm_init_short =
   function_call{mm_init_short_decl, {}};

static inline function_decl matmul_tiles_decl =
   function_decl{"matmul_tiles", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call matmul_tiles =
   function_call{matmul_tiles_decl, {}};

static inline function_decl mm_block_init_decl =
   function_decl{"mm_block_init", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call mm_block_init =
   function_call{mm_block_init_decl, {}};

static inline function_decl mm_block_init_short_decl =
   function_decl{"mm_block_init_short", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call mm_block_init_short =
   function_call{mm_block_init_short_decl, {}};

static inline function_decl mm_block_init_short_dt_decl =
   function_decl{"mm_block_init_short_dt", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call mm_block_init_short_dt =
   function_call{mm_block_init_short_dt_decl, {}};

static inline function_decl matmul_block_decl =
   function_decl{"matmul_block", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call matmul_block =
   function_call{matmul_block_decl, {}};

static inline function_decl exp_tile_init_decl =
   function_decl{"exp_tile_init", std::vector<variable_type>{}};

static inline function_call exp_tile_init =
   function_call{exp_tile_init_decl, {}};

static inline function_decl exp_tile_decl =
   function_decl{"exp_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call exp_tile =
   function_call{exp_tile_decl, {}};

static inline function_decl exp_tile_fast_approx_init_decl =
   function_decl{"exp_tile_init<true>", std::vector<variable_type>{}};

static inline function_call exp_tile_fast_approx_init =
   function_call{exp_tile_fast_approx_init_decl, {}};

static inline function_decl exp_tile_fast_approx_decl =
   function_decl{"exp_tile<true>", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call exp_tile_fast_approx =
   function_call{exp_tile_fast_approx_decl, {}};

static inline function_decl exp2_tile_init_decl =
   function_decl{"exp2_tile_init", std::vector<variable_type>{}};

static inline function_call exp2_tile_init =
   function_call{exp2_tile_init_decl, {}};

static inline function_decl exp2_tile_decl =
   function_decl{"exp2_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call exp2_tile =
   function_call{exp2_tile_decl, {}};

static inline function_decl expm1_tile_init_decl =
   function_decl{"expm1_tile_init", std::vector<variable_type>{}};

static inline function_call expm1_tile_init =
   function_call{expm1_tile_init_decl, {}};

static inline function_decl expm1_tile_decl =
   function_decl{"expm1_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call expm1_tile =
   function_call{expm1_tile_decl, {}};

static inline function_decl relu_tile_init_decl =
   function_decl{"relu_tile_init", std::vector<variable_type>{}};

static inline function_call relu_tile_init =
   function_call{relu_tile_init_decl, {}};

static inline function_decl relu_tile_decl =
   function_decl{"relu_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call relu_tile =
   function_call{relu_tile_decl, {}};

static inline function_decl relu_max_tile_init_decl =
   function_decl{"relu_max_tile_init", std::vector<variable_type>{}};

static inline function_call relu_max_tile_init =
   function_call{relu_max_tile_init_decl, {}};

static inline function_decl relu_max_tile_decl =
   function_decl{"relu_max_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call relu_max_tile =
   function_call{relu_max_tile_decl, {}};

static inline function_decl relu_min_tile_init_decl =
   function_decl{"relu_min_tile_init", std::vector<variable_type>{}};

static inline function_call relu_min_tile_init =
   function_call{relu_min_tile_init_decl, {}};

static inline function_decl relu_min_tile_decl =
   function_decl{"relu_min_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call relu_min_tile =
   function_call{relu_min_tile_decl, {}};

static inline function_decl leaky_relu_tile_init_decl =
   function_decl{"leaky_relu_tile_init", std::vector<variable_type>{}};

static inline function_call leaky_relu_tile_init =
   function_call{leaky_relu_tile_init_decl, {}};

static inline function_decl leaky_relu_tile_decl =
   function_decl{"leaky_relu_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call leaky_relu_tile =
   function_call{leaky_relu_tile_decl, {}};

static inline function_decl elu_tile_init_decl =
   function_decl{"elu_tile_init", std::vector<variable_type>{}};

static inline function_call elu_tile_init =
   function_call{elu_tile_init_decl, {}};

static inline function_decl elu_tile_decl =
   function_decl{"elu_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call elu_tile =
   function_call{elu_tile_decl, {}};

static inline function_decl erf_tile_init_decl =
   function_decl{"erf_tile_init<false>", std::vector<variable_type>{}};

static inline function_call erf_tile_init =
   function_call{erf_tile_init_decl, {}};

static inline function_decl erf_tile_decl =
   function_decl{"erf_tile<false>", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call erf_tile =
   function_call{erf_tile_decl, {}};

static inline function_decl erf_tile_fast_approx_init_decl =
   function_decl{"erf_tile_init", std::vector<variable_type>{}};

static inline function_call erf_tile_fast_approx_init =
   function_call{erf_tile_fast_approx_init_decl, {}};

static inline function_decl erf_tile_fast_approx_decl =
   function_decl{"erf_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call erf_tile_fast_approx =
   function_call{erf_tile_fast_approx_decl, {}};

static inline function_decl erfc_tile_init_decl =
   function_decl{"erfc_tile_init<false>", std::vector<variable_type>{}};

static inline function_call erfc_tile_init =
   function_call{erfc_tile_init_decl, {}};

static inline function_decl erfc_tile_decl =
   function_decl{"erfc_tile<false>", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call erfc_tile =
   function_call{erfc_tile_decl, {}};

static inline function_decl erfc_tile_fast_approx_init_decl =
   function_decl{"erfc_tile_init", std::vector<variable_type>{}};

static inline function_call erfc_tile_fast_approx_init =
   function_call{erfc_tile_fast_approx_init_decl, {}};

static inline function_decl erfc_tile_fast_approx_decl =
   function_decl{"erfc_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call erfc_tile_fast_approx =
   function_call{erfc_tile_fast_approx_decl, {}};

static inline function_decl erfinv_tile_init_decl =
   function_decl{"erfinv_tile_init", std::vector<variable_type>{}};

static inline function_call erfinv_tile_init =
   function_call{erfinv_tile_init_decl, {}};

static inline function_decl erfinv_tile_decl =
   function_decl{"erfinv_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call erfinv_tile =
   function_call{erfinv_tile_decl, {}};

static inline function_decl gelu_tile_init_decl =
   function_decl{"gelu_tile_init<false>", std::vector<variable_type>{}};

static inline function_call gelu_tile_init =
   function_call{gelu_tile_init_decl, {}};

static inline function_decl gelu_tile_decl =
   function_decl{"gelu_tile<false>", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call gelu_tile =
   function_call{gelu_tile_decl, {}};

static inline function_decl gelu_tile_fast_approx_init_decl =
   function_decl{"gelu_tile_init", std::vector<variable_type>{}};

static inline function_call gelu_tile_fast_approx_init =
   function_call{gelu_tile_fast_approx_init_decl, {}};

static inline function_decl gelu_tile_fast_approx_decl =
   function_decl{"gelu_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call gelu_tile_fast_approx =
   function_call{gelu_tile_fast_approx_decl, {}};

static inline function_decl heaviside_tile_init_decl =
   function_decl{"heaviside_tile_init", std::vector<variable_type>{}};

static inline function_call heaviside_tile_init =
   function_call{heaviside_tile_init_decl, {}};

static inline function_decl heaviside_tile_decl =
   function_decl{"heaviside_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call heaviside_tile =
   function_call{heaviside_tile_decl, {}};

static inline function_decl isinf_tile_init_decl =
   function_decl{"isinf_tile_init", std::vector<variable_type>{}};

static inline function_call isinf_tile_init =
   function_call{isinf_tile_init_decl, {}};

static inline function_decl isinf_tile_decl =
   function_decl{"isinf_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call isinf_tile =
   function_call{isinf_tile_decl, {}};

static inline function_decl isposinf_tile_init_decl =
   function_decl{"isposinf_tile_init", std::vector<variable_type>{}};

static inline function_call isposinf_tile_init =
   function_call{isposinf_tile_init_decl, {}};

static inline function_decl isposinf_tile_decl =
   function_decl{"isposinf_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call isposinf_tile =
   function_call{isposinf_tile_decl, {}};

static inline function_decl isneginf_tile_init_decl =
   function_decl{"isneginf_tile_init", std::vector<variable_type>{}};

static inline function_call isneginf_tile_init =
   function_call{isneginf_tile_init_decl, {}};

static inline function_decl isneginf_tile_decl =
   function_decl{"isneginf_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call isneginf_tile =
   function_call{isneginf_tile_decl, {}};

static inline function_decl isfinite_tile_init_decl =
   function_decl{"isfinite_tile_init", std::vector<variable_type>{}};

static inline function_call isfinite_tile_init =
   function_call{isfinite_tile_init_decl, {}};

static inline function_decl isfinite_tile_decl =
   function_decl{"isfinite_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call isfinite_tile =
   function_call{isfinite_tile_decl, {}};

static inline function_decl isnan_tile_decl =
   function_decl{"isnan_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call isnan_tile =
   function_call{isnan_tile_decl, {}};

static inline function_decl i0_tile_init_decl =
   function_decl{"i0_tile_init", std::vector<variable_type>{}};

static inline function_call i0_tile_init =
   function_call{i0_tile_init_decl, {}};

static inline function_decl i0_tile_decl =
   function_decl{"i0_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call i0_tile =
   function_call{i0_tile_decl, {}};

static inline function_decl logical_not_unary_tile_init_decl =
   function_decl{"logical_not_unary_tile_init", std::vector<variable_type>{}};

static inline function_call logical_not_unary_tile_init =
   function_call{logical_not_unary_tile_init_decl, {}};

static inline function_decl logical_not_unary_tile_decl =
   function_decl{"logical_not_unary_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call logical_not_unary_tile =
   function_call{logical_not_unary_tile_decl, {}};

static inline function_decl recip_tile_init_decl =
   function_decl{"recip_tile_init", std::vector<variable_type>{}};

static inline function_call recip_tile_init =
   function_call{recip_tile_init_decl, {}};

static inline function_decl recip_tile_decl =
   function_decl{"recip_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call recip_tile =
   function_call{recip_tile_decl, {}};

static inline function_decl sign_tile_init_decl =
   function_decl{"sign_tile_init", std::vector<variable_type>{}};

static inline function_call sign_tile_init =
   function_call{sign_tile_init_decl, {}};

static inline function_decl sign_tile_decl =
   function_decl{"sign_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call sign_tile =
   function_call{sign_tile_decl, {}};

static inline function_decl sqrt_tile_init_decl =
   function_decl{"sqrt_tile_init", std::vector<variable_type>{}};

static inline function_call sqrt_tile_init =
   function_call{sqrt_tile_init_decl, {}};

static inline function_decl sqrt_tile_decl =
   function_decl{"sqrt_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call sqrt_tile =
   function_call{sqrt_tile_decl, {}};

static inline function_decl rsqrt_tile_init_decl =
   function_decl{"rsqrt_tile_init<false>", std::vector<variable_type>{}};

static inline function_call rsqrt_tile_init =
   function_call{rsqrt_tile_init_decl, {}};

static inline function_decl rsqrt_tile_decl =
   function_decl{"rsqrt_tile<false>", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call rsqrt_tile =
   function_call{rsqrt_tile_decl, {}};

static inline function_decl rsqrt_tile_fast_approx_init_decl =
   function_decl{"rsqrt_tile_init", std::vector<variable_type>{}};

static inline function_call rsqrt_tile_fast_approx_init =
   function_call{rsqrt_tile_fast_approx_init_decl, {}};

static inline function_decl rsqrt_tile_fast_approx_decl =
   function_decl{"rsqrt_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call rsqrt_tile_fast_approx =
   function_call{rsqrt_tile_fast_approx_decl, {}};

static inline function_decl sigmoid_tile_init_decl =
   function_decl{"sigmoid_tile_init", std::vector<variable_type>{}};

static inline function_call sigmoid_tile_init =
   function_call{sigmoid_tile_init_decl, {}};

static inline function_decl sigmoid_tile_decl =
   function_decl{"sigmoid_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call sigmoid_tile =
   function_call{sigmoid_tile_decl, {}};

static inline function_decl log_tile_init_decl =
   function_decl{"log_tile_init", std::vector<variable_type>{}};

static inline function_call log_tile_init =
   function_call{log_tile_init_decl, {}};

static inline function_decl log_tile_decl =
   function_decl{"log_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call log_tile =
   function_call{log_tile_decl, {}};

static inline function_decl log_with_base_tile_init_decl =
   function_decl{"log_with_base_tile_init", std::vector<variable_type>{}};

static inline function_call log_with_base_tile_init =
   function_call{log_with_base_tile_init_decl, {}};

static inline function_decl log_with_base_tile_decl =
   function_decl{"log_with_base_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call log_with_base_tile =
   function_call{log_with_base_tile_decl, {}};

static inline function_decl power_tile_init_decl =
   function_decl{"power_tile_init", std::vector<variable_type>{}};

static inline function_call power_tile_init =
   function_call{power_tile_init_decl, {}};

static inline function_decl power_tile_decl =
   function_decl{"power_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call power_tile =
   function_call{power_tile_decl, {}};

static inline function_decl rsub_tile_init_decl =
   function_decl{"rsub_tile_init", std::vector<variable_type>{}};

static inline function_call rsub_tile_init =
   function_call{rsub_tile_init_decl, {}};

static inline function_decl rsub_tile_decl =
   function_decl{"rsub_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call rsub_tile =
   function_call{rsub_tile_decl, {}};

static inline function_decl signbit_tile_init_decl =
   function_decl{"signbit_tile_init", std::vector<variable_type>{}};

static inline function_call signbit_tile_init =
   function_call{signbit_tile_init_decl, {}};

static inline function_decl signbit_tile_decl =
   function_decl{"signbit_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call signbit_tile =
   function_call{signbit_tile_decl, {}};

static inline function_decl square_tile_init_decl =
   function_decl{"square_tile_init", std::vector<variable_type>{}};

static inline function_call square_tile_init =
   function_call{square_tile_init_decl, {}};

static inline function_decl square_tile_decl =
   function_decl{"square_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call square_tile =
   function_call{square_tile_decl, {}};

static inline function_decl reduce_tile_sum_r_decl =
   function_decl{"reduce_tile<ReduceFunc::Sum, Reduce::R>", std::vector<variable_type>{scalar<u32>{},scalar<u32>{},scalar<u32>{},scalar<u32>{},scalar<u32>{}}};

static inline function_call reduce_tile_sum_r =
   function_call{reduce_tile_sum_r_decl, {}};

static inline function_decl reduce_tile_sum_c_decl =
   function_decl{"reduce_tile<ReduceFunc::Sum, Reduce::C>", std::vector<variable_type>{scalar<u32>{},scalar<u32>{},scalar<u32>{},scalar<u32>{},scalar<u32>{}}};

static inline function_call reduce_tile_sum_c =
   function_call{reduce_tile_sum_c_decl, {}};

static inline function_decl reduce_tile_sum_rc_decl =
   function_decl{"reduce_tile<ReduceFunc::Sum, Reduce::RC>", std::vector<variable_type>{scalar<u32>{},scalar<u32>{},scalar<u32>{},scalar<u32>{},scalar<u32>{}}};

static inline function_call reduce_tile_sum_rc =
   function_call{reduce_tile_sum_rc_decl, {}};

static inline function_decl reduce_tile_max_r_decl =
   function_decl{"reduce_tile<ReduceFunc::Max, Reduce::R>", std::vector<variable_type>{scalar<u32>{},scalar<u32>{},scalar<u32>{},scalar<u32>{},scalar<u32>{}}};

static inline function_call reduce_tile_max_r =
   function_call{reduce_tile_max_r_decl, {}};

static inline function_decl reduce_tile_max_c_decl =
   function_decl{"reduce_tile<ReduceFunc::Max, Reduce::C>", std::vector<variable_type>{scalar<u32>{},scalar<u32>{},scalar<u32>{},scalar<u32>{},scalar<u32>{}}};

static inline function_call reduce_tile_max_c =
   function_call{reduce_tile_max_c_decl, {}};

static inline function_decl reduce_tile_max_rc_decl =
   function_decl{"reduce_tile<ReduceFunc::Max, Reduce::RC>", std::vector<variable_type>{scalar<u32>{},scalar<u32>{},scalar<u32>{},scalar<u32>{},scalar<u32>{}}};

static inline function_call reduce_tile_max_rc =
   function_call{reduce_tile_max_rc_decl, {}};

static inline function_decl transpose_wh_init_decl =
   function_decl{"transpose_wh_init", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call transpose_wh_init =
   function_call{transpose_wh_init_decl, {}};

static inline function_decl transpose_wh_tile_decl =
   function_decl{"transpose_wh_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call transpose_wh_tile =
   function_call{transpose_wh_tile_decl, {}};

static inline function_decl tanh_tile_init_decl =
   function_decl{"tanh_tile_init", std::vector<variable_type>{}};

static inline function_call tanh_tile_init =
   function_call{tanh_tile_init_decl, {}};

static inline function_decl tanh_tile_decl =
   function_decl{"tanh_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call tanh_tile =
   function_call{tanh_tile_decl, {}};

static inline function_decl tan_tile_init_decl =
   function_decl{"tan_tile_init", std::vector<variable_type>{}};

static inline function_call tan_tile_init =
   function_call{tan_tile_init_decl, {}};

static inline function_decl tan_tile_decl =
   function_decl{"tan_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call tan_tile =
   function_call{tan_tile_decl, {}};

static inline function_decl sin_tile_init_decl =
   function_decl{"sin_tile_init", std::vector<variable_type>{}};

static inline function_call sin_tile_init =
   function_call{sin_tile_init_decl, {}};

static inline function_decl sin_tile_decl =
   function_decl{"sin_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call sin_tile =
   function_call{sin_tile_decl, {}};

static inline function_decl cos_tile_init_decl =
   function_decl{"cos_tile_init", std::vector<variable_type>{}};

static inline function_call cos_tile_init =
   function_call{cos_tile_init_decl, {}};

static inline function_decl cos_tile_decl =
   function_decl{"cos_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call cos_tile =
   function_call{cos_tile_decl, {}};

static inline function_decl asin_tile_init_decl =
   function_decl{"asin_tile_init", std::vector<variable_type>{}};

static inline function_call asin_tile_init =
   function_call{asin_tile_init_decl, {}};

static inline function_decl asin_tile_decl =
   function_decl{"asin_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call asin_tile =
   function_call{asin_tile_decl, {}};

static inline function_decl atan_tile_init_decl =
   function_decl{"atan_tile_init", std::vector<variable_type>{}};

static inline function_call atan_tile_init =
   function_call{atan_tile_init_decl, {}};

static inline function_decl atan_tile_decl =
   function_decl{"atan_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call atan_tile =
   function_call{atan_tile_decl, {}};

static inline function_decl acos_tile_init_decl =
   function_decl{"acos_tile_init", std::vector<variable_type>{}};

static inline function_call acos_tile_init =
   function_call{acos_tile_init_decl, {}};

static inline function_decl acos_tile_decl =
   function_decl{"acos_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call acos_tile =
   function_call{acos_tile_decl, {}};

static inline function_decl ltz_tile_init_decl =
   function_decl{"ltz_tile_init", std::vector<variable_type>{}};

static inline function_call ltz_tile_init =
   function_call{ltz_tile_init_decl, {}};

static inline function_decl ltz_tile_decl =
   function_decl{"ltz_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call ltz_tile =
   function_call{ltz_tile_decl, {}};

static inline function_decl eqz_tile_init_decl =
   function_decl{"eqz_tile_init", std::vector<variable_type>{}};

static inline function_call eqz_tile_init =
   function_call{eqz_tile_init_decl, {}};

static inline function_decl eqz_tile_decl =
   function_decl{"eqz_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call eqz_tile =
   function_call{eqz_tile_decl, {}};

static inline function_decl lez_tile_init_decl =
   function_decl{"lez_tile_init", std::vector<variable_type>{}};

static inline function_call lez_tile_init =
   function_call{lez_tile_init_decl, {}};

static inline function_decl lez_tile_decl =
   function_decl{"lez_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call lez_tile =
   function_call{lez_tile_decl, {}};

static inline function_decl gtz_tile_init_decl =
   function_decl{"gtz_tile_init", std::vector<variable_type>{}};

static inline function_call gtz_tile_init =
   function_call{gtz_tile_init_decl, {}};

static inline function_decl gtz_tile_decl =
   function_decl{"gtz_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call gtz_tile =
   function_call{gtz_tile_decl, {}};

static inline function_decl gez_tile_init_decl =
   function_decl{"gez_tile_init", std::vector<variable_type>{}};

static inline function_call gez_tile_init =
   function_call{gez_tile_init_decl, {}};

static inline function_decl gez_tile_decl =
   function_decl{"gez_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call gez_tile =
   function_call{gez_tile_decl, {}};

static inline function_decl nez_tile_init_decl =
   function_decl{"nez_tile_init", std::vector<variable_type>{}};

static inline function_call nez_tile_init =
   function_call{nez_tile_init_decl, {}};

static inline function_decl nez_tile_decl =
   function_decl{"nez_tile", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call nez_tile =
   function_call{nez_tile_decl, {}};

static inline function_decl unary_ne_tile_init_decl =
   function_decl{"unary_ne_tile_init", std::vector<variable_type>{}};

static inline function_call unary_ne_tile_init =
   function_call{unary_ne_tile_init_decl, {}};

static inline function_decl unary_ne_tile_decl =
   function_decl{"unary_ne_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call unary_ne_tile =
   function_call{unary_ne_tile_decl, {}};

static inline function_decl unary_gt_tile_init_decl =
   function_decl{"unary_gt_tile_init", std::vector<variable_type>{}};

static inline function_call unary_gt_tile_init =
   function_call{unary_gt_tile_init_decl, {}};

static inline function_decl unary_gt_tile_decl =
   function_decl{"unary_gt_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call unary_gt_tile =
   function_call{unary_gt_tile_decl, {}};

static inline function_decl unary_lt_tile_init_decl =
   function_decl{"unary_lt_tile_init", std::vector<variable_type>{}};

static inline function_call unary_lt_tile_init =
   function_call{unary_lt_tile_init_decl, {}};

static inline function_decl unary_lt_tile_decl =
   function_decl{"unary_lt_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call unary_lt_tile =
   function_call{unary_lt_tile_decl, {}};

static inline function_decl cb_wait_front_decl =
   function_decl{"cb_wait_front", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call cb_wait_front =
   function_call{cb_wait_front_decl, {}};

static inline function_decl cb_pop_front_decl =
   function_decl{"cb_pop_front", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call cb_pop_front =
   function_call{cb_pop_front_decl, {}};

static inline function_decl cb_reserve_back_decl =
   function_decl{"cb_reserve_back", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call cb_reserve_back =
   function_call{cb_reserve_back_decl, {}};

static inline function_decl cb_push_back_decl =
   function_decl{"cb_push_back", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call cb_push_back =
   function_call{cb_push_back_decl, {}};

static inline function_decl binary_op_init_common_decl =
   function_decl{"binary_op_init_common", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call binary_op_init_common =
   function_call{binary_op_init_common_decl, {}};

static inline function_decl binary_op_specific_full_add_init_decl =
   function_decl{"binary_op_specific_init<true, EltwiseBinaryType::ELWADD>", std::vector<variable_type>{}};

static inline function_call binary_op_specific_full_add_init =
   function_call{binary_op_specific_full_add_init_decl, {}};

static inline function_decl binary_op_specific_full_sub_init_decl =
   function_decl{"binary_op_specific_init<true, EltwiseBinaryType::ELWSUB>", std::vector<variable_type>{}};

static inline function_call binary_op_specific_full_sub_init =
   function_call{binary_op_specific_full_sub_init_decl, {}};

static inline function_decl binary_op_specific_full_mul_init_decl =
   function_decl{"binary_op_specific_init<true, EltwiseBinaryType::ELWMUL>", std::vector<variable_type>{}};

static inline function_call binary_op_specific_full_mul_init =
   function_call{binary_op_specific_full_mul_init_decl, {}};

static inline function_decl binary_op_specific_add_init_decl =
   function_decl{"binary_op_specific_init<false, EltwiseBinaryType::ELWADD>", std::vector<variable_type>{}};

static inline function_call binary_op_specific_add_init =
   function_call{binary_op_specific_add_init_decl, {}};

static inline function_decl binary_op_specific_sub_init_decl =
   function_decl{"binary_op_specific_init<false, EltwiseBinaryType::ELWSUB>", std::vector<variable_type>{}};

static inline function_call binary_op_specific_sub_init =
   function_call{binary_op_specific_sub_init_decl, {}};

static inline function_decl binary_op_specific_mul_init_decl =
   function_decl{"binary_op_specific_init<false, EltwiseBinaryType::ELWMUL>", std::vector<variable_type>{}};

static inline function_call binary_op_specific_mul_init =
   function_call{binary_op_specific_mul_init_decl, {}};

static inline function_decl tilize_init_decl =
   function_decl{"tilize_init", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call tilize_init =
   function_call{tilize_init_decl, {}};

static inline function_decl tilize_init_short_decl =
   function_decl{"tilize_init_short", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call tilize_init_short =
   function_call{tilize_init_short_decl, {}};

static inline function_decl tilize_init_short_with_dt_decl =
   function_decl{"tilize_init_short_with_dt", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call tilize_init_short_with_dt =
   function_call{tilize_init_short_with_dt_decl, {}};

static inline function_decl tilize_block_decl =
   function_decl{"tilize_block", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call tilize_block =
   function_call{tilize_block_decl, {}};

static inline function_decl tilize_uninit_decl =
   function_decl{"tilize_uninit", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call tilize_uninit =
   function_call{tilize_uninit_decl, {}};

static inline function_decl tilize_uninit_with_dt_decl =
   function_decl{"tilize_uninit_with_dt", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call tilize_uninit_with_dt =
   function_call{tilize_uninit_with_dt_decl, {}};

static inline function_decl untilize_init_decl =
   function_decl{"untilize_init", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}}};

static inline function_call untilize_init =
   function_call{untilize_init_decl, {}};

static inline function_decl untilize_init_short_decl =
   function_decl{"untilize_init_short", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call untilize_init_short =
   function_call{untilize_init_short_decl, {}};

static inline function_decl untilize_block_decl =
   function_decl{"untilize_block", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<i32>{}}};

static inline function_call untilize_block =
   function_call{untilize_block_decl, {}};

static inline function_decl untilize_uninit_decl =
   function_decl{"untilize_uninit", std::vector<variable_type>{scalar<u32>{}}};

static inline function_call untilize_uninit =
   function_call{untilize_uninit_decl, {}};

} /* namespace compute */

namespace packing {

static inline function_decl pack_tile_ooo_decl =
   function_decl{"pack_tile<true>", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call pack_tile_ooo =
   function_call{pack_tile_ooo_decl, {}};

static inline function_decl pack_tile_decl =
   function_decl{"pack_tile<false>", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call pack_tile =
   function_call{pack_tile_decl, {}};

static inline function_decl matmul_pack_tile_decl =
   function_decl{"matmul_pack_tile", std::vector<variable_type>{scalar<u32>{}, scalar<u32>{}, scalar<u32>{}}};

static inline function_call matmul_pack_tile =
   function_call{matmul_pack_tile_decl, {}};

}

} /* namespace kernel */ } /* namespace api */ } // namespace api

#endif

/*
* Copyright(c)	2024 Christopher Taylor

* SPDX-License-Identifier: BSL-1.0
* Distributed under the Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include <iostream>

#include "tt.hpp"

int main() {

   kernel_context<crisc> ctx{host_location()};

   expression_data src_addr =
      ctx.instance<scalar<u32>>("src_addr");

   expression_data bank_id =
      ctx.instance<scalar<u32>>("bank_id");

   expression_data num_tiles =
      ctx.instance<scalar<u32>>("num_tiles");

   expression_data cb_id_in0 =
      ctx.instance<scalar<u32>>("cb_id_in0");

   expression_data ublock_size_tiles =
      ctx.instance<scalar<u32>>("ublock_size_tiles");

   expression_data ublock_size_bytes =
      ctx.instance<scalar<u32>>("ublock_size_bytes");

   expression_data i =
      ctx.instance<scalar<u32>>("i");

   expression_data src_noc_addr =
      ctx.instance<scalar<u32>>("src_noc_addr");

   expression_data l1_write_addr =
      ctx.instance<scalar<u32>>("l1_write_addr");

   kernel<brisc> brisc_kernel(ctx, {
      decl(src_addr)  = get_arg_val(0),
      decl(bank_id) = get_arg_val(1),
      decl(num_tiles) = get_arg_val(2),
      decl(cb_id_in0) = 0,
      decl(ublock_size_tiles) = 1,
      decl(ublock_size_bytes) = get_tile_size(cb_id_in0) * ublock_size_tiles,
      decl(i) = 0,
      decl(l1_write_addr) = 0,
      for_(i = 0, i < num_tiles, i = i + ublock_size_tiles, {
         src_noc_addr = get_noc_addr_from_bank_id_true(bank_id, src_addr),
         cb_reserve_back(cb_id_in0, ublock_size_tiles),
         l1_write_addr = get_write_ptr(cb_id_in0),
         noc_async_read(src_noc_addr, l1_write_addr, ublock_size_bytes),
         noc_async_read_barrier(),
         cb_push_back(cb_id_in0, ublock_size_tiles),
         src_addr = src_addr + ublock_size_bytes
      }),
   });

   std::cout << crisc_kernel << std::endl;
   std::cout << crisc_kernel.host_program_location << std::endl;

   return 0;
}

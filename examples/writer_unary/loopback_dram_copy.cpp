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

   expression_data l1_buffer_addr =
      ctx.instance<scalar<i32>>("l1_buffer_addr");

   expression_data dram_buffer_src_addr =
      ctx.instance<scalar<i32>>("dram_buffer_src_addr");

   expression_data dram_buffer_src_bank =
      ctx.instance<scalar<i32>>("dram_buffer_src_bank");

   expression_data dram_buffer_dst_addr =
      ctx.instance<scalar<i32>>("dram_buffer_dst_addr");

   expression_data dram_buffer_dst_bank =
      ctx.instance<scalar<i32>>("dram_buffer_dst_bank");

   expression_data dram_buffer_size =
      ctx.instance<scalar<i32>>("dram_buffer_size");

   expression_data dram_buffer_src_noc_addr =
      ctx.instance<scalar<i64>>("dram_buffer_src_noc_addr");

   expression_data dram_buffer_dst_noc_addr =
      ctx.instance<scalar<i64>>("dram_buffer_dst_noc_addr");

   comment empty_comment{};

   kernel<crisc> crisc_kernel(ctx, {
         decl(l1_buffer_addr) = get_arg_val(0),
         decl(dram_buffer_src_addr) = get_arg_val(1),
         decl(dram_buffer_src_bank) = get_arg_val(2),
         decl(dram_buffer_dst_addr) = get_arg_val(3),
         decl(dram_buffer_dst_bank) = get_arg_val(4),
         decl(dram_buffer_size) = get_arg_val(5),
         empty_comment,
         decl(dram_buffer_src_noc_addr) = get_noc_addr_from_bank_id_dram(dram_buffer_src_bank, dram_buffer_src_addr),
         empty_comment,
         noc_async_read(dram_buffer_src_noc_addr, l1_buffer_addr, dram_buffer_size),
         noc_async_read_barrier(),
         empty_comment,
         decl(dram_buffer_dst_noc_addr) = get_noc_addr_from_bank_id_dram(dram_buffer_dst_bank, dram_buffer_dst_addr),
         empty_comment,
         noc_async_write(dram_buffer_dst_noc_addr, l1_buffer_addr, dram_buffer_size),
         noc_async_write_barrier()
   });

   std::cout << crisc_kernel << std::endl;
   std::cout << crisc_kernel.host_program_location << std::endl;

   return 0;
}

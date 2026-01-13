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

   kernel<crisc> crisc_kernel(ctx, {
      DECL("Hello!")
   });

   std::cout << crisc_kernel << std::endl;
   std::cout << crisc_kernel.host_program_location << std::endl;

   return 0;
}

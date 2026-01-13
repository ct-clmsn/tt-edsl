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

   expression_data a =
      ctx.instance<scalar<i32>>("a");

   expression_data b =
      ctx.instance<array<i32>>("b", 10UL);

   expression_data c =
      ctx.instance<matrix<i32>>("c", {10UL,10UL});

   kernel<crisc> crisc_kernel(ctx, {
         include(cstdint),
         kernel_main[{
            decl(a),
            decl(b),
            decl(c),
            a = 0,
/*
            a = a,
            a = a + 1,
            a = b[0],
            b[0] = b[0],
            b[0] = c[0][0],
            a = b[0] * c[0][0],
            a = b[0] + c[0][0] - a * 1,
            a = b[0] * c[0][0] / c[0][0],
            a = _( a + a ) % b[0],
            a = a + _( a + a ) + a,
            comment{"a = get_arg_addr(0)"},
            for_(a = a, a < a, a = a + a, {
               a = a + 1
            }),
            if_(a == 0, {
               a = 0
            }),
            comment{"a = get_arg_addr(0)"},
*/
            if_(a == 0, {
               a = 0
            }),
            if_(a == 20, {
               a = 20
            })
            .else_({
               a = 2
            }),
            if_(a == 10, {
               a = 10
            }),
/*
            comment{"a = get_arg_addr(0)"},
            if_(a == 0, {
               a = 0
            })
            .else_if_(a == 1,{
               a = 1
            }),
            comment{"a = get_arg_addr(0)"},
            if_(a == 0, {
               a = 0
            })
            .else_if_(a == 1,{
               a = 1
            })
            .else_({
               a = 2
            }),
*/
         }]
   });

/*
            if_(a == 0, {
               a = a + 1
            })
            .else_if_( a == 0, {
               a = a + 1
            })
            .else_({
               a = a + 1
            }),
            while_(a == 0, {
               a = a + 1
            }),
            switch_(a)
            .case_(1, {
               a = a + 1
            })
            .case_(2,{
               a = a + 1
            })
            .default_({
               a = a + 1
            })
         }]
   });
*/
/*
         include(cstdint),
         kernel_main[{
            decl(a),
            decl(b),
            decl(c),
            a = b[0] + c[0][0] + a,
            a = b[0] - c[0][0],
            a = b[0] * c[0][0],
            a = b[0] / c[0][0],
            a = b[0] % c[0][0],
            a = _( a + a ),
            a = _( a + a ) + a,
            a = a + _( a + a ),
            a = a + _( a + a ) + a,
            a = b[0],
            a = c[0][0],
            comment{"here"},
            comment{"a = get_arg_addr(0)"},
            a = 0,
            for_(a = 0, a < 1, a = a + 1, {}),
            for_(a = a, a < a, a = a + a, {}),
            if_(a == 0, {
               a = a + 1
            }),
            if_(a == 0, {
            })
            .else_({
            }),
            if_(a == 0, {
            })
            .else_if_( a == 0, {
            }),
            if_(a == 0, {
            })
            .else_if_( a == 0, {
            })
            .else_({
            }),
            while_(a == a, {
            }),
            while_(a == 0, {
               a = a + 1
            }),
            switch_(a).case_(1, {}),
            switch_(a).case_(1, {}).default_({ a = a + 1 }),
            switch_(a).case_(1, {}).case_(2,{}),
            switch_(a).case_(1, {}).case_(2,{}).default_({ a = a + 1 })
         }]
      });
*/
   std::cout << crisc_kernel << std::endl;

   return 0;
}

/*
* Copyright(c)	2024 Christopher Taylor

* SPDX-License-Identifier: BSL-1.0
* Distributed under the Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once
#ifndef __TT_EDSL_BASE_HPP__
#define __TT_EDSL_BASE_HPP__

#include <string>
#include <tuple>
#include <map>
#include <vector>
#include <type_traits>
#include <functional>
#include <initializer_list>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include <iostream>

#include "variant.hpp"
#include "recursive_wrapper.hpp"

using namespace mpark;
using namespace mpark::util;

namespace tt { namespace dsl {

using identifier = std::string;

struct none {
   using value_type = void*;
   constexpr static inline char const* value = R"(nullptr)";

   void decl(std::string & buf) const {
   }
};

struct i8 { 
   using value_type = std::int8_t;
   constexpr static inline char const* value = R"(std::int8_t)";
};
struct i16 {
   using value_type = std::int16_t;
   constexpr static inline char const* value = R"(std::int16_t)";
};
struct i32 {
   using value_type = std::int32_t;
   constexpr static inline char const* value = R"(std::int32_t)";
};

struct i64 {
   using value_type = std::int64_t;
   constexpr static inline char const* value = R"(std::int64_t)";
};

struct u8 {
   using value_type = std::uint8_t;
   constexpr static inline char const* value = R"(std::uint8_t)";
};
struct u16 {
   using value_type = std::uint16_t;
   constexpr static inline char const* value = R"(std::uint16_t)";
};
struct u32 {
   using value_type = std::uint32_t;
   constexpr static inline char const* value = R"(std::uint32_t)";
};
struct u64 {
   using value_type = std::uint64_t;
   constexpr static inline char const* value = R"(std::uint64_t)";
};

struct fp16a {
   using value_type = std::uint16_t;
   constexpr static inline char const* value = R"(std::uint16_t)";
};
struct fp16b {
   using value_type = std::uint16_t;
   constexpr static inline char const* value = R"(std::uint16_t)";
};
struct fp32 {
   using value_type = float;
   constexpr static inline char const* value = R"(float)";
};
struct fp64 {
   using value_type = double;
   constexpr static inline char const* value = R"(double)";
};

struct boolean {
   using value_type = bool;
   constexpr static inline char const* value = R"(bool)";
};

using integral_type = variant<
   monostate,
   none,
   i8,
   i16,
   i32,
   i64,
   u8,
   u16,
   u32,
   u64,
   fp16a,
   fp16b,
   fp32,
   fp64,
   boolean
>;

template<typename T>
using is_integral_type = std::conditional<
      std::is_same<T, none>::value ||
      std::is_same<T, i8>::value ||
      std::is_same<T, i16>::value ||
      std::is_same<T, i32>::value ||
      std::is_same<T, i64> ::value ||
      std::is_same<T, u8>::value ||
      std::is_same<T, u16>::value ||
      std::is_same<T, u32>::value ||
      std::is_same<T, u64>::value ||
      std::is_same<T, fp16a>::value ||
      std::is_same<T, fp16b>::value ||
      std::is_same<T, fp32>::value ||
      std::is_same<T, fp64>::value ||
      std::is_same<T, boolean>::value,
      std::true_type,
      std::false_type
>;

template<typename T>
struct variable_base {

   static_assert(
      !std::is_same<T, none>::value,
      "template parameter is `none`"
   );

   using value_type = T;

   const std::string identity;

   variable_base() : identity() {}

   variable_base(std::string const& ident) : identity(ident) {}
};

template<typename T>
struct scalar : public variable_base<T> {
   static_assert(
      is_integral_type<T>::type::value,
      "variable declaration is not of tt::dsl::integral_type"
   );

   scalar() : variable_base<T>() {}

   scalar(std::string const& ident) : variable_base<T>(ident) {}

//   scalar(scalar<T> s) : variable_base<T>(s.identity) {}

   void decl(std::string & buf) const {
      buf += fmt::format("{} {}", scalar<T>::value_type::value, (*this).identity);
   }
};

using scalar_type = variant<
   monostate,
   none,
   scalar<i8>,
   scalar<i16>,
   scalar<i32>,
   scalar<i64>,
   scalar<u8>,
   scalar<u16>,
   scalar<u32>,
   scalar<u64>,
   scalar<fp16a>,
   scalar<fp16b>,
   scalar<fp32>,
   scalar<fp64>,
   scalar<boolean>
>;

template<typename T>
using is_scalar_type = typename std::conditional<
      std::is_same<T, scalar<i8> >::value ||
      std::is_same<T, scalar<i16> >::value ||
      std::is_same<T, scalar<i32> >::value ||
      std::is_same<T, scalar<i64> > ::value ||
      std::is_same<T, scalar<u8> >::value ||
      std::is_same<T, scalar<u16> >::value ||
      std::is_same<T, scalar<u32> >::value ||
      std::is_same<T, scalar<u64> >::value ||
      std::is_same<T, scalar<fp16a> >::value ||
      std::is_same<T, scalar<fp16b> >::value ||
      std::is_same<T, scalar<fp32> >::value ||
      std::is_same<T, scalar<fp64> >::value ||
      std::is_same<T, scalar<boolean> >::value,
      std::true_type,
      std::false_type
>::type;

template<typename T>
struct literal : public variable_base<T> {
   static_assert(
      is_integral_type<T>::type::value,
      "variable declaration is not of tt::dsl::integral_type"
   );

   using integral_value_type = typename T::value_type;

   literal() : variable_base<T>(), value() {}

   literal(integral_value_type val) : variable_base<T>(), value(val) {}

//   literal(literal<T> & s) : variable_base<T>(), value(s.value) {}

   integral_value_type value;

   void decl(std::string & buf) const {
      buf += fmt::format("{} {}", scalar<T>::value_type::value, (*this).identity);
   }
};

using literal_type = variant<
   monostate,
   literal<i8>,
   literal<i16>,
   literal<i32>,
   literal<i64>,
   literal<u8>,
   literal<u16>,
   literal<u32>,
   literal<u64>,
   literal<fp16a>,
   literal<fp16b>,
   literal<fp32>,
   literal<fp64>,
   literal<boolean>
>;

template<typename T>
using is_literal_type = typename std::conditional<
      std::is_same<T, literal<i8> >::value ||
      std::is_same<T, literal<i16> >::value ||
      std::is_same<T, literal<i32> >::value ||
      std::is_same<T, literal<i64> > ::value ||
      std::is_same<T, literal<u8> >::value ||
      std::is_same<T, literal<u16> >::value ||
      std::is_same<T, literal<u32> >::value ||
      std::is_same<T, literal<u64> >::value ||
      std::is_same<T, literal<fp16a> >::value ||
      std::is_same<T, literal<fp16b> >::value ||
      std::is_same<T, literal<fp32> >::value ||
      std::is_same<T, literal<fp64> >::value ||
      std::is_same<T, literal<boolean> >::value,
      std::true_type,
      std::false_type
>::type;

template< typename T >
struct array : public variable_base<T> {
   static_assert(
       is_integral_type<T>::type::value,
       "integral_type not used to define array"
   );

   using value_type = T;

   std::size_t num_dims;

   array() : 
      variable_base<T>(), num_dims(0) {}

   array(std::string const& ident) :
      variable_base<T>(ident), num_dims(0) {}

   array(std::string const& ident, const std::size_t ndims) :
      variable_base<T>(ident), num_dims(ndims) {}

//   array(array<T> & s) : variable_base<T>(s.identity), num_dims(s.num_dims) {}

   void decl(std::string & buf) const {
      buf += fmt::format("{} {} [{}]", array<T>::value_type::value, (*this).identity, num_dims);
   }
};

using array_type = variant<
   monostate,
   array<i8>,
   array<i16>,
   array<i32>,
   array<i64>,
   array<u8>,
   array<u16>,
   array<u32>,
   array<u64>,
   array<fp16a>,
   array<fp16b>,
   array<fp32>,
   array<fp64>,
   array<boolean>
>;

template<typename T>
using is_array_type = typename std::conditional<
      std::is_same<T, array<i8> >::value ||
      std::is_same<T, array<i16> >::value ||
      std::is_same<T, array<i32> >::value ||
      std::is_same<T, array<i64> > ::value ||
      std::is_same<T, array<u8> >::value ||
      std::is_same<T, array<u16> >::value ||
      std::is_same<T, array<u32> >::value ||
      std::is_same<T, array<u64> >::value ||
      std::is_same<T, array<fp16a> >::value ||
      std::is_same<T, array<fp16b> >::value ||
      std::is_same<T, array<fp32> >::value ||
      std::is_same<T, array<fp64> >::value ||
      std::is_same<T, array<boolean> >::value,
      std::true_type,
      std::false_type
>::type;

template< typename T >
struct matrix : variable_base<T> {
   static_assert(
      is_integral_type<T>::type::value,
      "integral_type not used to define matrix"
   );

   using value_type = T;

   std::size_t num_dims;
   std::vector<std::size_t> dimensions;

   matrix() :
      variable_base<T>(), num_dims(0), dimensions() {}

   matrix(std::string const& ident) :
      variable_base<T>(ident), num_dims(0), dimensions() {}

   matrix(std::string const& ident, std::initializer_list<std::size_t> values) :
      variable_base<T>(ident), num_dims(values.size()), dimensions(values) {}

   matrix(std::string const& ident, std::vector<std::size_t> const& values) :
      variable_base<T>(ident), num_dims(values.size()), dimensions(values) {}

//   matrix(matrix<T> & s) : variable_base<T>(s.identity), num_dims(s.values.size()), dimensions(s.dimensions) {}

   void decl(std::string & buf) const {
      buf += fmt::format("{} {} ", array<T>::value_type::value, (*this).identity);
      for(const auto & dim : dimensions) {
         buf += fmt::format("[{}]", dim);
      }
   }
};

using matrix_type = variant<
   monostate,
   matrix<i8>,
   matrix<i16>,
   matrix<i32>,
   matrix<i64>,
   matrix<u8>,
   matrix<u16>,
   matrix<u32>,
   matrix<u64>,
   matrix<fp16a>,
   matrix<fp16b>,
   matrix<fp32>,
   matrix<fp64>,
   matrix<boolean>
>;

template<typename T>
using is_matrix_type = typename std::conditional<
      std::is_same<T, matrix<i8> >::value ||
      std::is_same<T, matrix<i16> >::value ||
      std::is_same<T, matrix<i32> >::value ||
      std::is_same<T, matrix<i64> >::value ||
      std::is_same<T, matrix<u8> >::value ||
      std::is_same<T, matrix<u16> >::value ||
      std::is_same<T, matrix<u32> >::value ||
      std::is_same<T, matrix<u64> >::value ||
      std::is_same<T, matrix<fp16a> >::value ||
      std::is_same<T, matrix<fp16b> >::value ||
      std::is_same<T, matrix<fp32> >::value ||
      std::is_same<T, matrix<fp64> >::value ||
      std::is_same<T, matrix<boolean> >::value,
      std::true_type,
      std::false_type
>::type;

template<typename T>
struct underlying_value_type {
   using value_type = T;
};

template<typename T>
struct underlying_value_type< scalar<T> > {
   using value_type = typename scalar<T>::value_type;
};

template<typename T>
struct underlying_value_type< literal<T> > {
   using value_type = typename literal<T>::value_type;
};

template<typename T>
struct underlying_value_type< array<T> > {
   using value_type = typename array<T>::value_type;
};

template<typename T>
struct underlying_value_type< matrix<T> > {
   using value_type = typename matrix<T>::value_type;
};

template<typename T>
struct pointer : public variable_base< typename underlying_value_type<T>::value_type > {
   static_assert(
      !std::is_same<T, none>::value ||
      is_scalar_type<T>::type::value ||
      is_literal_type<T>::type::value ||
      is_array_type<T>::type::value ||
      is_matrix_type<T>::type::value,
      "variable declaration is not of tt::dsl::integral_type"
   );

   pointer() : variable_base< typename underlying_value_type<T>::value_type >() {}

   pointer(std::string const& ident) : variable_base< typename underlying_value_type<T>::value_type >(ident) {}

//   pointer(pointer<T> & s) : variable_base< typename underlying_value_type<T>::value_type >(s.identity) {}

   void decl(std::string & buf) const {
      buf += fmt::format("{} * {}", pointer<T>::value_type::value, (*this).identity);
   }
};

using pointer_type = variant<
   monostate,
   pointer<scalar<i8>>,
   pointer<scalar<i16>>,
   pointer<scalar<i32>>,
   pointer<scalar<i64>>,
   pointer<scalar<u8>>,
   pointer<scalar<u16>>,
   pointer<scalar<u32>>,
   pointer<scalar<u64>>,
   pointer<scalar<fp16a>>,
   pointer<scalar<fp16b>>,
   pointer<scalar<fp32>>,
   pointer<scalar<fp64>>,
   pointer<scalar<boolean>>,
   pointer<array<i8>>,
   pointer<array<i16>>,
   pointer<array<i32>>,
   pointer<array<i64>>,
   pointer<array<u8>>,
   pointer<array<u16>>,
   pointer<array<u32>>,
   pointer<array<u64>>,
   pointer<array<fp16a>>,
   pointer<array<fp16b>>,
   pointer<array<fp32>>,
   pointer<array<fp64>>,
   pointer<array<boolean>>,
   pointer<matrix<i8>>,
   pointer<matrix<i16>>,
   pointer<matrix<i32>>,
   pointer<matrix<i64>>,
   pointer<matrix<u8>>,
   pointer<matrix<u16>>,
   pointer<matrix<u32>>,
   pointer<matrix<u64>>,
   pointer<matrix<fp16a>>,
   pointer<matrix<fp16b>>,
   pointer<matrix<fp32>>,
   pointer<matrix<fp64>>,
   pointer<matrix<boolean>>
>;

template<typename T>
using is_pointer_type = typename std::conditional<
      std::is_same<T, pointer<scalar<i8>> >::value ||
      std::is_same<T, pointer<scalar<i16>> >::value ||
      std::is_same<T, pointer<scalar<i32>> >::value ||
      std::is_same<T, pointer<scalar<i64>> > ::value ||
      std::is_same<T, pointer<scalar<u8>> >::value ||
      std::is_same<T, pointer<scalar<u16>> >::value ||
      std::is_same<T, pointer<scalar<u32>> >::value ||
      std::is_same<T, pointer<scalar<u64>> >::value ||
      std::is_same<T, pointer<scalar<fp16a>> >::value ||
      std::is_same<T, pointer<scalar<fp16b>> >::value ||
      std::is_same<T, pointer<scalar<fp32>> >::value ||
      std::is_same<T, pointer<scalar<fp64>> >::value ||
      std::is_same<T, pointer<scalar<boolean>> >::value ||
      std::is_same<T, pointer<array<i8>> >::value ||
      std::is_same<T, pointer<array<i16>> >::value ||
      std::is_same<T, pointer<array<i32>> >::value ||
      std::is_same<T, pointer<array<i64>> > ::value ||
      std::is_same<T, pointer<array<u8>> >::value ||
      std::is_same<T, pointer<array<u16>> >::value ||
      std::is_same<T, pointer<array<u32>> >::value ||
      std::is_same<T, pointer<array<u64>> >::value ||
      std::is_same<T, pointer<array<fp16a>> >::value ||
      std::is_same<T, pointer<array<fp16b>> >::value ||
      std::is_same<T, pointer<array<fp32>> >::value ||
      std::is_same<T, pointer<array<fp64>> >::value ||
      std::is_same<T, pointer<array<boolean>> >::value ||
      std::is_same<T, pointer<matrix<i8>> >::value ||
      std::is_same<T, pointer<matrix<i16>> >::value ||
      std::is_same<T, pointer<matrix<i32>> >::value ||
      std::is_same<T, pointer<matrix<i64>> > ::value ||
      std::is_same<T, pointer<matrix<u8>> >::value ||
      std::is_same<T, pointer<matrix<u16>> >::value ||
      std::is_same<T, pointer<matrix<u32>> >::value ||
      std::is_same<T, pointer<matrix<u64>> >::value ||
      std::is_same<T, pointer<matrix<fp16a>> >::value ||
      std::is_same<T, pointer<matrix<fp16b>> >::value ||
      std::is_same<T, pointer<matrix<fp32>> >::value ||
      std::is_same<T, pointer<matrix<fp64>> >::value ||
      std::is_same<T, pointer<matrix<boolean>> >::value,
      std::true_type,
      std::false_type
>::type;

template<typename T>
struct reference : public variable_base< typename underlying_value_type<T>::value_type > {
   static_assert(
      is_scalar_type<T>::type::value ||
      is_array_type<T>::type::value ||
      is_matrix_type<T>::type::value,
      "variable declaration is not of tt::dsl::integral_type"
   );

   reference(std::string const& ident) : variable_base< typename underlying_value_type<T>::value_type >(ident) {}

//   reference(reference<T> & s) : variable_base< typename underlying_value_type<T>::value_type >(s.identity) {}

   void decl(std::string & buf) const {
      buf += fmt::format("{} * {}", reference<T>::value_type::value, (*this).identity);
   }
};

using reference_type = variant<
   monostate,
   reference<scalar<i8>>,
   reference<scalar<i16>>,
   reference<scalar<i32>>,
   reference<scalar<i64>>,
   reference<scalar<u8>>,
   reference<scalar<u16>>,
   reference<scalar<u32>>,
   reference<scalar<u64>>,
   reference<scalar<fp16a>>,
   reference<scalar<fp16b>>,
   reference<scalar<fp32>>,
   reference<scalar<fp64>>,
   reference<scalar<boolean>>,
   reference<array<i8>>,
   reference<array<i16>>,
   reference<array<i32>>,
   reference<array<i64>>,
   reference<array<u8>>,
   reference<array<u16>>,
   reference<array<u32>>,
   reference<array<u64>>,
   reference<array<fp16a>>,
   reference<array<fp16b>>,
   reference<array<fp32>>,
   reference<array<fp64>>,
   reference<array<boolean>>,
   reference<matrix<i8>>,
   reference<matrix<i16>>,
   reference<matrix<i32>>,
   reference<matrix<i64>>,
   reference<matrix<u8>>,
   reference<matrix<u16>>,
   reference<matrix<u32>>,
   reference<matrix<u64>>,
   reference<matrix<fp16a>>,
   reference<matrix<fp16b>>,
   reference<matrix<fp32>>,
   reference<matrix<fp64>>,
   reference<matrix<boolean>>
>;

template<typename T>
using is_reference_type = typename std::conditional<
      std::is_same<T, reference<scalar<i8>> >::value ||
      std::is_same<T, reference<scalar<i16>> >::value ||
      std::is_same<T, reference<scalar<i32>> >::value ||
      std::is_same<T, reference<scalar<i64>> > ::value ||
      std::is_same<T, reference<scalar<u8>> >::value ||
      std::is_same<T, reference<scalar<u16>> >::value ||
      std::is_same<T, reference<scalar<u32>> >::value ||
      std::is_same<T, reference<scalar<u64>> >::value ||
      std::is_same<T, reference<scalar<fp16a>> >::value ||
      std::is_same<T, reference<scalar<fp16b>> >::value ||
      std::is_same<T, reference<scalar<fp32>> >::value ||
      std::is_same<T, reference<scalar<fp64>> >::value ||
      std::is_same<T, reference<scalar<boolean>> >::value ||
      std::is_same<T, reference<array<i8>> >::value ||
      std::is_same<T, reference<array<i16>> >::value ||
      std::is_same<T, reference<array<i32>> >::value ||
      std::is_same<T, reference<array<i64>> > ::value ||
      std::is_same<T, reference<array<u8>> >::value ||
      std::is_same<T, reference<array<u16>> >::value ||
      std::is_same<T, reference<array<u32>> >::value ||
      std::is_same<T, reference<array<u64>> >::value ||
      std::is_same<T, reference<array<fp16a>> >::value ||
      std::is_same<T, reference<array<fp16b>> >::value ||
      std::is_same<T, reference<array<fp32>> >::value ||
      std::is_same<T, reference<array<fp64>> >::value ||
      std::is_same<T, reference<array<boolean>> >::value ||
      std::is_same<T, reference<matrix<i8>> >::value ||
      std::is_same<T, reference<matrix<i16>> >::value ||
      std::is_same<T, reference<matrix<i32>> >::value ||
      std::is_same<T, reference<matrix<i64>> > ::value ||
      std::is_same<T, reference<matrix<u8>> >::value ||
      std::is_same<T, reference<matrix<u16>> >::value ||
      std::is_same<T, reference<matrix<u32>> >::value ||
      std::is_same<T, reference<matrix<u64>> >::value ||
      std::is_same<T, reference<matrix<fp16a>> >::value ||
      std::is_same<T, reference<matrix<fp16b>> >::value ||
      std::is_same<T, reference<matrix<fp32>> >::value ||
      std::is_same<T, reference<matrix<fp64>> >::value ||
      std::is_same<T, reference<matrix<boolean>> >::value,
      std::true_type,
      std::false_type
>::type;

using placeholder_value_type = variant<
   monostate,
   scalar<i8>,
   scalar<i16>,
   scalar<i32>,
   scalar<i64>,
   scalar<u8>,
   scalar<u16>,
   scalar<u32>,
   scalar<u64>,
   scalar<fp16a>,
   scalar<fp16b>,
   scalar<fp32>,
   scalar<fp64>,
   scalar<boolean>,
   array<i8>,
   array<i16>,
   array<i32>,
   array<i64>,
   array<u8>,
   array<u16>,
   array<u32>,
   array<u64>,
   array<fp16a>,
   array<fp16b>,
   array<fp32>,
   array<fp64>,
   array<boolean>,
   matrix<i8>,
   matrix<i16>,
   matrix<i32>,
   matrix<i64>,
   matrix<u8>,
   matrix<u16>,
   matrix<u32>,
   matrix<u64>,
   matrix<fp16a>,
   matrix<fp16b>,
   matrix<fp32>,
   matrix<fp64>,
   matrix<boolean>
>;

template<typename T>
using is_placeholder_variable_type = std::conditional<
   is_scalar_type<T>::type::value ||
   is_literal_type<T>::type::value ||
   is_array_type<T>::type::value ||
   is_matrix_type<T>::type::value,
   std::true_type,
   std::false_type
>;

struct placeholder_arg_base {

   using placeholder_narg = std::integral_constant<std::size_t, 8UL>;

   const placeholder_value_type node;
   const std::size_t identifier;
   const std::string identity;

   template<typename T>
   bool is_type() { return holds_alternative<T>(node); }

   std::size_t arg_n() { return identifier % placeholder_narg::value; }

   bool has_invalid_identity() { return identity.compare("{}_{}_{}") == 0UL; }
   
   template<typename T>
   std::string argument_str_template() const {
      static_assert(is_placeholder_variable_type<T>::type::value, "argument_str_template was passed a non-placeholder_variable_type type");
      using value_type = typename T::value_type;
      return fmt::format("{} {}", value_type::value, identity);
   }   

   void argument_str(std::string & buf) const {
     if(holds_alternative<scalar<i8>>(node)) {
        buf += argument_str_template<scalar<i8>>();
     }
     else if(holds_alternative<scalar<i16>>(node)) {
        buf += argument_str_template<scalar<i16>>();
     }
     else if(holds_alternative<scalar<i32>>(node)) {
        buf += argument_str_template<scalar<i32>>();
     }
     else if(holds_alternative<scalar<i64>>(node)) {
        buf += argument_str_template<scalar<i64>>();
     }
     else if(holds_alternative<scalar<u8>>(node)) {
        buf += argument_str_template<scalar<u8>>();
     }
     else if(holds_alternative<scalar<u16>>(node)) {
        buf += argument_str_template<scalar<u16>>();
     }
     else if(holds_alternative<scalar<u32>>(node)) {
        buf += argument_str_template<scalar<u32>>();
     }
     else if(holds_alternative<scalar<u64>>(node)) {
        buf += argument_str_template<scalar<u64>>();
     }
     else if(holds_alternative<scalar<fp16a>>(node)) {
        buf += argument_str_template<scalar<fp16b>>();
     }
     else if(holds_alternative<scalar<fp16b>>(node)) {
        buf += argument_str_template<scalar<fp16b>>();
     }
     else if(holds_alternative<scalar<fp32>>(node)) {
        buf += argument_str_template<scalar<fp32>>();
     }
     else if(holds_alternative<scalar<fp64>>(node)) {
        buf += argument_str_template<scalar<fp64>>();
     }
     else if(holds_alternative<scalar<boolean>>(node)) {
        buf += argument_str_template<scalar<boolean>>();
     }
     else if(holds_alternative<array<i8>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<i8>>());
     }
     else if(holds_alternative<array<i16>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<i16>>());
     }
     else if(holds_alternative<array<i32>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<i32>>());
     }
     else if(holds_alternative<array<i64>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<i64>>());
     }
     else if(holds_alternative<array<u8>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<u8>>());
     }
     else if(holds_alternative<array<u16>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<u16>>());
     }
     else if(holds_alternative<array<u32>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<u32>>());
     }
     else if(holds_alternative<array<u64>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<u64>>());
     }
     else if(holds_alternative<array<fp16a>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<fp16b>>());
     }
     else if(holds_alternative<array<fp16b>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<fp16b>>());
     }
     else if(holds_alternative<array<fp32>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<fp32>>());
     }
     else if(holds_alternative<array<fp64>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<fp64>>());
     }
     else if(holds_alternative<array<boolean>>(node)) {
        buf += fmt::format("{} []", argument_str_template<matrix<boolean>>());
     }
     else if(holds_alternative<matrix<i8>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<i8>>());
     }
     else if(holds_alternative<matrix<i16>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<i16>>());
     }
     else if(holds_alternative<matrix<i32>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<i32>>());
     }
     else if(holds_alternative<matrix<i64>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<i64>>());
     }
     else if(holds_alternative<matrix<u8>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<u8>>());
     }
     else if(holds_alternative<matrix<u16>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<u16>>());
     }
     else if(holds_alternative<matrix<u32>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<u32>>());
     }
     else if(holds_alternative<matrix<u64>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<u64>>());
     }
     else if(holds_alternative<matrix<fp16a>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<fp16b>>());
     }
     else if(holds_alternative<matrix<fp16b>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<fp16b>>());
     }
     else if(holds_alternative<matrix<fp32>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<fp32>>());
     }
     else if(holds_alternative<matrix<fp64>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<fp64>>());
     }
     else if(holds_alternative<matrix<boolean>>(node)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<boolean>>());
     }

     buf += "void";
   }

   void decl(std::string & buf) const {
      argument_str(buf);
   }

   template<typename T, std::size_t Identifier>
   static inline std::string calc_identity() {
      using identifier_value_type =
         std::integral_constant<std::size_t, Identifier % placeholder_narg::value>;

      if constexpr(std::is_same<T, scalar<i8>>::value) {
         return fmt::format("{}_{}_{}", "s", "i8", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, scalar<i16>>::value) {
         return fmt::format("{}_{}_{}", "s", "i16", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, scalar<i32>>::value) {
         return fmt::format("{}_{}_{}", "s", "i32", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, scalar<i64>>::value) {
         return fmt::format("{}_{}_{}", "s", "i64", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, scalar<u8>>::value) {
         return fmt::format("{}_{}_{}", "s", "u8", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, scalar<u16>>::value) {
         return fmt::format("{}_{}_{}", "s", "u16", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, scalar<u32>>::value) {
         return fmt::format("{}_{}_{}", "s", "u32", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, scalar<u64>>::value) {
         return fmt::format("{}_{}_{}", "s", "u64", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, scalar<fp16a>>::value) {
         return fmt::format("{}_{}_{}", "s", "fp16a", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, scalar<fp16b>>::value) {
         return fmt::format("{}_{}_{}", "s", "fp16b", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, scalar<fp32>>::value) {
         return fmt::format("{}_{}_{}", "s", "fp32", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, scalar<fp64>>::value) {
         return fmt::format("{}_{}_{}", "s", "fp64", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, scalar<boolean>>::value) {
         return fmt::format("{}_{}_{}", "s", "bool", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<i8>>::value) {
         return fmt::format("{}_{}_{}", "a", "i8", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<i16>>::value) {
         return fmt::format("{}_{}_{}", "a", "i16", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<i32>>::value) {
         return fmt::format("{}_{}_{}", "a", "i32", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<i64>>::value) {
         return fmt::format("{}_{}_{}", "a", "i64", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<u8>>::value) {
         return fmt::format("{}_{}_{}", "a", "u8", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<u16>>::value) {
         return fmt::format("{}_{}_{}", "a", "u16", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<u32>>::value) {
         return fmt::format("{}_{}_{}", "a", "u32", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<u64>>::value) {
         return fmt::format("{}_{}_{}", "a", "u64", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<fp16a>>::value) {
         return fmt::format("{}_{}_{}", "a", "fp16a", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<fp16b>>::value) {
         return fmt::format("{}_{}_{}", "a", "fp16b", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<fp32>>::value) {
         return fmt::format("{}_{}_{}", "a", "fp32", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<fp64>>::value) {
         return fmt::format("{}_{}_{}", "a", "fp64", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, array<boolean>>::value) {
         return fmt::format("{}_{}_{}", "a", "bool", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<i8>>::value) {
         return fmt::format("{}_{}_{}", "m", "i8", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<i16>>::value) {
         return fmt::format("{}_{}_{}", "m", "i16", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<i32>>::value) {
         return fmt::format("{}_{}_{}", "m", "i32", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<i64>>::value) {
         return fmt::format("{}_{}_{}", "m", "i64", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<u8>>::value) {
         return fmt::format("{}_{}_{}", "m", "u8", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<u16>>::value) {
         return fmt::format("{}_{}_{}", "m", "u16", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<u32>>::value) {
         return fmt::format("{}_{}_{}", "m", "u32", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<u64>>::value) {
         return fmt::format("{}_{}_{}", "m", "u64", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<fp16a>>::value) {
         return fmt::format("{}_{}_{}", "m", "fp16a", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<fp16b>>::value) {
         return fmt::format("{}_{}_{}", "m", "fp16b", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<fp32>>::value) {
         return fmt::format("{}_{}_{}", "m", "fp32", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<fp64>>::value) {
         return fmt::format("{}_{}_{}", "m", "fp64", std::to_string(identifier_value_type::value));
      }
      else if constexpr(std::is_same<T, matrix<boolean>>::value) {
         return fmt::format("{}_{}_{}", "m", "bool", std::to_string(identifier_value_type::value));
      }

      return "{}_{}_{}";
   }

};

template<std::size_t NumArg>
struct placeholder_arg : public placeholder_arg_base {
   using num_arg = std::integral_constant<std::size_t, NumArg>;
};

using placeholder_arg_1 = placeholder_arg<1>;
using placeholder_arg_2 = placeholder_arg<2>;
using placeholder_arg_3 = placeholder_arg<3>;
using placeholder_arg_4 = placeholder_arg<4>;
using placeholder_arg_5 = placeholder_arg<5>;
using placeholder_arg_6 = placeholder_arg<6>;
using placeholder_arg_7 = placeholder_arg<7>;
using placeholder_arg_8 = placeholder_arg<8>;

using placeholder = variant<
   monostate,
   placeholder_arg_1,
   placeholder_arg_2,
   placeholder_arg_3,
   placeholder_arg_4,
   placeholder_arg_5,
   placeholder_arg_6,
   placeholder_arg_7,
   placeholder_arg_8
>;

template<typename T>
using is_placeholder_arg_type = std::conditional<
   std::is_same< placeholder_arg_1, T>::value ||
   std::is_same< placeholder_arg_2, T>::value ||
   std::is_same< placeholder_arg_3, T>::value ||
   std::is_same< placeholder_arg_4, T>::value ||
   std::is_same< placeholder_arg_5, T>::value ||
   std::is_same< placeholder_arg_6, T>::value ||
   std::is_same< placeholder_arg_8, T>::value,
   std::true_type,
   std::false_type
>;

static inline placeholder const s_i8_1 = placeholder_arg_1{placeholder_value_type{scalar<i8>{}}, 0, placeholder_arg_base::calc_identity<scalar<i8>, 0>()};
static inline placeholder const s_i8_2 = placeholder_arg_2{placeholder_value_type{scalar<i8>{}}, 1, placeholder_arg_base::calc_identity<scalar<i8>, 1>()};
static inline placeholder const s_i8_3 = placeholder_arg_3{placeholder_value_type{scalar<i8>{}}, 2, placeholder_arg_base::calc_identity<scalar<i8>, 2>()};
static inline placeholder const s_i8_4 = placeholder_arg_4{placeholder_value_type{scalar<i8>{}}, 3, placeholder_arg_base::calc_identity<scalar<i8>, 3>()};
static inline placeholder const s_i8_5 = placeholder_arg_5{placeholder_value_type{scalar<i8>{}}, 4, placeholder_arg_base::calc_identity<scalar<i8>, 4>()};
static inline placeholder const s_i8_6 = placeholder_arg_6{placeholder_value_type{scalar<i8>{}}, 5, placeholder_arg_base::calc_identity<scalar<i8>, 5>()};
static inline placeholder const s_i8_7 = placeholder_arg_7{placeholder_value_type{scalar<i8>{}}, 6, placeholder_arg_base::calc_identity<scalar<i8>, 6>()};
static inline placeholder const s_i8_8 = placeholder_arg_8{placeholder_value_type{scalar<i8>{}}, 7, placeholder_arg_base::calc_identity<scalar<i8>, 7>()};

static inline placeholder const s_i16_1 = placeholder_arg_1{placeholder_value_type{scalar<i16>{}}, 8, placeholder_arg_base::calc_identity<scalar<i16>, 8>()};
static inline placeholder const s_i16_2 = placeholder_arg_2{placeholder_value_type{scalar<i16>{}}, 9, placeholder_arg_base::calc_identity<scalar<i16>, 9>()};
static inline placeholder const s_i16_3 = placeholder_arg_3{placeholder_value_type{scalar<i16>{}}, 10, placeholder_arg_base::calc_identity<scalar<i16>, 10>()};
static inline placeholder const s_i16_4 = placeholder_arg_4{placeholder_value_type{scalar<i16>{}}, 11, placeholder_arg_base::calc_identity<scalar<i16>, 11>()};
static inline placeholder const s_i16_5 = placeholder_arg_5{placeholder_value_type{scalar<i16>{}}, 12, placeholder_arg_base::calc_identity<scalar<i16>, 12>()};
static inline placeholder const s_i16_6 = placeholder_arg_6{placeholder_value_type{scalar<i16>{}}, 13, placeholder_arg_base::calc_identity<scalar<i16>, 13>()};
static inline placeholder const s_i16_7 = placeholder_arg_7{placeholder_value_type{scalar<i16>{}}, 14, placeholder_arg_base::calc_identity<scalar<i16>, 14>()};
static inline placeholder const s_i16_8 = placeholder_arg_8{placeholder_value_type{scalar<i16>{}}, 15, placeholder_arg_base::calc_identity<scalar<i16>, 15>()};

static inline placeholder const s_i32_1 = placeholder_arg_1{placeholder_value_type{scalar<i32>{}}, 16, placeholder_arg_base::calc_identity<scalar<i32>, 16>()};
static inline placeholder const s_i32_2 = placeholder_arg_2{placeholder_value_type{scalar<i32>{}}, 17, placeholder_arg_base::calc_identity<scalar<i32>, 17>()};
static inline placeholder const s_i32_3 = placeholder_arg_3{placeholder_value_type{scalar<i32>{}}, 18, placeholder_arg_base::calc_identity<scalar<i32>, 18>()};
static inline placeholder const s_i32_4 = placeholder_arg_4{placeholder_value_type{scalar<i32>{}}, 19, placeholder_arg_base::calc_identity<scalar<i32>, 19>()};
static inline placeholder const s_i32_5 = placeholder_arg_5{placeholder_value_type{scalar<i32>{}}, 20, placeholder_arg_base::calc_identity<scalar<i32>, 20>()};
static inline placeholder const s_i32_6 = placeholder_arg_6{placeholder_value_type{scalar<i32>{}}, 21, placeholder_arg_base::calc_identity<scalar<i32>, 21>()};
static inline placeholder const s_i32_7 = placeholder_arg_7{placeholder_value_type{scalar<i32>{}}, 22, placeholder_arg_base::calc_identity<scalar<i32>, 22>()};
static inline placeholder const s_i32_8 = placeholder_arg_8{placeholder_value_type{scalar<i32>{}}, 23, placeholder_arg_base::calc_identity<scalar<i32>, 23>()};

static inline placeholder const s_i64_1 = placeholder_arg_1{placeholder_value_type{scalar<i64>{}}, 24, placeholder_arg_base::calc_identity<scalar<i64>, 24>()};
static inline placeholder const s_i64_2 = placeholder_arg_2{placeholder_value_type{scalar<i64>{}}, 25, placeholder_arg_base::calc_identity<scalar<i64>, 25>()};
static inline placeholder const s_i64_3 = placeholder_arg_3{placeholder_value_type{scalar<i64>{}}, 26, placeholder_arg_base::calc_identity<scalar<i64>, 26>()};
static inline placeholder const s_i64_4 = placeholder_arg_4{placeholder_value_type{scalar<i64>{}}, 27, placeholder_arg_base::calc_identity<scalar<i64>, 27>()};
static inline placeholder const s_i64_5 = placeholder_arg_5{placeholder_value_type{scalar<i64>{}}, 28, placeholder_arg_base::calc_identity<scalar<i64>, 28>()};
static inline placeholder const s_i64_6 = placeholder_arg_6{placeholder_value_type{scalar<i64>{}}, 29, placeholder_arg_base::calc_identity<scalar<i64>, 29>()};
static inline placeholder const s_i64_7 = placeholder_arg_7{placeholder_value_type{scalar<i64>{}}, 30, placeholder_arg_base::calc_identity<scalar<i64>, 30>()};
static inline placeholder const s_i64_8 = placeholder_arg_8{placeholder_value_type{scalar<i64>{}}, 31, placeholder_arg_base::calc_identity<scalar<i64>, 31>()};

static inline placeholder const s_u8_1 = placeholder_arg_1{placeholder_value_type{scalar<u8>{}}, 32, placeholder_arg_base::calc_identity<scalar<u8>, 32>()};
static inline placeholder const s_u8_2 = placeholder_arg_2{placeholder_value_type{scalar<u8>{}}, 33, placeholder_arg_base::calc_identity<scalar<u8>, 33>()};
static inline placeholder const s_u8_3 = placeholder_arg_3{placeholder_value_type{scalar<u8>{}}, 34, placeholder_arg_base::calc_identity<scalar<u8>, 34>()};
static inline placeholder const s_u8_4 = placeholder_arg_4{placeholder_value_type{scalar<u8>{}}, 35, placeholder_arg_base::calc_identity<scalar<u8>, 35>()};
static inline placeholder const s_u8_5 = placeholder_arg_5{placeholder_value_type{scalar<u8>{}}, 36, placeholder_arg_base::calc_identity<scalar<u8>, 36>()};
static inline placeholder const s_u8_6 = placeholder_arg_6{placeholder_value_type{scalar<u8>{}}, 37, placeholder_arg_base::calc_identity<scalar<u8>, 37>()};
static inline placeholder const s_u8_7 = placeholder_arg_7{placeholder_value_type{scalar<u8>{}}, 38, placeholder_arg_base::calc_identity<scalar<u8>, 38>()};
static inline placeholder const s_u8_8 = placeholder_arg_8{placeholder_value_type{scalar<u8>{}}, 39, placeholder_arg_base::calc_identity<scalar<u8>, 39>()};

static inline placeholder const s_u16_1 = placeholder_arg_1{placeholder_value_type{scalar<u16>{}}, 40, placeholder_arg_base::calc_identity<scalar<u16>, 40>()};
static inline placeholder const s_u16_2 = placeholder_arg_2{placeholder_value_type{scalar<u16>{}}, 41, placeholder_arg_base::calc_identity<scalar<u16>, 41>()};
static inline placeholder const s_u16_3 = placeholder_arg_3{placeholder_value_type{scalar<u16>{}}, 42, placeholder_arg_base::calc_identity<scalar<u16>, 42>()};
static inline placeholder const s_u16_4 = placeholder_arg_4{placeholder_value_type{scalar<u16>{}}, 43, placeholder_arg_base::calc_identity<scalar<u16>, 43>()};
static inline placeholder const s_u16_5 = placeholder_arg_5{placeholder_value_type{scalar<u16>{}}, 44, placeholder_arg_base::calc_identity<scalar<u16>, 44>()};
static inline placeholder const s_u16_6 = placeholder_arg_6{placeholder_value_type{scalar<u16>{}}, 45, placeholder_arg_base::calc_identity<scalar<u16>, 45>()};
static inline placeholder const s_u16_7 = placeholder_arg_7{placeholder_value_type{scalar<u16>{}}, 46, placeholder_arg_base::calc_identity<scalar<u16>, 46>()};
static inline placeholder const s_u16_8 = placeholder_arg_8{placeholder_value_type{scalar<u16>{}}, 47, placeholder_arg_base::calc_identity<scalar<u16>, 47>()};

static inline placeholder const s_u32_1 = placeholder_arg_1{placeholder_value_type{scalar<u32>{}}, 48, placeholder_arg_base::calc_identity<scalar<u32>, 48>()};
static inline placeholder const s_u32_2 = placeholder_arg_2{placeholder_value_type{scalar<u32>{}}, 49, placeholder_arg_base::calc_identity<scalar<u32>, 49>()};
static inline placeholder const s_u32_3 = placeholder_arg_3{placeholder_value_type{scalar<u32>{}}, 50, placeholder_arg_base::calc_identity<scalar<u32>, 50>()};
static inline placeholder const s_u32_4 = placeholder_arg_4{placeholder_value_type{scalar<u32>{}}, 51, placeholder_arg_base::calc_identity<scalar<u32>, 51>()};
static inline placeholder const s_u32_5 = placeholder_arg_5{placeholder_value_type{scalar<u32>{}}, 52, placeholder_arg_base::calc_identity<scalar<u32>, 52>()};
static inline placeholder const s_u32_6 = placeholder_arg_6{placeholder_value_type{scalar<u32>{}}, 53, placeholder_arg_base::calc_identity<scalar<u32>, 53>()};
static inline placeholder const s_u32_7 = placeholder_arg_7{placeholder_value_type{scalar<u32>{}}, 54, placeholder_arg_base::calc_identity<scalar<u32>, 54>()};
static inline placeholder const s_u32_8 = placeholder_arg_8{placeholder_value_type{scalar<u32>{}}, 55, placeholder_arg_base::calc_identity<scalar<u32>, 55>()};

static inline placeholder const s_u64_1 = placeholder_arg_1{placeholder_value_type{scalar<u64>{}}, 56, placeholder_arg_base::calc_identity<scalar<u64>, 56>()};
static inline placeholder const s_u64_2 = placeholder_arg_2{placeholder_value_type{scalar<u64>{}}, 57, placeholder_arg_base::calc_identity<scalar<u64>, 57>()};
static inline placeholder const s_u64_3 = placeholder_arg_3{placeholder_value_type{scalar<u64>{}}, 58, placeholder_arg_base::calc_identity<scalar<u64>, 58>()};
static inline placeholder const s_u64_4 = placeholder_arg_4{placeholder_value_type{scalar<u64>{}}, 59, placeholder_arg_base::calc_identity<scalar<u64>, 59>()};
static inline placeholder const s_u64_5 = placeholder_arg_5{placeholder_value_type{scalar<u64>{}}, 60, placeholder_arg_base::calc_identity<scalar<u64>, 60>()};
static inline placeholder const s_u64_6 = placeholder_arg_6{placeholder_value_type{scalar<u64>{}}, 61, placeholder_arg_base::calc_identity<scalar<u64>, 61>()};
static inline placeholder const s_u64_7 = placeholder_arg_7{placeholder_value_type{scalar<u64>{}}, 62, placeholder_arg_base::calc_identity<scalar<u64>, 62>()};
static inline placeholder const s_u64_8 = placeholder_arg_8{placeholder_value_type{scalar<u64>{}}, 63, placeholder_arg_base::calc_identity<scalar<u64>, 63>()};

static inline placeholder const s_fp16a_1 = placeholder_arg_1{placeholder_value_type{scalar<fp16a>{}}, 64, placeholder_arg_base::calc_identity<scalar<fp16a>, 64>()};
static inline placeholder const s_fp16a_2 = placeholder_arg_2{placeholder_value_type{scalar<fp16a>{}}, 65, placeholder_arg_base::calc_identity<scalar<fp16a>, 65>()};
static inline placeholder const s_fp16a_3 = placeholder_arg_3{placeholder_value_type{scalar<fp16a>{}}, 66, placeholder_arg_base::calc_identity<scalar<fp16a>, 66>()};
static inline placeholder const s_fp16a_4 = placeholder_arg_4{placeholder_value_type{scalar<fp16a>{}}, 67, placeholder_arg_base::calc_identity<scalar<fp16a>, 67>()};
static inline placeholder const s_fp16a_5 = placeholder_arg_5{placeholder_value_type{scalar<fp16a>{}}, 68, placeholder_arg_base::calc_identity<scalar<fp16a>, 68>()};
static inline placeholder const s_fp16a_6 = placeholder_arg_6{placeholder_value_type{scalar<fp16a>{}}, 69, placeholder_arg_base::calc_identity<scalar<fp16a>, 69>()};
static inline placeholder const s_fp16a_7 = placeholder_arg_7{placeholder_value_type{scalar<fp16a>{}}, 70, placeholder_arg_base::calc_identity<scalar<fp16a>, 70>()};
static inline placeholder const s_fp16a_8 = placeholder_arg_8{placeholder_value_type{scalar<fp16a>{}}, 71, placeholder_arg_base::calc_identity<scalar<fp16a>, 71>()};

static inline placeholder const s_fp16b_1 = placeholder_arg_1{placeholder_value_type{scalar<fp16b>{}}, 72, placeholder_arg_base::calc_identity<scalar<fp16b>, 72>()};
static inline placeholder const s_fp16b_2 = placeholder_arg_2{placeholder_value_type{scalar<fp16b>{}}, 73, placeholder_arg_base::calc_identity<scalar<fp16b>, 73>()};
static inline placeholder const s_fp16b_3 = placeholder_arg_3{placeholder_value_type{scalar<fp16b>{}}, 74, placeholder_arg_base::calc_identity<scalar<fp16b>, 74>()};
static inline placeholder const s_fp16b_4 = placeholder_arg_4{placeholder_value_type{scalar<fp16b>{}}, 75, placeholder_arg_base::calc_identity<scalar<fp16b>, 75>()};
static inline placeholder const s_fp16b_5 = placeholder_arg_5{placeholder_value_type{scalar<fp16b>{}}, 76, placeholder_arg_base::calc_identity<scalar<fp16b>, 76>()};
static inline placeholder const s_fp16b_6 = placeholder_arg_6{placeholder_value_type{scalar<fp16b>{}}, 77, placeholder_arg_base::calc_identity<scalar<fp16b>, 77>()};
static inline placeholder const s_fp16b_7 = placeholder_arg_7{placeholder_value_type{scalar<fp16b>{}}, 78, placeholder_arg_base::calc_identity<scalar<fp16b>, 78>()};
static inline placeholder const s_fp16b_8 = placeholder_arg_8{placeholder_value_type{scalar<fp16b>{}}, 79, placeholder_arg_base::calc_identity<scalar<fp16b>, 79>()};

static inline placeholder const s_fp32_1 = placeholder_arg_1{placeholder_value_type{scalar<fp32>{}}, 80, placeholder_arg_base::calc_identity<scalar<fp32>, 80>()};
static inline placeholder const s_fp32_2 = placeholder_arg_2{placeholder_value_type{scalar<fp32>{}}, 81, placeholder_arg_base::calc_identity<scalar<fp32>, 81>()};
static inline placeholder const s_fp32_3 = placeholder_arg_3{placeholder_value_type{scalar<fp32>{}}, 82, placeholder_arg_base::calc_identity<scalar<fp32>, 82>()};
static inline placeholder const s_fp32_4 = placeholder_arg_4{placeholder_value_type{scalar<fp32>{}}, 83, placeholder_arg_base::calc_identity<scalar<fp32>, 83>()};
static inline placeholder const s_fp32_5 = placeholder_arg_5{placeholder_value_type{scalar<fp32>{}}, 84, placeholder_arg_base::calc_identity<scalar<fp32>, 84>()};
static inline placeholder const s_fp32_6 = placeholder_arg_6{placeholder_value_type{scalar<fp32>{}}, 85, placeholder_arg_base::calc_identity<scalar<fp32>, 85>()};
static inline placeholder const s_fp32_7 = placeholder_arg_7{placeholder_value_type{scalar<fp32>{}}, 86, placeholder_arg_base::calc_identity<scalar<fp32>, 86>()};
static inline placeholder const s_fp32_8 = placeholder_arg_8{placeholder_value_type{scalar<fp32>{}}, 87, placeholder_arg_base::calc_identity<scalar<fp32>, 87>()};

static inline placeholder const s_fp64_1 = placeholder_arg_1{placeholder_value_type{scalar<fp64>{}}, 88, placeholder_arg_base::calc_identity<scalar<fp64>, 88>()};
static inline placeholder const s_fp64_2 = placeholder_arg_2{placeholder_value_type{scalar<fp64>{}}, 89, placeholder_arg_base::calc_identity<scalar<fp64>, 89>()};
static inline placeholder const s_fp64_3 = placeholder_arg_3{placeholder_value_type{scalar<fp64>{}}, 90, placeholder_arg_base::calc_identity<scalar<fp64>, 90>()};
static inline placeholder const s_fp64_4 = placeholder_arg_4{placeholder_value_type{scalar<fp64>{}}, 91, placeholder_arg_base::calc_identity<scalar<fp64>, 91>()};
static inline placeholder const s_fp64_5 = placeholder_arg_5{placeholder_value_type{scalar<fp64>{}}, 92, placeholder_arg_base::calc_identity<scalar<fp64>, 92>()};
static inline placeholder const s_fp64_6 = placeholder_arg_6{placeholder_value_type{scalar<fp64>{}}, 93, placeholder_arg_base::calc_identity<scalar<fp64>, 93>()};
static inline placeholder const s_fp64_7 = placeholder_arg_7{placeholder_value_type{scalar<fp64>{}}, 94, placeholder_arg_base::calc_identity<scalar<fp64>, 94>()};
static inline placeholder const s_fp64_8 = placeholder_arg_8{placeholder_value_type{scalar<fp64>{}}, 95, placeholder_arg_base::calc_identity<scalar<fp64>, 95>()};

static inline placeholder const s_bool_1 = placeholder_arg_1{placeholder_value_type{scalar<boolean>{}}, 96, placeholder_arg_base::calc_identity<scalar<boolean>, 96>()};
static inline placeholder const s_bool_2 = placeholder_arg_2{placeholder_value_type{scalar<boolean>{}}, 97, placeholder_arg_base::calc_identity<scalar<boolean>, 97>()};
static inline placeholder const s_bool_3 = placeholder_arg_3{placeholder_value_type{scalar<boolean>{}}, 98, placeholder_arg_base::calc_identity<scalar<boolean>, 98>()};
static inline placeholder const s_bool_4 = placeholder_arg_4{placeholder_value_type{scalar<boolean>{}}, 99, placeholder_arg_base::calc_identity<scalar<boolean>, 99>()};
static inline placeholder const s_bool_5 = placeholder_arg_5{placeholder_value_type{scalar<boolean>{}}, 100, placeholder_arg_base::calc_identity<scalar<boolean>, 100>()};
static inline placeholder const s_bool_6 = placeholder_arg_6{placeholder_value_type{scalar<boolean>{}}, 101, placeholder_arg_base::calc_identity<scalar<boolean>, 101>()};
static inline placeholder const s_bool_7 = placeholder_arg_7{placeholder_value_type{scalar<boolean>{}}, 102, placeholder_arg_base::calc_identity<scalar<boolean>, 102>()};
static inline placeholder const s_bool_8 = placeholder_arg_8{placeholder_value_type{scalar<boolean>{}}, 103, placeholder_arg_base::calc_identity<scalar<boolean>, 103>()};

static inline placeholder const a_i8_1 = placeholder_arg_1{placeholder_value_type{array<i8>{}}, 104, placeholder_arg_base::calc_identity<array<i8>, 104>()};
static inline placeholder const a_i8_2 = placeholder_arg_2{placeholder_value_type{array<i8>{}}, 105, placeholder_arg_base::calc_identity<array<i8>, 105>()};
static inline placeholder const a_i8_3 = placeholder_arg_3{placeholder_value_type{array<i8>{}}, 106, placeholder_arg_base::calc_identity<array<i8>, 106>()};
static inline placeholder const a_i8_4 = placeholder_arg_4{placeholder_value_type{array<i8>{}}, 107, placeholder_arg_base::calc_identity<array<i8>, 107>()};
static inline placeholder const a_i8_5 = placeholder_arg_5{placeholder_value_type{array<i8>{}}, 108, placeholder_arg_base::calc_identity<array<i8>, 108>()};
static inline placeholder const a_i8_6 = placeholder_arg_6{placeholder_value_type{array<i8>{}}, 109, placeholder_arg_base::calc_identity<array<i8>, 109>()};
static inline placeholder const a_i8_7 = placeholder_arg_7{placeholder_value_type{array<i8>{}}, 110, placeholder_arg_base::calc_identity<array<i8>, 110>()};
static inline placeholder const a_i8_8 = placeholder_arg_8{placeholder_value_type{array<i8>{}}, 111, placeholder_arg_base::calc_identity<array<i8>, 111>()};

static inline placeholder const a_i16_1 = placeholder_arg_1{placeholder_value_type{array<i16>{}}, 112, placeholder_arg_base::calc_identity<array<i16>, 112>()};
static inline placeholder const a_i16_2 = placeholder_arg_2{placeholder_value_type{array<i16>{}}, 113, placeholder_arg_base::calc_identity<array<i16>, 113>()};
static inline placeholder const a_i16_3 = placeholder_arg_3{placeholder_value_type{array<i16>{}}, 114, placeholder_arg_base::calc_identity<array<i16>, 114>()};
static inline placeholder const a_i16_4 = placeholder_arg_4{placeholder_value_type{array<i16>{}}, 115, placeholder_arg_base::calc_identity<array<i16>, 115>()};
static inline placeholder const a_i16_5 = placeholder_arg_5{placeholder_value_type{array<i16>{}}, 116, placeholder_arg_base::calc_identity<array<i16>, 116>()};
static inline placeholder const a_i16_6 = placeholder_arg_6{placeholder_value_type{array<i16>{}}, 117, placeholder_arg_base::calc_identity<array<i16>, 117>()};
static inline placeholder const a_i16_7 = placeholder_arg_7{placeholder_value_type{array<i16>{}}, 118, placeholder_arg_base::calc_identity<array<i16>, 118>()};
static inline placeholder const a_i16_8 = placeholder_arg_8{placeholder_value_type{array<i16>{}}, 119, placeholder_arg_base::calc_identity<array<i16>, 119>()};

static inline placeholder const a_i32_1 = placeholder_arg_1{placeholder_value_type{array<i32>{}}, 120, placeholder_arg_base::calc_identity<array<i32>, 120>()};
static inline placeholder const a_i32_2 = placeholder_arg_2{placeholder_value_type{array<i32>{}}, 121, placeholder_arg_base::calc_identity<array<i32>, 121>()};
static inline placeholder const a_i32_3 = placeholder_arg_3{placeholder_value_type{array<i32>{}}, 122, placeholder_arg_base::calc_identity<array<i32>, 122>()};
static inline placeholder const a_i32_4 = placeholder_arg_4{placeholder_value_type{array<i32>{}}, 123, placeholder_arg_base::calc_identity<array<i32>, 123>()};
static inline placeholder const a_i32_5 = placeholder_arg_5{placeholder_value_type{array<i32>{}}, 124, placeholder_arg_base::calc_identity<array<i32>, 124>()};
static inline placeholder const a_i32_6 = placeholder_arg_6{placeholder_value_type{array<i32>{}}, 125, placeholder_arg_base::calc_identity<array<i32>, 125>()};
static inline placeholder const a_i32_7 = placeholder_arg_7{placeholder_value_type{array<i32>{}}, 126, placeholder_arg_base::calc_identity<array<i32>, 126>()};
static inline placeholder const a_i32_8 = placeholder_arg_8{placeholder_value_type{array<i32>{}}, 127, placeholder_arg_base::calc_identity<array<i32>, 127>()};

static inline placeholder const a_i64_1 = placeholder_arg_1{placeholder_value_type{array<i64>{}}, 128, placeholder_arg_base::calc_identity<array<i64>, 128>()};
static inline placeholder const a_i64_2 = placeholder_arg_2{placeholder_value_type{array<i64>{}}, 129, placeholder_arg_base::calc_identity<array<i64>, 129>()};
static inline placeholder const a_i64_3 = placeholder_arg_3{placeholder_value_type{array<i64>{}}, 130, placeholder_arg_base::calc_identity<array<i64>, 130>()};
static inline placeholder const a_i64_4 = placeholder_arg_4{placeholder_value_type{array<i64>{}}, 131, placeholder_arg_base::calc_identity<array<i64>, 131>()};
static inline placeholder const a_i64_5 = placeholder_arg_5{placeholder_value_type{array<i64>{}}, 132, placeholder_arg_base::calc_identity<array<i64>, 132>()};
static inline placeholder const a_i64_6 = placeholder_arg_6{placeholder_value_type{array<i64>{}}, 133, placeholder_arg_base::calc_identity<array<i64>, 133>()};
static inline placeholder const a_i64_7 = placeholder_arg_7{placeholder_value_type{array<i64>{}}, 134, placeholder_arg_base::calc_identity<array<i64>, 134>()};
static inline placeholder const a_i64_8 = placeholder_arg_8{placeholder_value_type{array<i64>{}}, 135, placeholder_arg_base::calc_identity<array<i64>, 135>()};

static inline placeholder const a_u8_1 = placeholder_arg_1{placeholder_value_type{array<u8>{}}, 136, placeholder_arg_base::calc_identity<array<u8>, 136>()};
static inline placeholder const a_u8_2 = placeholder_arg_2{placeholder_value_type{array<u8>{}}, 137, placeholder_arg_base::calc_identity<array<u8>, 137>()};
static inline placeholder const a_u8_3 = placeholder_arg_3{placeholder_value_type{array<u8>{}}, 138, placeholder_arg_base::calc_identity<array<u8>, 138>()};
static inline placeholder const a_u8_4 = placeholder_arg_4{placeholder_value_type{array<u8>{}}, 139, placeholder_arg_base::calc_identity<array<u8>, 139>()};
static inline placeholder const a_u8_5 = placeholder_arg_5{placeholder_value_type{array<u8>{}}, 140, placeholder_arg_base::calc_identity<array<u8>, 140>()};
static inline placeholder const a_u8_6 = placeholder_arg_6{placeholder_value_type{array<u8>{}}, 141, placeholder_arg_base::calc_identity<array<u8>, 141>()};
static inline placeholder const a_u8_7 = placeholder_arg_7{placeholder_value_type{array<u8>{}}, 142, placeholder_arg_base::calc_identity<array<u8>, 142>()};
static inline placeholder const a_u8_8 = placeholder_arg_8{placeholder_value_type{array<u8>{}}, 143, placeholder_arg_base::calc_identity<array<u8>, 143>()};

static inline placeholder const a_u16_1 = placeholder_arg_1{placeholder_value_type{array<u16>{}}, 144, placeholder_arg_base::calc_identity<array<u16>, 144>()};
static inline placeholder const a_u16_2 = placeholder_arg_2{placeholder_value_type{array<u16>{}}, 145, placeholder_arg_base::calc_identity<array<u16>, 145>()};
static inline placeholder const a_u16_3 = placeholder_arg_3{placeholder_value_type{array<u16>{}}, 146, placeholder_arg_base::calc_identity<array<u16>, 146>()};
static inline placeholder const a_u16_4 = placeholder_arg_4{placeholder_value_type{array<u16>{}}, 147, placeholder_arg_base::calc_identity<array<u16>, 147>()};
static inline placeholder const a_u16_5 = placeholder_arg_5{placeholder_value_type{array<u16>{}}, 148, placeholder_arg_base::calc_identity<array<u16>, 148>()};
static inline placeholder const a_u16_6 = placeholder_arg_6{placeholder_value_type{array<u16>{}}, 149, placeholder_arg_base::calc_identity<array<u16>, 149>()};
static inline placeholder const a_u16_7 = placeholder_arg_7{placeholder_value_type{array<u16>{}}, 150, placeholder_arg_base::calc_identity<array<u16>, 150>()};
static inline placeholder const a_u16_8 = placeholder_arg_8{placeholder_value_type{array<u16>{}}, 151, placeholder_arg_base::calc_identity<array<u16>, 151>()};

static inline placeholder const a_u32_1 = placeholder_arg_1{placeholder_value_type{array<u32>{}}, 152, placeholder_arg_base::calc_identity<array<i32>, 152>()};
static inline placeholder const a_u32_2 = placeholder_arg_2{placeholder_value_type{array<u32>{}}, 153, placeholder_arg_base::calc_identity<array<i32>, 153>()};
static inline placeholder const a_u32_3 = placeholder_arg_3{placeholder_value_type{array<u32>{}}, 154, placeholder_arg_base::calc_identity<array<i32>, 154>()};
static inline placeholder const a_u32_4 = placeholder_arg_4{placeholder_value_type{array<u32>{}}, 155, placeholder_arg_base::calc_identity<array<i32>, 155>()};
static inline placeholder const a_u32_5 = placeholder_arg_5{placeholder_value_type{array<u32>{}}, 156, placeholder_arg_base::calc_identity<array<i32>, 156>()};
static inline placeholder const a_u32_6 = placeholder_arg_6{placeholder_value_type{array<u32>{}}, 157, placeholder_arg_base::calc_identity<array<i32>, 157>()};
static inline placeholder const a_u32_7 = placeholder_arg_7{placeholder_value_type{array<u32>{}}, 158, placeholder_arg_base::calc_identity<array<i32>, 158>()};
static inline placeholder const a_u32_8 = placeholder_arg_8{placeholder_value_type{array<u32>{}}, 159, placeholder_arg_base::calc_identity<array<i32>, 159>()};

static inline placeholder const a_u64_1 = placeholder_arg_1{placeholder_value_type{array<u64>{}}, 160, placeholder_arg_base::calc_identity<array<i64>, 160>()};
static inline placeholder const a_u64_2 = placeholder_arg_2{placeholder_value_type{array<u64>{}}, 161, placeholder_arg_base::calc_identity<array<i64>, 161>()};
static inline placeholder const a_u64_3 = placeholder_arg_3{placeholder_value_type{array<u64>{}}, 162, placeholder_arg_base::calc_identity<array<i64>, 162>()};
static inline placeholder const a_u64_4 = placeholder_arg_4{placeholder_value_type{array<u64>{}}, 163, placeholder_arg_base::calc_identity<array<i64>, 163>()};
static inline placeholder const a_u64_5 = placeholder_arg_5{placeholder_value_type{array<u64>{}}, 164, placeholder_arg_base::calc_identity<array<i64>, 164>()};
static inline placeholder const a_u64_6 = placeholder_arg_6{placeholder_value_type{array<u64>{}}, 165, placeholder_arg_base::calc_identity<array<i64>, 165>()};
static inline placeholder const a_u64_7 = placeholder_arg_7{placeholder_value_type{array<u64>{}}, 166, placeholder_arg_base::calc_identity<array<i64>, 166>()};
static inline placeholder const a_u64_8 = placeholder_arg_8{placeholder_value_type{array<u64>{}}, 167, placeholder_arg_base::calc_identity<array<i64>, 167>()};

static inline placeholder const a_fp16a_1 = placeholder_arg_1{placeholder_value_type{array<fp16a>{}}, 168, placeholder_arg_base::calc_identity<array<fp16a>, 168>()};
static inline placeholder const a_fp16a_2 = placeholder_arg_2{placeholder_value_type{array<fp16a>{}}, 169, placeholder_arg_base::calc_identity<array<fp16a>, 169>()};
static inline placeholder const a_fp16a_3 = placeholder_arg_3{placeholder_value_type{array<fp16a>{}}, 170, placeholder_arg_base::calc_identity<array<fp16a>, 170>()};
static inline placeholder const a_fp16a_4 = placeholder_arg_4{placeholder_value_type{array<fp16a>{}}, 171, placeholder_arg_base::calc_identity<array<fp16a>, 171>()};
static inline placeholder const a_fp16a_5 = placeholder_arg_5{placeholder_value_type{array<fp16a>{}}, 172, placeholder_arg_base::calc_identity<array<fp16a>, 172>()};
static inline placeholder const a_fp16a_6 = placeholder_arg_6{placeholder_value_type{array<fp16a>{}}, 173, placeholder_arg_base::calc_identity<array<fp16a>, 173>()};
static inline placeholder const a_fp16a_7 = placeholder_arg_7{placeholder_value_type{array<fp16a>{}}, 174, placeholder_arg_base::calc_identity<array<fp16a>, 174>()};
static inline placeholder const a_fp16a_8 = placeholder_arg_8{placeholder_value_type{array<fp16a>{}}, 175, placeholder_arg_base::calc_identity<array<fp16a>, 175>()};

static inline placeholder const a_fp16b_1 = placeholder_arg_1{placeholder_value_type{array<fp16b>{}}, 176, placeholder_arg_base::calc_identity<array<fp16b>, 176>()};
static inline placeholder const a_fp16b_2 = placeholder_arg_2{placeholder_value_type{array<fp16b>{}}, 177, placeholder_arg_base::calc_identity<array<fp16b>, 177>()};
static inline placeholder const a_fp16b_3 = placeholder_arg_3{placeholder_value_type{array<fp16b>{}}, 178, placeholder_arg_base::calc_identity<array<fp16b>, 178>()};
static inline placeholder const a_fp16b_4 = placeholder_arg_4{placeholder_value_type{array<fp16b>{}}, 179, placeholder_arg_base::calc_identity<array<fp16b>, 179>()};
static inline placeholder const a_fp16b_5 = placeholder_arg_5{placeholder_value_type{array<fp16b>{}}, 180, placeholder_arg_base::calc_identity<array<fp16b>, 180>()};
static inline placeholder const a_fp16b_6 = placeholder_arg_6{placeholder_value_type{array<fp16b>{}}, 181, placeholder_arg_base::calc_identity<array<fp16b>, 181>()};
static inline placeholder const a_fp16b_7 = placeholder_arg_7{placeholder_value_type{array<fp16b>{}}, 182, placeholder_arg_base::calc_identity<array<fp16b>, 182>()};
static inline placeholder const a_fp16b_8 = placeholder_arg_8{placeholder_value_type{array<fp16b>{}}, 183, placeholder_arg_base::calc_identity<array<fp16b>, 183>()};

static inline placeholder const a_fp32_1 = placeholder_arg_1{placeholder_value_type{array<fp32>{}}, 184, placeholder_arg_base::calc_identity<array<fp32>, 184>()};
static inline placeholder const a_fp32_2 = placeholder_arg_2{placeholder_value_type{array<fp32>{}}, 185, placeholder_arg_base::calc_identity<array<fp32>, 185>()};
static inline placeholder const a_fp32_3 = placeholder_arg_3{placeholder_value_type{array<fp32>{}}, 186, placeholder_arg_base::calc_identity<array<fp32>, 186>()};
static inline placeholder const a_fp32_4 = placeholder_arg_4{placeholder_value_type{array<fp32>{}}, 187, placeholder_arg_base::calc_identity<array<fp32>, 187>()};
static inline placeholder const a_fp32_5 = placeholder_arg_5{placeholder_value_type{array<fp32>{}}, 188, placeholder_arg_base::calc_identity<array<fp32>, 188>()};
static inline placeholder const a_fp32_6 = placeholder_arg_6{placeholder_value_type{array<fp32>{}}, 189, placeholder_arg_base::calc_identity<array<fp32>, 189>()};
static inline placeholder const a_fp32_7 = placeholder_arg_7{placeholder_value_type{array<fp32>{}}, 190, placeholder_arg_base::calc_identity<array<fp32>, 190>()};
static inline placeholder const a_fp32_8 = placeholder_arg_8{placeholder_value_type{array<fp32>{}}, 191, placeholder_arg_base::calc_identity<array<fp32>, 191>()};

static inline placeholder const a_fp64_1 = placeholder_arg_1{placeholder_value_type{array<fp64>{}}, 192, placeholder_arg_base::calc_identity<array<fp64>, 192>()};
static inline placeholder const a_fp64_2 = placeholder_arg_2{placeholder_value_type{array<fp64>{}}, 193, placeholder_arg_base::calc_identity<array<fp64>, 193>()};
static inline placeholder const a_fp64_3 = placeholder_arg_3{placeholder_value_type{array<fp64>{}}, 194, placeholder_arg_base::calc_identity<array<fp64>, 194>()};
static inline placeholder const a_fp64_4 = placeholder_arg_4{placeholder_value_type{array<fp64>{}}, 195, placeholder_arg_base::calc_identity<array<fp64>, 195>()};
static inline placeholder const a_fp64_5 = placeholder_arg_5{placeholder_value_type{array<fp64>{}}, 196, placeholder_arg_base::calc_identity<array<fp64>, 196>()};
static inline placeholder const a_fp64_6 = placeholder_arg_6{placeholder_value_type{array<fp64>{}}, 197, placeholder_arg_base::calc_identity<array<fp64>, 197>()};
static inline placeholder const a_fp64_7 = placeholder_arg_7{placeholder_value_type{array<fp64>{}}, 198, placeholder_arg_base::calc_identity<array<fp64>, 198>()};
static inline placeholder const a_fp64_8 = placeholder_arg_8{placeholder_value_type{array<fp64>{}}, 199, placeholder_arg_base::calc_identity<array<fp64>, 199>()};

static inline placeholder const a_bool_1 = placeholder_arg_1{placeholder_value_type{array<boolean>{}}, 200, placeholder_arg_base::calc_identity<array<boolean>, 200>()};
static inline placeholder const a_bool_2 = placeholder_arg_2{placeholder_value_type{array<boolean>{}}, 201, placeholder_arg_base::calc_identity<array<boolean>, 201>()};
static inline placeholder const a_bool_3 = placeholder_arg_3{placeholder_value_type{array<boolean>{}}, 202, placeholder_arg_base::calc_identity<array<boolean>, 202>()};
static inline placeholder const a_bool_4 = placeholder_arg_4{placeholder_value_type{array<boolean>{}}, 203, placeholder_arg_base::calc_identity<array<boolean>, 203>()};
static inline placeholder const a_bool_5 = placeholder_arg_5{placeholder_value_type{array<boolean>{}}, 204, placeholder_arg_base::calc_identity<array<boolean>, 204>()};
static inline placeholder const a_bool_6 = placeholder_arg_6{placeholder_value_type{array<boolean>{}}, 205, placeholder_arg_base::calc_identity<array<boolean>, 205>()};
static inline placeholder const a_bool_7 = placeholder_arg_7{placeholder_value_type{array<boolean>{}}, 206, placeholder_arg_base::calc_identity<array<boolean>, 206>()};
static inline placeholder const a_bool_8 = placeholder_arg_8{placeholder_value_type{array<boolean>{}}, 207, placeholder_arg_base::calc_identity<array<boolean>, 207>()};

static inline placeholder const m_i8_1 = placeholder_arg_1{placeholder_value_type{matrix<i8>{}}, 208, placeholder_arg_base::calc_identity<matrix<i8>, 208>()};
static inline placeholder const m_i8_2 = placeholder_arg_2{placeholder_value_type{matrix<i8>{}}, 209, placeholder_arg_base::calc_identity<matrix<i8>, 209>()};
static inline placeholder const m_i8_3 = placeholder_arg_3{placeholder_value_type{matrix<i8>{}}, 210, placeholder_arg_base::calc_identity<matrix<i8>, 210>()};
static inline placeholder const m_i8_4 = placeholder_arg_4{placeholder_value_type{matrix<i8>{}}, 211, placeholder_arg_base::calc_identity<matrix<i8>, 211>()};
static inline placeholder const m_i8_5 = placeholder_arg_5{placeholder_value_type{matrix<i8>{}}, 212, placeholder_arg_base::calc_identity<matrix<i8>, 212>()};
static inline placeholder const m_i8_6 = placeholder_arg_6{placeholder_value_type{matrix<i8>{}}, 213, placeholder_arg_base::calc_identity<matrix<i8>, 213>()};
static inline placeholder const m_i8_7 = placeholder_arg_7{placeholder_value_type{matrix<i8>{}}, 214, placeholder_arg_base::calc_identity<matrix<i8>, 214>()};
static inline placeholder const m_i8_8 = placeholder_arg_8{placeholder_value_type{matrix<i8>{}}, 215, placeholder_arg_base::calc_identity<matrix<i8>, 215>()};

static inline placeholder const m_i16_1 = placeholder_arg_1{placeholder_value_type{matrix<i16>{}}, 216, placeholder_arg_base::calc_identity<matrix<i16>, 216>()};
static inline placeholder const m_i16_2 = placeholder_arg_2{placeholder_value_type{matrix<i16>{}}, 217, placeholder_arg_base::calc_identity<matrix<i16>, 217>()};
static inline placeholder const m_i16_3 = placeholder_arg_3{placeholder_value_type{matrix<i16>{}}, 218, placeholder_arg_base::calc_identity<matrix<i16>, 218>()};
static inline placeholder const m_i16_4 = placeholder_arg_4{placeholder_value_type{matrix<i16>{}}, 219, placeholder_arg_base::calc_identity<matrix<i16>, 219>()};
static inline placeholder const m_i16_5 = placeholder_arg_5{placeholder_value_type{matrix<i16>{}}, 220, placeholder_arg_base::calc_identity<matrix<i16>, 220>()};
static inline placeholder const m_i16_6 = placeholder_arg_6{placeholder_value_type{matrix<i16>{}}, 221, placeholder_arg_base::calc_identity<matrix<i16>, 221>()};
static inline placeholder const m_i16_7 = placeholder_arg_7{placeholder_value_type{matrix<i16>{}}, 222, placeholder_arg_base::calc_identity<matrix<i16>, 222>()};
static inline placeholder const m_i16_8 = placeholder_arg_8{placeholder_value_type{matrix<i16>{}}, 223, placeholder_arg_base::calc_identity<matrix<i16>, 223>()};

static inline placeholder const m_i32_1 = placeholder_arg_1{placeholder_value_type{matrix<i32>{}}, 224, placeholder_arg_base::calc_identity<matrix<i32>, 224>()};
static inline placeholder const m_i32_2 = placeholder_arg_2{placeholder_value_type{matrix<i32>{}}, 225, placeholder_arg_base::calc_identity<matrix<i32>, 225>()};
static inline placeholder const m_i32_3 = placeholder_arg_3{placeholder_value_type{matrix<i32>{}}, 226, placeholder_arg_base::calc_identity<matrix<i32>, 226>()};
static inline placeholder const m_i32_4 = placeholder_arg_4{placeholder_value_type{matrix<i32>{}}, 227, placeholder_arg_base::calc_identity<matrix<i32>, 227>()};
static inline placeholder const m_i32_5 = placeholder_arg_5{placeholder_value_type{matrix<i32>{}}, 228, placeholder_arg_base::calc_identity<matrix<i32>, 228>()};
static inline placeholder const m_i32_6 = placeholder_arg_6{placeholder_value_type{matrix<i32>{}}, 229, placeholder_arg_base::calc_identity<matrix<i32>, 229>()};
static inline placeholder const m_i32_7 = placeholder_arg_7{placeholder_value_type{matrix<i32>{}}, 230, placeholder_arg_base::calc_identity<matrix<i32>, 230>()};
static inline placeholder const m_i32_8 = placeholder_arg_8{placeholder_value_type{matrix<i32>{}}, 231, placeholder_arg_base::calc_identity<matrix<i32>, 231>()};

static inline placeholder const m_i64_1 = placeholder_arg_1{placeholder_value_type{matrix<i64>{}}, 232, placeholder_arg_base::calc_identity<matrix<i64>, 232>()};
static inline placeholder const m_i64_2 = placeholder_arg_2{placeholder_value_type{matrix<i64>{}}, 233, placeholder_arg_base::calc_identity<matrix<i64>, 233>()};
static inline placeholder const m_i64_3 = placeholder_arg_3{placeholder_value_type{matrix<i64>{}}, 234, placeholder_arg_base::calc_identity<matrix<i64>, 234>()};
static inline placeholder const m_i64_4 = placeholder_arg_4{placeholder_value_type{matrix<i64>{}}, 235, placeholder_arg_base::calc_identity<matrix<i64>, 235>()};
static inline placeholder const m_i64_5 = placeholder_arg_5{placeholder_value_type{matrix<i64>{}}, 236, placeholder_arg_base::calc_identity<matrix<i64>, 236>()};
static inline placeholder const m_i64_6 = placeholder_arg_6{placeholder_value_type{matrix<i64>{}}, 237, placeholder_arg_base::calc_identity<matrix<i64>, 237>()};
static inline placeholder const m_i64_7 = placeholder_arg_7{placeholder_value_type{matrix<i64>{}}, 238, placeholder_arg_base::calc_identity<matrix<i64>, 238>()};
static inline placeholder const m_i64_8 = placeholder_arg_8{placeholder_value_type{matrix<i64>{}}, 239, placeholder_arg_base::calc_identity<matrix<i64>, 239>()};

static inline placeholder const m_u8_1 = placeholder_arg_1{placeholder_value_type{matrix<u8>{}}, 240, placeholder_arg_base::calc_identity<matrix<u8>, 240>()};
static inline placeholder const m_u8_2 = placeholder_arg_2{placeholder_value_type{matrix<u8>{}}, 241, placeholder_arg_base::calc_identity<matrix<u8>, 241>()};
static inline placeholder const m_u8_3 = placeholder_arg_3{placeholder_value_type{matrix<u8>{}}, 242, placeholder_arg_base::calc_identity<matrix<u8>, 242>()};
static inline placeholder const m_u8_4 = placeholder_arg_4{placeholder_value_type{matrix<u8>{}}, 243, placeholder_arg_base::calc_identity<matrix<u8>, 243>()};
static inline placeholder const m_u8_5 = placeholder_arg_5{placeholder_value_type{matrix<u8>{}}, 244, placeholder_arg_base::calc_identity<matrix<u8>, 244>()};
static inline placeholder const m_u8_6 = placeholder_arg_6{placeholder_value_type{matrix<u8>{}}, 245, placeholder_arg_base::calc_identity<matrix<u8>, 245>()};
static inline placeholder const m_u8_7 = placeholder_arg_7{placeholder_value_type{matrix<u8>{}}, 246, placeholder_arg_base::calc_identity<matrix<u8>, 246>()};
static inline placeholder const m_u8_8 = placeholder_arg_8{placeholder_value_type{matrix<u8>{}}, 247, placeholder_arg_base::calc_identity<matrix<u8>, 247>()};

static inline placeholder const m_u16_1 = placeholder_arg_1{placeholder_value_type{matrix<u16>{}}, 248, placeholder_arg_base::calc_identity<matrix<u16>, 248>()};
static inline placeholder const m_u16_2 = placeholder_arg_2{placeholder_value_type{matrix<u16>{}}, 249, placeholder_arg_base::calc_identity<matrix<u16>, 249>()};
static inline placeholder const m_u16_3 = placeholder_arg_3{placeholder_value_type{matrix<u16>{}}, 250, placeholder_arg_base::calc_identity<matrix<u16>, 250>()};
static inline placeholder const m_u16_4 = placeholder_arg_4{placeholder_value_type{matrix<u16>{}}, 251, placeholder_arg_base::calc_identity<matrix<u16>, 251>()};
static inline placeholder const m_u16_5 = placeholder_arg_5{placeholder_value_type{matrix<u16>{}}, 252, placeholder_arg_base::calc_identity<matrix<u16>, 252>()};
static inline placeholder const m_u16_6 = placeholder_arg_6{placeholder_value_type{matrix<u16>{}}, 253, placeholder_arg_base::calc_identity<matrix<u16>, 253>()};
static inline placeholder const m_u16_7 = placeholder_arg_7{placeholder_value_type{matrix<u16>{}}, 254, placeholder_arg_base::calc_identity<matrix<u16>, 254>()};
static inline placeholder const m_u16_8 = placeholder_arg_8{placeholder_value_type{matrix<u16>{}}, 255, placeholder_arg_base::calc_identity<matrix<u16>, 255>()};

static inline placeholder const m_u32_1 = placeholder_arg_1{placeholder_value_type{matrix<u32>{}}, 256, placeholder_arg_base::calc_identity<matrix<u32>, 256>()};
static inline placeholder const m_u32_2 = placeholder_arg_2{placeholder_value_type{matrix<u32>{}}, 257, placeholder_arg_base::calc_identity<matrix<u32>, 257>()};
static inline placeholder const m_u32_3 = placeholder_arg_3{placeholder_value_type{matrix<u32>{}}, 258, placeholder_arg_base::calc_identity<matrix<u32>, 258>()};
static inline placeholder const m_u32_4 = placeholder_arg_4{placeholder_value_type{matrix<u32>{}}, 259, placeholder_arg_base::calc_identity<matrix<u32>, 259>()};
static inline placeholder const m_u32_5 = placeholder_arg_5{placeholder_value_type{matrix<u32>{}}, 260, placeholder_arg_base::calc_identity<matrix<u32>, 260>()};
static inline placeholder const m_u32_6 = placeholder_arg_6{placeholder_value_type{matrix<u32>{}}, 261, placeholder_arg_base::calc_identity<matrix<u32>, 261>()};
static inline placeholder const m_u32_7 = placeholder_arg_7{placeholder_value_type{matrix<u32>{}}, 262, placeholder_arg_base::calc_identity<matrix<u32>, 262>()};
static inline placeholder const m_u32_8 = placeholder_arg_8{placeholder_value_type{matrix<u32>{}}, 263, placeholder_arg_base::calc_identity<matrix<u32>, 263>()};

static inline placeholder const m_u64_1 = placeholder_arg_1{placeholder_value_type{matrix<u64>{}}, 264, placeholder_arg_base::calc_identity<matrix<u64>, 264>()};
static inline placeholder const m_u64_2 = placeholder_arg_2{placeholder_value_type{matrix<u64>{}}, 265, placeholder_arg_base::calc_identity<matrix<u64>, 265>()};
static inline placeholder const m_u64_3 = placeholder_arg_3{placeholder_value_type{matrix<u64>{}}, 266, placeholder_arg_base::calc_identity<matrix<u64>, 266>()};
static inline placeholder const m_u64_4 = placeholder_arg_4{placeholder_value_type{matrix<u64>{}}, 267, placeholder_arg_base::calc_identity<matrix<u64>, 267>()};
static inline placeholder const m_u64_5 = placeholder_arg_5{placeholder_value_type{matrix<u64>{}}, 268, placeholder_arg_base::calc_identity<matrix<u64>, 268>()};
static inline placeholder const m_u64_6 = placeholder_arg_6{placeholder_value_type{matrix<u64>{}}, 269, placeholder_arg_base::calc_identity<matrix<u64>, 269>()};
static inline placeholder const m_u64_7 = placeholder_arg_7{placeholder_value_type{matrix<u64>{}}, 270, placeholder_arg_base::calc_identity<matrix<u64>, 270>()};
static inline placeholder const m_u64_8 = placeholder_arg_8{placeholder_value_type{matrix<u64>{}}, 271, placeholder_arg_base::calc_identity<matrix<u64>, 271>()};

static inline placeholder const m_fp16a_1 = placeholder_arg_1{placeholder_value_type{matrix<fp16a>{}}, 272, placeholder_arg_base::calc_identity<matrix<fp16a>, 272>()};
static inline placeholder const m_fp16a_2 = placeholder_arg_2{placeholder_value_type{matrix<fp16a>{}}, 273, placeholder_arg_base::calc_identity<matrix<fp16a>, 273>()};
static inline placeholder const m_fp16a_3 = placeholder_arg_3{placeholder_value_type{matrix<fp16a>{}}, 274, placeholder_arg_base::calc_identity<matrix<fp16a>, 274>()};
static inline placeholder const m_fp16a_4 = placeholder_arg_4{placeholder_value_type{matrix<fp16a>{}}, 275, placeholder_arg_base::calc_identity<matrix<fp16a>, 275>()};
static inline placeholder const m_fp16a_5 = placeholder_arg_5{placeholder_value_type{matrix<fp16a>{}}, 276, placeholder_arg_base::calc_identity<matrix<fp16a>, 276>()};
static inline placeholder const m_fp16a_6 = placeholder_arg_6{placeholder_value_type{matrix<fp16a>{}}, 277, placeholder_arg_base::calc_identity<matrix<fp16a>, 277>()};
static inline placeholder const m_fp16a_7 = placeholder_arg_7{placeholder_value_type{matrix<fp16a>{}}, 278, placeholder_arg_base::calc_identity<matrix<fp16a>, 278>()};
static inline placeholder const m_fp16a_8 = placeholder_arg_8{placeholder_value_type{matrix<fp16a>{}}, 279, placeholder_arg_base::calc_identity<matrix<fp16a>, 279>()};

static inline placeholder const m_fp16b_1 = placeholder_arg_1{placeholder_value_type{matrix<fp16b>{}}, 280, placeholder_arg_base::calc_identity<matrix<fp16b>, 280>()};
static inline placeholder const m_fp16b_2 = placeholder_arg_2{placeholder_value_type{matrix<fp16b>{}}, 281, placeholder_arg_base::calc_identity<matrix<fp16b>, 281>()};
static inline placeholder const m_fp16b_3 = placeholder_arg_3{placeholder_value_type{matrix<fp16b>{}}, 282, placeholder_arg_base::calc_identity<matrix<fp16b>, 282>()};
static inline placeholder const m_fp16b_4 = placeholder_arg_4{placeholder_value_type{matrix<fp16b>{}}, 283, placeholder_arg_base::calc_identity<matrix<fp16b>, 283>()};
static inline placeholder const m_fp16b_5 = placeholder_arg_5{placeholder_value_type{matrix<fp16b>{}}, 284, placeholder_arg_base::calc_identity<matrix<fp16b>, 284>()};
static inline placeholder const m_fp16b_6 = placeholder_arg_6{placeholder_value_type{matrix<fp16b>{}}, 285, placeholder_arg_base::calc_identity<matrix<fp16b>, 285>()};
static inline placeholder const m_fp16b_7 = placeholder_arg_7{placeholder_value_type{matrix<fp16b>{}}, 286, placeholder_arg_base::calc_identity<matrix<fp16b>, 286>()};
static inline placeholder const m_fp16b_8 = placeholder_arg_8{placeholder_value_type{matrix<fp16b>{}}, 287, placeholder_arg_base::calc_identity<matrix<fp16b>, 287>()};

static inline placeholder const m_fp32_1 = placeholder_arg_1{placeholder_value_type{matrix<fp32>{}}, 288, placeholder_arg_base::calc_identity<matrix<fp32>, 288>()};
static inline placeholder const m_fp32_2 = placeholder_arg_2{placeholder_value_type{matrix<fp32>{}}, 289, placeholder_arg_base::calc_identity<matrix<fp32>, 289>()};
static inline placeholder const m_fp32_3 = placeholder_arg_3{placeholder_value_type{matrix<fp32>{}}, 290, placeholder_arg_base::calc_identity<matrix<fp32>, 290>()};
static inline placeholder const m_fp32_4 = placeholder_arg_4{placeholder_value_type{matrix<fp32>{}}, 291, placeholder_arg_base::calc_identity<matrix<fp32>, 291>()};
static inline placeholder const m_fp32_5 = placeholder_arg_5{placeholder_value_type{matrix<fp32>{}}, 292, placeholder_arg_base::calc_identity<matrix<fp32>, 292>()};
static inline placeholder const m_fp32_6 = placeholder_arg_6{placeholder_value_type{matrix<fp32>{}}, 293, placeholder_arg_base::calc_identity<matrix<fp32>, 293>()};
static inline placeholder const m_fp32_7 = placeholder_arg_7{placeholder_value_type{matrix<fp32>{}}, 294, placeholder_arg_base::calc_identity<matrix<fp32>, 294>()};
static inline placeholder const m_fp32_8 = placeholder_arg_8{placeholder_value_type{matrix<fp32>{}}, 295, placeholder_arg_base::calc_identity<matrix<fp32>, 295>()};

static inline placeholder const m_fp64_1 = placeholder_arg_1{placeholder_value_type{matrix<fp64>{}}, 296, placeholder_arg_base::calc_identity<matrix<fp64>, 296>()};
static inline placeholder const m_fp64_2 = placeholder_arg_2{placeholder_value_type{matrix<fp64>{}}, 297, placeholder_arg_base::calc_identity<matrix<fp64>, 297>()};
static inline placeholder const m_fp64_3 = placeholder_arg_3{placeholder_value_type{matrix<fp64>{}}, 298, placeholder_arg_base::calc_identity<matrix<fp64>, 298>()};
static inline placeholder const m_fp64_4 = placeholder_arg_4{placeholder_value_type{matrix<fp64>{}}, 299, placeholder_arg_base::calc_identity<matrix<fp64>, 299>()};
static inline placeholder const m_fp64_5 = placeholder_arg_5{placeholder_value_type{matrix<fp64>{}}, 300, placeholder_arg_base::calc_identity<matrix<fp64>, 300>()};
static inline placeholder const m_fp64_6 = placeholder_arg_6{placeholder_value_type{matrix<fp64>{}}, 301, placeholder_arg_base::calc_identity<matrix<fp64>, 301>()};
static inline placeholder const m_fp64_7 = placeholder_arg_7{placeholder_value_type{matrix<fp64>{}}, 302, placeholder_arg_base::calc_identity<matrix<fp64>, 302>()};
static inline placeholder const m_fp64_8 = placeholder_arg_8{placeholder_value_type{matrix<fp64>{}}, 303, placeholder_arg_base::calc_identity<matrix<fp64>, 303>()};

static inline placeholder const m_bool_1 = placeholder_arg_1{placeholder_value_type{matrix<boolean>{}}, 304, placeholder_arg_base::calc_identity<matrix<boolean>, 304>()};
static inline placeholder const m_bool_2 = placeholder_arg_2{placeholder_value_type{matrix<boolean>{}}, 305, placeholder_arg_base::calc_identity<matrix<boolean>, 305>()};
static inline placeholder const m_bool_3 = placeholder_arg_3{placeholder_value_type{matrix<boolean>{}}, 306, placeholder_arg_base::calc_identity<matrix<boolean>, 306>()};
static inline placeholder const m_bool_4 = placeholder_arg_4{placeholder_value_type{matrix<boolean>{}}, 307, placeholder_arg_base::calc_identity<matrix<boolean>, 307>()};
static inline placeholder const m_bool_5 = placeholder_arg_5{placeholder_value_type{matrix<boolean>{}}, 308, placeholder_arg_base::calc_identity<matrix<boolean>, 308>()};
static inline placeholder const m_bool_6 = placeholder_arg_6{placeholder_value_type{matrix<boolean>{}}, 309, placeholder_arg_base::calc_identity<matrix<boolean>, 309>()};
static inline placeholder const m_bool_7 = placeholder_arg_7{placeholder_value_type{matrix<boolean>{}}, 310, placeholder_arg_base::calc_identity<matrix<boolean>, 310>()};
static inline placeholder const m_bool_8 = placeholder_arg_8{placeholder_value_type{matrix<boolean>{}}, 311, placeholder_arg_base::calc_identity<matrix<boolean>, 311>()};

template<typename T>
using is_placeholder_type = std::conditional<
   std::is_same< placeholder, T>::value,
   std::true_type,
   std::false_type
>;

struct PlaceholderVisitor {

   std::string & buf;

   PlaceholderVisitor(std::string & b) : buf(b) {}

   template<typename T>
   void operator()(T const& t) {
   }

   template<>
   void operator()(placeholder_arg_1 const& t) {
      t.decl(buf);
   }
   template<>
   void operator()(placeholder_arg_2 const& t) {
      t.decl(buf);
   }
   template<>
   void operator()(placeholder_arg_3 const& t) {
      t.decl(buf);
   }
   template<>
   void operator()(placeholder_arg_4 const& t) {
      t.decl(buf);
   }
   template<>
   void operator()(placeholder_arg_5 const& t) {
      t.decl(buf);
   }
   template<>
   void operator()(placeholder_arg_6 const& t) {
      t.decl(buf);
   }
   template<>
   void operator()(placeholder_arg_7 const& t) {
      t.decl(buf);
   }
   template<>
   void operator()(placeholder_arg_8 const& t) {
      t.decl(buf);
   }
};

using variable_type = variant<
   monostate,
   none,
   scalar<i8>,
   scalar<i16>,
   scalar<i32>,
   scalar<i64>,
   scalar<u8>,
   scalar<u16>,
   scalar<u32>,
   scalar<u64>,
   scalar<fp16a>,
   scalar<fp16b>,
   scalar<fp32>,
   scalar<fp64>,
   scalar<boolean>,
   literal<i8>,
   literal<i16>,
   literal<i32>,
   literal<i64>,
   literal<u8>,
   literal<u16>,
   literal<u32>,
   literal<u64>,
   literal<fp16a>,
   literal<fp16b>,
   literal<fp32>,
   literal<fp64>,
   literal<boolean>,
   array<i8>,
   array<i16>,
   array<i32>,
   array<i64>,
   array<u8>,
   array<u16>,
   array<u32>,
   array<u64>,
   array<fp16a>,
   array<fp16b>,
   array<fp32>,
   array<fp64>,
   array<boolean>,
   matrix<i8>,
   matrix<i16>,
   matrix<i32>,
   matrix<i64>,
   matrix<u8>,
   matrix<u16>,
   matrix<u32>,
   matrix<u64>,
   matrix<fp16a>,
   matrix<fp16b>,
   matrix<fp32>,
   matrix<fp64>,
   matrix<boolean>,
   pointer<scalar<i8>>,
   pointer<scalar<i16>>,
   pointer<scalar<i32>>,
   pointer<scalar<i64>>,
   pointer<scalar<u8>>,
   pointer<scalar<u16>>,
   pointer<scalar<u32>>,
   pointer<scalar<u64>>,
   pointer<scalar<fp16a>>,
   pointer<scalar<fp16b>>,
   pointer<scalar<fp32>>,
   pointer<scalar<fp64>>,
   pointer<scalar<boolean>>,
   pointer<array<i8>>,
   pointer<array<i16>>,
   pointer<array<i32>>,
   pointer<array<i64>>,
   pointer<array<u8>>,
   pointer<array<u16>>,
   pointer<array<u32>>,
   pointer<array<u64>>,
   pointer<array<fp16a>>,
   pointer<array<fp16b>>,
   pointer<array<fp32>>,
   pointer<array<fp64>>,
   pointer<array<boolean>>,
   pointer<matrix<i8>>,
   pointer<matrix<i16>>,
   pointer<matrix<i32>>,
   pointer<matrix<i64>>,
   pointer<matrix<u8>>,
   pointer<matrix<u16>>,
   pointer<matrix<u32>>,
   pointer<matrix<u64>>,
   pointer<matrix<fp16a>>,
   pointer<matrix<fp16b>>,
   pointer<matrix<fp32>>,
   pointer<matrix<fp64>>,
   pointer<matrix<boolean>>,
   reference<scalar<i8>>,
   reference<scalar<i16>>,
   reference<scalar<i32>>,
   reference<scalar<i64>>,
   reference<scalar<u8>>,
   reference<scalar<u16>>,
   reference<scalar<u32>>,
   reference<scalar<u64>>,
   reference<scalar<fp16a>>,
   reference<scalar<fp16b>>,
   reference<scalar<fp32>>,
   reference<scalar<fp64>>,
   reference<scalar<boolean>>,
   reference<array<i8>>,
   reference<array<i16>>,
   reference<array<i32>>,
   reference<array<i64>>,
   reference<array<u8>>,
   reference<array<u16>>,
   reference<array<u32>>,
   reference<array<u64>>,
   reference<array<fp16a>>,
   reference<array<fp16b>>,
   reference<array<fp32>>,
   reference<array<fp64>>,
   reference<array<boolean>>,
   reference<matrix<i8>>,
   reference<matrix<i16>>,
   reference<matrix<i32>>,
   reference<matrix<i64>>,
   reference<matrix<u8>>,
   reference<matrix<u16>>,
   reference<matrix<u32>>,
   reference<matrix<u64>>,
   reference<matrix<fp16a>>,
   reference<matrix<fp16b>>,
   reference<matrix<fp32>>,
   reference<matrix<fp64>>,
   reference<matrix<boolean>>,
   placeholder
>;

template<typename T>
using is_variable_type = std::conditional<
   is_scalar_type<T>::type::value ||
   is_literal_type<T>::type::value ||
   is_array_type<T>::type::value ||
   is_matrix_type<T>::type::value ||
   is_pointer_type<T>::type::value ||
   is_reference_type<T>::type::value ||
   is_placeholder_type<T>::type::value,
   std::true_type,
   std::false_type
>;

struct expression_data;

struct unary_op {
   recursive_wrapper<expression_data> node;
};

struct neg_op : public unary_op {};
struct not_op : public unary_op {};
struct paren_op : public unary_op {};

using unary_op_type = variant<
   monostate,
   neg_op,
   not_op,
   paren_op 
>;

template<typename T>
using is_unary_op_type = std::conditional<
      std::is_same<T, neg_op>::value ||
      std::is_same<T, not_op>::value ||
      std::is_same<T, paren_op>::value,
      std::true_type,
      std::false_type
>;

struct binary_op {
   std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>> args;
};

struct assign_op : public binary_op {};
struct index_op : public binary_op {};

struct add_op : public binary_op {};
struct sub_op : public binary_op {};
struct mul_op : public binary_op {};
struct div_op : public binary_op {};
struct mod_op : public binary_op {};

struct pow_op : public binary_op {};
struct log_op : public binary_op {};
struct exp_op : public binary_op {};
struct sin_op : public binary_op {};
struct cos_op : public binary_op {};
struct tan_op : public binary_op {};

struct lt_op : public binary_op {};
struct lte_op : public binary_op {};
struct gt_op : public binary_op {};
struct gte_op : public binary_op {};
struct eq_op : public binary_op {};
struct neq_op : public binary_op {};
struct logical_and_op : public binary_op {};
struct logical_or_op : public binary_op {};

struct bitwise_and_op : public binary_op {};
struct bitwise_or_op : public binary_op {};
struct xor_op : public binary_op {};

using binary_op_type = variant<
   monostate,
   assign_op,
   index_op,
   add_op,
   sub_op,
   mul_op,
   div_op,
   mod_op,
   pow_op,
   log_op,
   exp_op,
   sin_op,
   cos_op,
   tan_op,
   lt_op,
   lte_op,
   gt_op,
   gte_op,
   eq_op,
   neq_op,
   logical_and_op,   
   logical_or_op,   
   bitwise_and_op,   
   bitwise_or_op,
   xor_op
>;

template<typename T>
using is_binary_op_type = std::conditional<
      std::is_same<T, assign_op>::value ||
      std::is_same<T, index_op>::value ||
      std::is_same<T, add_op>::value ||
      std::is_same<T, sub_op>::value ||
      std::is_same<T, mul_op>::value ||
      std::is_same<T, div_op>::value ||
      std::is_same<T, mod_op>::value ||
      std::is_same<T, pow_op>::value ||
      std::is_same<T, log_op>::value ||
      std::is_same<T, exp_op>::value ||
      std::is_same<T, sin_op>::value ||
      std::is_same<T, cos_op>::value ||
      std::is_same<T, tan_op>::value ||
      std::is_same<T, lt_op>::value ||
      std::is_same<T, lte_op>::value ||
      std::is_same<T, gt_op>::value ||
      std::is_same<T, gte_op>::value ||
      std::is_same<T, eq_op>::value ||
      std::is_same<T, neq_op>::value ||
      std::is_same<T, logical_and_op>::value ||
      std::is_same<T, logical_or_op>::value ||
      std::is_same<T, bitwise_and_op>::value ||
      std::is_same<T, bitwise_or_op>::value ||
      std::is_same<T, xor_op>::value,
      std::true_type,
      std::false_type
>;

using logical_op_type = variant<
   logical_and_op,
   logical_or_op,
   not_op
>;

template<typename T>
using is_logical_op_type = std::conditional<
      std::is_same<T, logical_and_op>::value ||
      std::is_same<T, logical_or_op>::value ||
      std::is_same<T, not_op>::value,
      std::true_type,
      std::false_type
>;

using bitwise_op_type = variant<
   monostate,
   bitwise_and_op,
   bitwise_or_op,
   not_op,
   xor_op
>;

template<typename T>
using is_bitwise_op_type = std::conditional<
      std::is_same<T, bitwise_and_op>::value ||
      std::is_same<T, bitwise_or_op>::value ||
      std::is_same<T, not_op>::value ||
      std::is_same<T, xor_op>::value,
      std::true_type,
      std::false_type
>;

struct function_call;

struct decl_expr {
   std::reference_wrapper<expression_data> var;
};

using expression_type = variant<
   monostate,
   variable_type,
   decl_expr,
   assign_op,
   index_op,
   add_op,
   sub_op,
   mul_op,
   div_op,
   mod_op,
   pow_op,
   log_op,
   exp_op,
   sin_op,
   cos_op,
   tan_op,
   lt_op,
   lte_op,
   gt_op,
   gte_op,
   eq_op,
   neq_op,
   neg_op,
   not_op,
   xor_op,
   logical_and_op,
   logical_or_op,
   bitwise_and_op,
   bitwise_or_op,
   paren_op,
   recursive_wrapper<function_call>
>;

template<typename T>
using is_expression_type = std::conditional<
   std::is_same<T, variable_type>::value ||
   std::is_same<T, decl_expr>::value ||
   std::is_same<T, assign_op>::value ||
   std::is_same<T, index_op>::value ||
   std::is_same<T, add_op>::value ||
   std::is_same<T, sub_op>::value ||
   std::is_same<T, mul_op>::value ||
   std::is_same<T, div_op>::value ||
   std::is_same<T, mod_op>::value ||
   std::is_same<T, pow_op>::value ||
   std::is_same<T, log_op>::value ||
   std::is_same<T, exp_op>::value ||
   std::is_same<T, sin_op>::value ||
   std::is_same<T, cos_op>::value ||
   std::is_same<T, tan_op>::value ||
   std::is_same<T, lt_op>::value ||
   std::is_same<T, lte_op>::value ||
   std::is_same<T, gt_op>::value ||
   std::is_same<T, gte_op>::value ||
   std::is_same<T, eq_op>::value ||
   std::is_same<T, neq_op>::value ||
   std::is_same<T, neg_op>::value ||
   std::is_same<T, not_op>::value ||
   std::is_same<T, xor_op>::value ||
   std::is_same<T, logical_and_op>::value ||
   std::is_same<T, logical_or_op>::value ||
   std::is_same<T, bitwise_and_op>::value ||
   std::is_same<T, bitwise_or_op>::value ||
   std::is_same<T, paren_op>::value ||
   std::is_same<T, recursive_wrapper<function_call>>::value,
   std::true_type,
   std::false_type
>;

template<typename T>
bool is_expression(T const& t) { return is_expression_type<T>::type::value; }

struct expression_data {
   expression_type node;

   expression_data operator=(function_call t);

   expression_data operator=(expression_data t) {
      return expression_data{expression_type{
         assign_op{
            std::pair< recursive_wrapper<expression_data>, recursive_wrapper<expression_data> >{
               *this, t
            }
         }
      }};
   }

   template<typename T>
   expression_data operator=(T t) {
      using value_type = typename std::conditional< std::is_same<T, std::int8_t>::value, literal<i8>,
         typename std::conditional< std::is_same<T, std::int16_t>::value, literal<i16>,
            typename std::conditional< std::is_same<T, std::int32_t>::value, literal<i32>,
               typename std::conditional< std::is_same<T, std::int64_t>::value, literal<i64>,
                  typename std::conditional< std::is_same<T, std::uint8_t>::value, literal<u8>,
                     typename std::conditional< std::is_same<T, std::uint16_t>::value, literal<u16>,
                        typename std::conditional< std::is_same<T, std::uint32_t>::value, literal<u32>,
                           typename std::conditional< std::is_same<T, std::uint64_t>::value, literal<u64>,
                              typename std::conditional< std::is_same<T, float>::value, literal<fp32>,
                                 typename std::conditional< std::is_same<T, double>::value, literal<fp64>,
                                    typename std::conditional< std::is_same<T, bool>::value, literal<boolean>, T>::type
                                 >::type
                              >::type
                           >::type
                        >::type
                     >::type
                  >::type
               >::type
            >::type
         >::type
      >::type;
              
      static_assert(is_variable_type<value_type>::type::value, "invalid type assignment");

      if constexpr(is_literal_type<value_type>::type::value) {
         return expression_data{expression_type{assign_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, expression_data{value_type{t}}
            }
         }}};
      } 
      else {
         return expression_data{expression_type{assign_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, t
            }
         }}};
      }
   }

   template<>
   expression_data operator=(expression_data t) {
      return expression_data{expression_type{assign_op{
         std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
            *this, t
         }
      }}};
   }

   template<typename T>
   void wrap_literal(expression_data & d, T t) {
   }
   template<>
   void wrap_literal(expression_data & d, std::int8_t t) {
      d.node.emplace<variable_type>( variable_type{literal<i8>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::int16_t t) {
      d.node.emplace<variable_type>( variable_type{literal<i16>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::int32_t t) {
      d.node.emplace<variable_type>( variable_type{literal<i32>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::int64_t t) {
      d.node.emplace<variable_type>( variable_type{literal<i64>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::uint8_t t) {
      d.node.emplace<variable_type>( variable_type{literal<u8>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::uint16_t t) {
      d.node.emplace<variable_type>( variable_type{literal<u16>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::uint32_t t) {
      d.node.emplace<variable_type>( variable_type{literal<u32>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::uint64_t t) {
      d.node.emplace<variable_type>( variable_type{literal<u64>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, float t) {
      d.node.emplace<variable_type>( variable_type{literal<fp32>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, double t) {
      d.node.emplace<variable_type>( variable_type{literal<fp64>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, bool t) {
      d.node.emplace<variable_type>( variable_type{literal<boolean>{t}} );
   }

   template<typename T>
   expression_data operator()(T t) {
      return expression_data{expression_type{paren_op{
         recursive_wrapper<expression_data>{
            t
         }
      }}};
   }

   template<typename T>
   expression_data operator[](T t) {
      if constexpr(std::is_integral<T>::value) {
         expression_data val;
         wrap_literal(val, t);

         return expression_data{expression_type{index_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, val
            }
         }}};
      }
      else{
         return expression_data{expression_type{index_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, t
            }
         }}};
      }
   }

   template<typename T>
   expression_data operator+(T t) {
      if constexpr(std::is_integral<T>::value) {
         expression_data val;
         wrap_literal(val, t);

         return expression_data{expression_type{add_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, val
            }
         }}};
      }
      else{
         return expression_data{expression_type{add_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, t
            }
         }}};
      }
   }

   template<typename T>
   expression_data operator-(T t) {
      if constexpr(std::is_integral<T>::value) {
         expression_data val;
         wrap_literal(val, t);

         return expression_data{expression_type{sub_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, val
            }
         }}};
      }
      else{
         return expression_data{expression_type{sub_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, t
            }
         }}};
      }
   }

   template<typename T>
   expression_data operator*(T t) {
      if constexpr(std::is_integral<T>::value) {
         expression_data val;
         wrap_literal(val, t);

         return expression_data{expression_type{mul_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, val
            }
         }}};
      }
      else{
         return expression_data{expression_type{mul_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, t
            }
         }}};
      }
   }

   template<typename T>
   expression_data operator/(T t) {
      if constexpr(std::is_integral<T>::value) {
         expression_data val;
         wrap_literal(val, t);

         return expression_data{expression_type{div_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, val
            }
         }}};
      }
      else{
         return expression_data{expression_type{div_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, t
            }
         }}};
      }
   }

   template<typename T>
   expression_data operator%(T t) {
      if constexpr(std::is_integral<T>::value) {
         expression_data val;
         wrap_literal(val, t);

         return expression_data{expression_type{mod_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, val
            }
         }}};
      }
      else{
         return expression_data{expression_type{mod_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, t
            }
         }}};
      }
   }

   template<typename T>
   expression_data operator<(T t) {
      if constexpr(std::is_integral<T>::value) {
         expression_data val;
         wrap_literal(val, t);

         return expression_data{expression_type{lt_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, val
            }
         }}};
      }
      else{
         return expression_data{expression_type{lt_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, t
            }
         }}};
      }
   }

   template<typename T>
   expression_data operator<=(T t) {
      if constexpr(std::is_integral<T>::value) {
         expression_data val;
         wrap_literal(val, t);

         return expression_data{expression_type{lte_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, val
            }
         }}};
      }
      else{
         return expression_data{expression_type{lte_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, t
            }
         }}};
      }
   }

   template<typename T>
   expression_data operator>(T t) {
      if constexpr(std::is_integral<T>::value) {
         expression_data val;
         wrap_literal(val, t);

         return expression_data{expression_type{gt_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, val
            }
         }}};
      }
      else{
         return expression_data{expression_type{gt_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, t
            }
         }}};
      }
   }

   template<typename T>
   expression_data operator>=(T t) {
      if constexpr(std::is_integral<T>::value) {
         expression_data val;
         wrap_literal(val, t);

         return expression_data{expression_type{gte_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, val
            }
         }}};
      }
      else{
         return expression_data{expression_type{gte_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, t
            }
         }}};
      }
   }

   template<typename T>
   expression_data operator==(T t) {
      if constexpr(std::is_integral<T>::value) {
         expression_data val;
         wrap_literal(val, t);

         return expression_data{expression_type{eq_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, val
            }
         }}};
      }
      else{
         return expression_data{expression_type{eq_op{
            std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
               *this, t
            }
         }}};
      }
   }

   static void copy(expression_data & ret, expression_data & t) {
     if(mpark::holds_alternative<variable_type>(t.node)) {
        variable_type & v = mpark::get<variable_type>(t.node);
        if(mpark::holds_alternative<none>(v)) {
           ret.node.emplace<variable_type>(variable_type{none{}});
        }
        else if(mpark::holds_alternative<scalar<i8>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<i8>{mpark::get<scalar<i8>>(v).identity}});
        }
        else if(mpark::holds_alternative<scalar<i16>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<i16>{mpark::get<scalar<i16>>(v).identity}});
        }
        else if(mpark::holds_alternative<scalar<i32>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<i32>{mpark::get<scalar<i32>>(v).identity}});
        }
        else if(mpark::holds_alternative<scalar<i64>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<i64>{mpark::get<scalar<i64>>(v).identity}});
        }
        else if(mpark::holds_alternative<scalar<u8>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<u8>{mpark::get<scalar<u8>>(v).identity}});
        }
        else if(mpark::holds_alternative<scalar<u16>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<u16>{mpark::get<scalar<u16>>(v).identity}});
       }
       else if(mpark::holds_alternative<scalar<u32>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<u32>{mpark::get<scalar<u32>>(v).identity}});
       }
       else if(mpark::holds_alternative<scalar<u64>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<u64>{mpark::get<scalar<u64>>(v).identity}});
       }
       else if(mpark::holds_alternative<scalar<fp16a>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<fp16a>{mpark::get<scalar<fp16a>>(v).identity}});
       }
       else if(mpark::holds_alternative<scalar<fp16b>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<fp16b>{mpark::get<scalar<fp16b>>(v).identity}});
       }
       else if(mpark::holds_alternative<scalar<fp32>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<fp32>{mpark::get<scalar<fp32>>(v).identity}});
       }
       else if(mpark::holds_alternative<scalar<fp64>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<fp64>{mpark::get<scalar<fp64>>(v).identity}});
       }
       else if(mpark::holds_alternative<scalar<boolean>>(v)) {
           ret.node.emplace<variable_type>(variable_type{scalar<boolean>{mpark::get<scalar<boolean>>(v).identity}});
       }
       else if(mpark::holds_alternative<literal<i8>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<i8>{mpark::get<literal<i8>>(v).value}});
       }
       else if(mpark::holds_alternative<literal<i16>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<i16>{mpark::get<literal<i16>>(v).value}});
       }
       else if(mpark::holds_alternative<literal<i32>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<i32>{mpark::get<literal<i32>>(v).value}});
       }
       else if(mpark::holds_alternative<literal<i64>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<i64>{mpark::get<literal<i64>>(v).value}});
       }
       else if(mpark::holds_alternative<literal<u8>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<u8>{mpark::get<literal<u8>>(v).value}});
       }
       else if(mpark::holds_alternative<literal<u16>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<u16>{mpark::get<literal<u16>>(v).value}});
       }
       else if(mpark::holds_alternative<literal<u32>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<u32>{mpark::get<literal<u32>>(v).value}});
       }
       else if(mpark::holds_alternative<literal<u64>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<u64>{mpark::get<literal<u64>>(v).value}});
       }
       else if(mpark::holds_alternative<literal<fp16a>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<fp16a>{mpark::get<literal<fp16a>>(v).value}});
       }
       else if(mpark::holds_alternative<literal<fp16b>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<fp16b>{mpark::get<literal<fp16b>>(v).value}});
       }
       else if(mpark::holds_alternative<literal<fp32>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<fp32>{mpark::get<literal<fp32>>(v).value}});
       }
       else if(mpark::holds_alternative<literal<fp64>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<fp64>{mpark::get<literal<fp64>>(v).value}});
       }
       else if(mpark::holds_alternative<literal<boolean>>(v)) {
           ret.node.emplace<variable_type>(variable_type{literal<boolean>{mpark::get<literal<boolean>>(v).value}});
       }
       else if(mpark::holds_alternative<array<i8>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<i8>{mpark::get<array<i8>>(v).identity}});
       }
       else if(mpark::holds_alternative<array<i16>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<i16>{mpark::get<array<i16>>(v).identity}});
       }
       else if(mpark::holds_alternative<array<i32>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<i32>{mpark::get<array<i32>>(v).identity}});
       }
       else if(mpark::holds_alternative<array<i64>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<i64>{mpark::get<array<i64>>(v).identity}});
       }
       else if(mpark::holds_alternative<array<u8>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<u8>{mpark::get<array<u8>>(v).identity}});
       }
       else if(mpark::holds_alternative<array<u16>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<u16>{mpark::get<array<u16>>(v).identity}});
       }
       else if(mpark::holds_alternative<array<u32>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<u32>{mpark::get<array<u32>>(v).identity}});
       }
       else if(mpark::holds_alternative<array<u64>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<u64>{mpark::get<array<u64>>(v).identity}});
       }
       else if(mpark::holds_alternative<array<fp16a>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<fp16a>{mpark::get<array<fp16a>>(v).identity}});
       }
       else if(mpark::holds_alternative<array<fp16b>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<fp16b>{mpark::get<array<fp16b>>(v).identity}});
       }
       else if(mpark::holds_alternative<array<fp32>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<fp32>{mpark::get<array<fp32>>(v).identity}});
       }
       else if(mpark::holds_alternative<array<fp64>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<fp64>{mpark::get<array<fp64>>(v).identity}});
       }
       else if(mpark::holds_alternative<array<boolean>>(v)) {
           ret.node.emplace<variable_type>(variable_type{array<boolean>{mpark::get<array<boolean>>(v).identity}});
       }
       else if(mpark::holds_alternative<matrix<i8>>(v)) {
           auto & a = mpark::get<matrix<i8>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<i8>{a.identity, a.dimensions}});
       }
       else if(mpark::holds_alternative<matrix<i16>>(v)) {
           auto & a = mpark::get<matrix<i16>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<i16>{a.identity, a.dimensions}});
       }
       else if(mpark::holds_alternative<matrix<i32>>(v)) {
           auto & a = mpark::get<matrix<i32>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<i32>{a.identity, a.dimensions}});
       }
       else if(mpark::holds_alternative<matrix<i64>>(v)) {
           auto & a = mpark::get<matrix<i64>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<i64>{a.identity, a.dimensions}});
       }
       else if(mpark::holds_alternative<matrix<u8>>(v)) {
           auto & a = mpark::get<matrix<u8>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<u8>{a.identity, a.dimensions}});
       }
       else if(mpark::holds_alternative<matrix<u16>>(v)) {
           auto & a = mpark::get<matrix<u16>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<u16>{a.identity, a.dimensions}});
       }
       else if(mpark::holds_alternative<matrix<u32>>(v)) {
           auto & a = mpark::get<matrix<u32>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<u32>{a.identity, a.dimensions}});
       }
       else if(mpark::holds_alternative<matrix<u64>>(v)) {
           auto & a = mpark::get<matrix<u64>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<u64>{a.identity, a.dimensions}});
       }
       else if(mpark::holds_alternative<matrix<fp16a>>(v)) {
           auto & a = mpark::get<matrix<fp16a>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<fp16a>{a.identity, a.dimensions}});
       }
       else if(mpark::holds_alternative<matrix<fp16b>>(v)) {
           auto & a = mpark::get<matrix<fp16b>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<fp16b>{a.identity, a.dimensions}});
       }
       else if(mpark::holds_alternative<matrix<fp32>>(v)) {
           auto & a = mpark::get<matrix<fp32>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<fp32>{a.identity, a.dimensions}});
       }
       else if(mpark::holds_alternative<matrix<fp64>>(v)) {
           auto & a = mpark::get<matrix<fp64>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<fp64>{a.identity, a.dimensions}});
       }
       else if(mpark::holds_alternative<matrix<boolean>>(v)) {
           auto & a = mpark::get<matrix<boolean>>(v);
           ret.node.emplace<variable_type>(variable_type{matrix<boolean>{a.identity, a.dimensions}});
       }

       return;
     }
     else if(mpark::holds_alternative<decl_expr>(t.node)) {
        //auto & v = mpark::get<decl_expr>(t.node);
     }
     else if(mpark::holds_alternative<assign_op>(t.node)) {
        auto & a = mpark::get<assign_op>(t.node);
        ret.node.emplace<assign_op>(assign_op{a.args});
     }
     else if(mpark::holds_alternative<index_op>(t.node)) {
        auto & a = mpark::get<index_op>(t.node);
        ret.node.emplace<index_op>(index_op{a.args});
     }
     else if(mpark::holds_alternative<add_op>(t.node)) {
        auto & a = mpark::get<add_op>(t.node);
        ret.node.emplace<add_op>(add_op{a.args});
     }
     else if(mpark::holds_alternative<sub_op>(t.node)) {
        auto & a = mpark::get<sub_op>(t.node);
        ret.node.emplace<sub_op>(sub_op{a.args});
     }
     else if(mpark::holds_alternative<mul_op>(t.node)) {
        auto & a = mpark::get<mul_op>(t.node);
        ret.node.emplace<mul_op>(mul_op{a.args});
     }
     else if(mpark::holds_alternative<div_op>(t.node)) {
        auto & a = mpark::get<div_op>(t.node);
        ret.node.emplace<div_op>(div_op{a.args});
     }
     else if(mpark::holds_alternative<mod_op>(t.node)) {
        auto & a = mpark::get<mod_op>(t.node);
        ret.node.emplace<mod_op>(mod_op{a.args});
     }
     else if(mpark::holds_alternative<pow_op>(t.node)) {
        auto & a = mpark::get<pow_op>(t.node);
        ret.node.emplace<pow_op>(pow_op{a.args});
     }
     else if(mpark::holds_alternative<log_op>(t.node)) {
        auto & a = mpark::get<log_op>(t.node);
        ret.node.emplace<log_op>(log_op{a.args});
     }
     else if(mpark::holds_alternative<exp_op>(t.node)) {
        auto & a = mpark::get<exp_op>(t.node);
        ret.node.emplace<exp_op>(exp_op{a.args});
     }
     else if(mpark::holds_alternative<sin_op>(t.node)) {
        auto & a = mpark::get<sin_op>(t.node);
        ret.node.emplace<sin_op>(sin_op{a.args});
     }
     else if(mpark::holds_alternative<cos_op>(t.node)) {
        auto & a = mpark::get<cos_op>(t.node);
        ret.node.emplace<cos_op>(cos_op{a.args});
     }
     else if(mpark::holds_alternative<tan_op>(t.node)) {
        auto & a = mpark::get<tan_op>(t.node);
        ret.node.emplace<tan_op>(tan_op{a.args});
     }
     else if(mpark::holds_alternative<lt_op>(t.node)) {
        auto & a = mpark::get<lt_op>(t.node);
        ret.node.emplace<lt_op>(lt_op{a.args});
     }
     else if(mpark::holds_alternative<lte_op>(t.node)) {
        auto & a = mpark::get<lte_op>(t.node);
        ret.node.emplace<lte_op>(lte_op{a.args});
     }
     else if(mpark::holds_alternative<gt_op>(t.node)) {
        auto & a = mpark::get<gt_op>(t.node);
        ret.node.emplace<gt_op>(gt_op{a.args});
     }
     else if(mpark::holds_alternative<gte_op>(t.node)) {
        auto & a = mpark::get<gte_op>(t.node);
        ret.node.emplace<gte_op>(gte_op{a.args});
     }
     else if(mpark::holds_alternative<eq_op>(t.node)) {
        auto & a = mpark::get<eq_op>(t.node);
        ret.node.emplace<eq_op>(eq_op{a.args});
     }
     else if(mpark::holds_alternative<neq_op>(t.node)) {
        auto & a = mpark::get<neq_op>(t.node);
        ret.node.emplace<neq_op>(neq_op{a.args});
     }
     else if(mpark::holds_alternative<neg_op>(t.node)) {
        auto & a = mpark::get<neg_op>(t.node);
        ret.node.emplace<neg_op>(neg_op{a.node});
     }
     else if(mpark::holds_alternative<not_op>(t.node)) {
        auto & a = mpark::get<not_op>(t.node);
        ret.node.emplace<not_op>(not_op{a.node});
     }
     else if(mpark::holds_alternative<xor_op>(t.node)) {
        auto & a = mpark::get<xor_op>(t.node);
        ret.node.emplace<xor_op>(xor_op{a.args});
     }
     else if(mpark::holds_alternative<logical_and_op>(t.node)) {
        auto & a = mpark::get<logical_and_op>(t.node);
        ret.node.emplace<logical_and_op>(logical_and_op{a.args});
     }
     else if(mpark::holds_alternative<logical_or_op>(t.node)) {
        auto & a = mpark::get<logical_or_op>(t.node);
        ret.node.emplace<logical_or_op>(logical_or_op{a.args});
     }
     else if(mpark::holds_alternative<bitwise_and_op>(t.node)) {
        auto & a = mpark::get<bitwise_and_op>(t.node);
        ret.node.emplace<bitwise_and_op>(bitwise_and_op{a.args});
     }
     else if(mpark::holds_alternative<bitwise_or_op>(t.node)) {
        auto & a = mpark::get<bitwise_or_op>(t.node);
        ret.node.emplace<bitwise_or_op>(bitwise_or_op{a.args});
     }
     else if(mpark::holds_alternative<paren_op>(t.node)) {
        auto & a = mpark::get<paren_op>(t.node);
        ret.node.emplace<paren_op>(paren_op{a.node});
     }
     else if(mpark::holds_alternative<recursive_wrapper<function_call>>(t.node)) {
        //auto & v = mpark::get<recursive_wrapper<function_call>>(t.node);
        //ret.node.emplace<recursive_wrapper<function_call>>(variable_type{recursive_wrapper<function_call>{a.args}});
     }
  }

/*
        else if(mpark::holds_alternative<pointer<scalar<i8>>(v))
        else if(mpark::holds_alternative<pointer<scalar<i16>>(v))
        else if(mpark::holds_alternative<pointer<scalar<i32>>(v))
        else if(mpark::holds_alternative<pointer<scalar<i64>>(v))
        else if(mpark::holds_alternative<pointer<scalar<u8>>(v))
        else if(mpark::holds_alternative<pointer<scalar<u16>>(v))
        else if(mpark::holds_alternative<pointer<scalar<u32>>(v))
        else if(mpark::holds_alternative<pointer<scalar<u64>>(v))
        else if(mpark::holds_alternative<pointer<scalar<fp16a>>(v))
        else if(mpark::holds_alternative<pointer<scalar<fp16b>>(v))
        else if(mpark::holds_alternative<pointer<scalar<fp32>>(v))
        else if(mpark::holds_alternative<pointer<scalar<fp64>>(v))
        else if(mpark::holds_alternative<pointer<scalar<boolean>>(v))
        else if(mpark::holds_alternative<pointer<array<i8>>(v))
        else if(mpark::holds_alternative<pointer<array<i16>>(v))
        else if(mpark::holds_alternative<pointer<array<i32>>(v))
        else if(mpark::holds_alternative<pointer<array<i64>>(v))
        else if(mpark::holds_alternative<pointer<array<u8>>(v))
        else if(mpark::holds_alternative<pointer<array<u16>>(v))
        else if(mpark::holds_alternative<pointer<array<u32>>(v))
        else if(mpark::holds_alternative<pointer<array<u64>>(v))
        else if(mpark::holds_alternative<pointer<array<fp16a>>(v))
        else if(mpark::holds_alternative<pointer<array<fp16b>>(v))
        else if(mpark::holds_alternative<pointer<array<fp32>>(v))
        else if(mpark::holds_alternative<pointer<array<fp64>>(v))
        else if(mpark::holds_alternative<pointer<array<boolean>>(v))
        else if(mpark::holds_alternative<pointer<matrix<i8>>(v))
        else if(mpark::holds_alternative<pointer<matrix<i16>>(v))
        else if(mpark::holds_alternative<pointer<matrix<i32>>(v))
        else if(mpark::holds_alternative<pointer<matrix<i64>>(v))
        else if(mpark::holds_alternative<pointer<matrix<u8>>(v))
        else if(mpark::holds_alternative<pointer<matrix<u16>>(v))
        else if(mpark::holds_alternative<pointer<matrix<u32>>(v))
        else if(mpark::holds_alternative<pointer<matrix<u64>>(v))
        else if(mpark::holds_alternative<pointer<matrix<fp16a>>(v))
        else if(mpark::holds_alternative<pointer<matrix<fp16b>>(v))
        else if(mpark::holds_alternative<pointer<matrix<fp32>>(v))
        else if(mpark::holds_alternative<pointer<matrix<fp64>>(v))
        else if(mpark::holds_alternative<pointer<matrix<boolean>>(v))
        else if(mpark::holds_alternative<reference<scalar<i8>>(v))
        else if(mpark::holds_alternative<reference<scalar<i16>>(v))
        else if(mpark::holds_alternative<reference<scalar<i32>>(v))
        else if(mpark::holds_alternative<reference<scalar<i64>>(v))
        else if(mpark::holds_alternative<reference<scalar<u8>>(v))
        else if(mpark::holds_alternative<reference<scalar<u16>>(v))
        else if(mpark::holds_alternative<reference<scalar<u32>>(v))
        else if(mpark::holds_alternative<reference<scalar<u64>>(v))
        else if(mpark::holds_alternative<reference<scalar<fp16a>>(v))
        else if(mpark::holds_alternative<reference<scalar<fp16b>>(v))
        else if(mpark::holds_alternative<reference<scalar<fp32>>(v))
        else if(mpark::holds_alternative<reference<scalar<fp64>>(v))
        else if(mpark::holds_alternative<reference<scalar<boolean>>(v))
        else if(mpark::holds_alternative<reference<array<i8>>(v))
        else if(mpark::holds_alternative<reference<array<i16>>(v))
        else if(mpark::holds_alternative<reference<array<i32>>(v))
        else if(mpark::holds_alternative<reference<array<i64>>(v))
        else if(mpark::holds_alternative<reference<array<u8>>(v))
        else if(mpark::holds_alternative<reference<array<u16>>(v))
        else if(mpark::holds_alternative<reference<array<u32>>(v))
        else if(mpark::holds_alternative<reference<array<u64>>(v))
        else if(mpark::holds_alternative<reference<array<fp16a>>(v))
        else if(mpark::holds_alternative<reference<array<fp16b>>(v))
        else if(mpark::holds_alternative<reference<array<fp32>>(v))
        else if(mpark::holds_alternative<reference<array<fp64>>(v))
        else if(mpark::holds_alternative<reference<array<boolean>>(v))
        else if(mpark::holds_alternative<reference<matrix<i8>>(v))
        else if(mpark::holds_alternative<reference<matrix<i16>>(v))
        else if(mpark::holds_alternative<reference<matrix<i32>>(v))
        else if(mpark::holds_alternative<reference<matrix<i64>>(v))
        else if(mpark::holds_alternative<reference<matrix<u8>>(v))
        else if(mpark::holds_alternative<reference<matrix<u16>>(v))
        else if(mpark::holds_alternative<reference<matrix<u32>>(v))
        else if(mpark::holds_alternative<reference<matrix<u64>>(v))
        else if(mpark::holds_alternative<reference<matrix<fp16a>>(v))
        else if(mpark::holds_alternative<reference<matrix<fp16b>>(v))
        else if(mpark::holds_alternative<reference<matrix<fp32>>(v))
        else if(mpark::holds_alternative<reference<matrix<fp64>>(v))
        else if(mpark::holds_alternative<reference<matrix<boolean>>(v))
*/

};

static inline expression_data _ = expression_data{expression_type{paren_op{}}};

struct VariableDeclVisitor {

   std::uint64_t const indent;
   std::string & buf;

   VariableDeclVisitor(std::uint64_t const i, std::string & b) : indent(i), buf(b) {}

   template<typename T>
   void operator()(T const& t) {
   }

   template<>
   void operator()(scalar<i8> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(scalar<i16> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(scalar<i32> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(scalar<i64> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(scalar<u8> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(scalar<u16> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(scalar<u32> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(scalar<u64> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(scalar<fp16a> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(scalar<fp16b> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(scalar<fp32> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(scalar<fp64> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(array<i8> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(array<i16> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(array<i32> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(array<i64> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(array<u8> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(array<u16> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(array<u32> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(array<u64> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(array<fp16a> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(array<fp16b> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(array<fp32> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(array<fp64> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(matrix<i8> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(matrix<i16> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(matrix<i32> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(matrix<i64> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(matrix<u8> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(matrix<u16> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(matrix<u32> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(matrix<u64> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(matrix<fp16a> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(matrix<fp16b> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(matrix<fp32> const& t) {
      t.decl(buf);
   }

   template<>
   void operator()(matrix<fp64> const& t) {
      t.decl(buf);
   }
};

struct VariableVisitor {

   std::uint64_t const indent;
   std::string & buf;

   VariableVisitor(std::uint64_t const i, std::string & b) : indent(i), buf(b) {}

   template<typename T>
   void operator()(T const& t) {
   }

   template<>
   void operator()(scalar<i8> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(scalar<i16> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(scalar<i32> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(scalar<i64> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(scalar<u8> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(scalar<u16> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(scalar<u32> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(scalar<u64> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(scalar<fp16a> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(scalar<fp16b> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(scalar<fp32> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(scalar<fp64> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(array<i8> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(array<i16> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(array<i32> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(array<i64> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(array<u8> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(array<u16> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(array<u32> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(array<u64> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(array<fp16a> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(array<fp16b> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(array<fp32> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(array<fp64> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(matrix<i8> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(matrix<i16> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(matrix<i32> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(matrix<i64> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(matrix<u8> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(matrix<u16> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(matrix<u32> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(matrix<u64> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(matrix<fp16a> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(matrix<fp16b> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(matrix<fp32> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(matrix<fp64> const& t) {
      buf += t.identity;
   }

   template<>
   void operator()(literal<i8> const& t) {
      buf += std::to_string(t.value);
   }

   template<>
   void operator()(literal<i16> const& t) {
      buf += std::to_string(t.value);
   }

   template<>
   void operator()(literal<i32> const& t) {
      buf += std::to_string(t.value);
   }

   template<>
   void operator()(literal<i64> const& t) {
      buf += std::to_string(t.value);
   }

   template<>
   void operator()(literal<u8> const& t) {
      buf += std::to_string(t.value);
   }

   template<>
   void operator()(literal<u16> const& t) {
      buf += std::to_string(t.value);
   }

   template<>
   void operator()(literal<u32> const& t) {
      buf += std::to_string(t.value);
   }

   template<>
   void operator()(literal<u64> const& t) {
      buf += std::to_string(t.value);
   }

   template<>
   void operator()(literal<fp32> const& t) {
      buf += std::to_string(t.value);
   }

   template<>
   void operator()(literal<fp64> const& t) {
      buf += std::to_string(t.value);
   }

   template<>
   void operator()(recursive_wrapper<expression_data> const& t) {
      (*this)(t.get());
   }

   template<>
   void operator()(expression_data const& t) {
      (*this)(t.node);
   }

   template<>
   void operator()(monostate const& t) {
   }

   template<>
   void operator()(placeholder const& t) {
   }
};

struct ExpressionVisitor {

   std::uint64_t & indent;
   std::string & buf;

   ExpressionVisitor(std::uint64_t & i, std::string & b) : indent(i), buf(b) {}

   template<typename T>
   void operator()(T const& t) {
   }

   template<>
   void operator()(variable_type const& t) {
     visit(VariableVisitor{indent, buf}, t);
   }

   template<>
   void operator()(decl_expr const& t) {
     visit(VariableDeclVisitor{indent, buf}, get<variable_type>(t.var.get().node));
   }

   template<>
   void operator()(assign_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " = ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(add_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " + ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(sub_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " - ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(mul_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " * ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(div_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " / ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(mod_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " % ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(paren_op const& t) {
      buf += "( ";
      visit(*this, t.node.get().node);
      buf += " )";
   }

   template<>
   void operator()(index_op const& t) {
      auto & node_ref = t.args.first.get().node;

      if(holds_alternative<variable_type>(node_ref)) {
          visit(VariableVisitor{indent, buf}, get<variable_type>(node_ref));
      }
      else {
          visit(*this, node_ref);
      }

      buf += " [ ";
      visit(*this, t.args.second.get().node);
      buf += " ] ";
   }

   template<>
   void operator()(lt_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " < ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(gt_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " > ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(lte_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " <= ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(gte_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " >= ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(eq_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " == ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(neq_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " != ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(logical_and_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " && ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(logical_or_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " || ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(bitwise_and_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " & ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(bitwise_or_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " | ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(xor_op const& t) {
      visit(*this, t.args.first.get().node);
      buf += " ^ ";
      visit(*this, t.args.second.get().node);
   }

   template<>
   void operator()(recursive_wrapper<function_call> const& t);

   template<>
   void operator()(recursive_wrapper<function_call> const& t);
};

expression_data decl(expression_data & var) {
   return expression_data{expression_type{decl_expr{var}}};
}

expression_type decl(expression_data & a, expression_data & b) {
   return assign_op{
      std::pair<recursive_wrapper<expression_data>, recursive_wrapper<expression_data>>{
         a,b
      }
   };
}

using conditional_type = variant<
   monostate,
   binary_op_type,
   unary_op_type,
   bitwise_op_type
>;

template<typename T>
using is_conditional_type = std::conditional<
   is_binary_op_type<T>::type::value ||
   is_unary_op_type<T>::type::value ||
   is_bitwise_op_type<T>::type::value,
   std::true_type,
   std::false_type
>;

struct for_;
struct while_;
struct if_;
struct switch_;
struct function_def;

struct comment {
    std::string data;
};

struct filepath {
    std::string data;
};

static inline const filepath cstdint{"cstdint"};

struct include {
   filepath path;

   include() = delete;

   include(filepath pth) : path(pth) {
   }
};

using statement = variant<
   monostate,
   expression_data,
   recursive_wrapper<for_>,
   recursive_wrapper<while_>,
   recursive_wrapper<if_>,
   recursive_wrapper<switch_>,
   recursive_wrapper<function_def>,
   comment,
   include
>;

template<typename T>
using is_statement_type = std::conditional<
   std::is_same<T, expression_data>::value ||
   std::is_same<T, recursive_wrapper<for_>>::value ||
   std::is_same<T, recursive_wrapper<while_>>::value ||
   std::is_same<T, recursive_wrapper<if_>>::value ||
   std::is_same<T, recursive_wrapper<switch_>>::value ||
   std::is_same<T, recursive_wrapper<function_def>>::value ||
   std::is_same<T, comment>::value ||
   std::is_same<T, include>::value,
   std::true_type,
   std::false_type
>;

template<typename T>
bool is_statement(T const& t) { return is_statement_type<T>::type::value; }

struct StatementVisitor {

   std::uint64_t & indent;
   std::string & buf;
   bool is_expression_data;
   bool is_comment;

   StatementVisitor(std::uint64_t & i, std::string & b) : indent(i), buf(b), is_expression_data(false), is_comment(false) {
      for(std::uint64_t i = 0; i < indent; ++i) {
         buf += "    ";
      }
   }

   static inline const std::string term[2] = { " ;\n", ";\n" };

   ~StatementVisitor() {
      if(is_comment) {
         buf += "\n"; indent--;
         is_comment = false;
      }
      else if(indent > 0 && !is_expression_data) {
         buf += term[buf.back() == ' ']; indent--;
      }
      else if(is_expression_data) {
         buf += "\n"; indent--;
         is_expression_data = false;
      }
   }

   template<typename T>
   void operator()(T const& t) {
      if constexpr(is_expression_type<T>::type::value) {
          (*this)(expression_data{t});
      }
      else {
          std::cerr<< "ERROR\t" << typeid(T).name() << std::endl;
      }
   }

  
   template<>
   void operator()(expression_data const& t) {
      visit(ExpressionVisitor{indent, buf}, t.node);
   }

   template<>
   void operator()(comment const& t) {
      buf += fmt::format("// {}", t.data);
      is_comment = true;
   }

   template<>
   void operator()(include const& t) {
      buf += fmt::format("#include<{}>", t.path.data);
      is_comment = true;
   }

   template<>
   void operator()(placeholder const& t) {
      visit(PlaceholderVisitor{buf}, t);
   }

   template<>
   void operator()(recursive_wrapper<for_> const& t);

   template<>
   void operator()(recursive_wrapper<while_> const& t);

   template<>
   void operator()(recursive_wrapper<if_> const& t);

   template<>
   void operator()(recursive_wrapper<switch_> const& t);

   template<>
   void operator()(recursive_wrapper<function_def> const& t);

};

struct loop_base {
   std::vector<statement> statements;

   loop_base() : statements() {}

   loop_base(std::vector<statement> & stmts) : statements(stmts) {}
   loop_base(std::initializer_list<statement> stmts) : statements(stmts) {}
};

struct for_ : public loop_base {

   expression_data init_expr;
   expression_data cond_expr;
   expression_data incr_expr;

   //for_(binary_op_type init, conditional_type cond, binary_op_type incr, std::initializer_list<statement> statements) :
   //
   for_(expression_data init, expression_data cond, expression_data incr, std::initializer_list<statement> statements) :
      loop_base(statements), init_expr(init), cond_expr(cond), incr_expr(incr) {
   } 

   for_(expression_data init, expression_data cond, expression_data incr, std::vector<statement> statements) :
      loop_base(statements), init_expr(init), cond_expr(cond), incr_expr(incr) {
   } 

};

template<>
void StatementVisitor::operator()(recursive_wrapper<for_> const& t) {
   is_expression_data = true;

   for_ const& t_val = t.get();

   buf += "for ( ";

   visit(*this, t_val.init_expr.node); 
   buf += " ; ";

   visit(*this, t_val.cond_expr.node); 
   buf += " ; ";

   visit(*this, t_val.incr_expr.node); 
   buf += " ) {\n";

   std::uint64_t & indent = this->indent;
   indent += 1UL;

   auto & t_val_statements = t_val.statements;
   for(auto & stmt : t_val_statements) {
      for(std::uint64_t i = 0; i < indent; ++i) {
         buf += "    ";
      }

      visit(*this, stmt);

      if(!holds_alternative<monostate>(stmt)) {
         buf += ";\n";
      }
   }

   indent -= 1UL;

   for(std::uint64_t i = 0; i < indent; ++i) {
      buf += "    ";
   }

   buf += "}";
}

struct while_ : public loop_base {
   expression_data cond_expr;

   //while_(conditional_type cond, std::initializer_list<statement> statements) :

   while_(expression_data cond, std::initializer_list<statement> statements) :
      loop_base(statements), cond_expr(cond) {
   } 
};

template<>
void StatementVisitor::operator()(recursive_wrapper<while_> const& t) {
   is_expression_data = true;

   while_ const& t_val = t.get();

   buf += "while ( ";

   visit(*this, t_val.cond_expr.node);

   buf += " ) {\n";

   std::uint64_t & indent = this->indent;
   indent += 1UL;

   auto & t_val_statements = t_val.statements;
   for(auto & stmt : t_val_statements) {
      for(std::uint64_t i = 0; i < indent; ++i) {
         buf += "    ";
      }

      visit(*this, stmt);

      if(!holds_alternative<monostate>(stmt)) {
         buf += ";\n";
      }
   }

   indent -= 1UL;

   for(std::uint64_t i = 0; i < indent; ++i) {
      buf += "    ";
   }

   buf += "}";   
}

using loop_types = variant<
   monostate,
   for_,
   while_ 
>;

struct if_ {

   template<typename T>
   if_(T cond, std::initializer_list<statement> stmts) :
      statements({std::make_pair<expression_data, std::vector<statement>>(expression_data{cond}, stmts)}) {
      static_assert(is_conditional_type<T>::type::value, "invalid conditional expression used in if_ statement");
   }

   if_(expression_data cond, std::initializer_list<statement> stmts) :
      statements({std::make_pair<expression_data, std::vector<statement>>(expression_data{cond}, stmts)}) {
   }

   template<typename T>
   if_ & else_if_(T cond, std::initializer_list<statement> stmts) {
     static_assert(is_conditional_type<T>::type::value, "invalid conditional expression used in if_ statement");

     statements.push_back({std::make_pair<expression_data, std::vector<statement>>(expression_data{cond}, stmts)});
     return (*this);
   }

   if_ & else_if_(expression_data cond, std::initializer_list<statement> stmts) {
     statements.push_back({std::make_pair<expression_data, std::vector<statement>>(expression_data{cond}, stmts)});
     return (*this);
   }

   if_ & else_(std::initializer_list<statement> stmts) {
     statements.push_back({std::make_pair<expression_data, std::vector<statement>>(expression_data{}, stmts)});
     return (*this);
   }

   std::vector< std::pair<expression_data, std::vector<statement> > > statements;
};

template<>
void StatementVisitor::operator()(recursive_wrapper<if_> const& t) {
   is_expression_data = true;

   if_ const& t_val = t.get();

   if(t_val.statements.size() < 1) {
      std::cerr << "if_ expression lacks conditional and statements" << std::endl;
   }

   std::vector< std::pair<expression_data, std::vector<statement> > >::const_iterator beg_itr =
      t_val.statements.begin();

   std::vector< std::pair<expression_data, std::vector<statement> > >::const_iterator end_itr =
      t_val.statements.end();

   for(auto itr = beg_itr; itr != end_itr; ++itr) {
      if(itr == beg_itr) {
         buf += "if ( ";
         visit(*this, itr->first.node);
         buf += " ) ";
      }
      else if( holds_alternative<monostate>(itr->first.node) ) {
         buf += "\n";
         for(std::uint64_t i = 0; i < indent; ++i) {
            buf += "    ";
         }
         buf += "else";
      }
      else {
         buf += "\n";
         for(std::uint64_t i = 0; i < indent; ++i) {
            buf += "    ";
         }
         buf += "else if ( ";
         visit(*this, itr->first.node);
         buf += " ) ";
      }
      buf += " {\n"; 

      std::uint64_t & indent = this->indent;
      indent += 1UL;

      auto & itr_statements = itr->second;
      for(auto & stmt : itr_statements) {
         for(std::uint64_t i = 0; i < indent; ++i) {
            buf += "    ";
         }

         visit(*this, stmt);

         if(!holds_alternative<monostate>(stmt)) {
            buf += ";\n";
         }
      }

      indent -= 1UL;

      for(std::uint64_t i = 0; i < indent; ++i) {
         buf += "    ";
      }

      buf += "}";
   }
}

struct switch_ {

   template<typename T>
   void wrap_literal(expression_data & d, T t) {
   }
   template<>
   void wrap_literal(expression_data & d, std::int8_t t) {
      d.node.emplace<variable_type>( variable_type{literal<i8>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::int16_t t) {
      d.node.emplace<variable_type>( variable_type{literal<i16>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::int32_t t) {
      d.node.emplace<variable_type>( variable_type{literal<i32>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::int64_t t) {
      d.node.emplace<variable_type>( variable_type{literal<i64>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::uint8_t t) {
      d.node.emplace<variable_type>( variable_type{literal<u8>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::uint16_t t) {
      d.node.emplace<variable_type>( variable_type{literal<u16>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::uint32_t t) {
      d.node.emplace<variable_type>( variable_type{literal<u32>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::uint64_t t) {
      d.node.emplace<variable_type>( variable_type{literal<u64>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, float t) {
      d.node.emplace<variable_type>( variable_type{literal<fp32>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, double t) {
      d.node.emplace<variable_type>( variable_type{literal<fp64>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, bool t) {
      d.node.emplace<variable_type>( variable_type{literal<boolean>{t}} );
   }

   switch_() = delete;

   template<typename T>
   switch_(T var) :
      variable(), cases(), default_case() {

      if constexpr(std::is_integral<T>::value) {
         wrap_literal(variable, var);
      }
      else {
         variable = expression_data{var};
      }
   }

   template<>
   switch_(expression_data var) :
      variable(var), cases(), default_case() {
   }

   template<typename T>
   switch_ & case_(T var, std::initializer_list< statement > stmts) {

      if constexpr(std::is_integral<T>::value) {
         expression_data val;
         wrap_literal(val, var);

         cases.push_back({std::make_pair<>(val, stmts)});
      }
      else{
         cases.push_back({std::make_pair<>(var, stmts)});
      }

      return (*this);
   }

   switch_ & default_(std::initializer_list< statement > stmts) {
      std::vector<statement> stmts_(stmts);
      default_case.reserve(stmts_.size());
      for(auto const& stmt : stmts_) {
         default_case.push_back(stmt);
      }

      return (*this);
   }

   expression_data variable;
   std::vector< std::pair< expression_data, std::vector< statement > > > cases;
   std::vector< statement > default_case;
};

template<>
void StatementVisitor::operator()(recursive_wrapper<switch_> const& t) {
   is_expression_data = true;

   switch_ const& t_val = t.get();

   if(t_val.cases.size() < 1) {
      std::cerr << "switch_ expression lacks cases and statements" << std::endl;
   }

   buf += "switch ( ";
   visit(*this, t_val.variable.node);
   buf += " ) {\n";

   std::uint64_t & out_indent = this->indent;
   out_indent += 1UL;

   std::vector< std::pair<expression_data, std::vector<statement> > >::const_iterator beg_itr =
      t_val.cases.begin();

   std::vector< std::pair<expression_data, std::vector<statement> > >::const_iterator end_itr =
      t_val.cases.end();

   for(auto itr = beg_itr; itr != end_itr; ++itr) {
      std::uint64_t & indent = this->indent;

      for(std::uint64_t i = 0; i < indent; ++i) {
         buf += "    ";
      }

      buf += "case ";
      visit(*this, itr->first.node);
      buf += " :\n";

      for(std::uint64_t i = 0; i < indent; ++i) {
         buf += "    ";
      }
      buf += "{\n";

      indent += 1UL;
      auto & itr_statements = itr->second;
      for(auto & stmt : itr_statements) {
         for(std::uint64_t i = 0; i < indent; ++i) {
            buf += "    ";
         }

         visit(*this, stmt);

         if(!holds_alternative<monostate>(stmt)) {
            buf += ";\n";
         }
      }

      indent -= 1UL;

      for(std::uint64_t i = 0; i < indent; ++i) {
         buf += "    ";
      }

      buf += "}\n";


      for(std::uint64_t i = 0; i < indent; ++i) {
         buf += "    ";
      }

      buf += "break;\n";

   }

   if(0 < t_val.default_case.size()) {
      std::uint64_t & indent = this->indent;

      for(std::uint64_t i = 0; i < indent; ++i) {
         buf += "    ";
      }
      buf += "default:\n";

      for(std::uint64_t i = 0; i < indent; ++i) {
         buf += "    ";
      }

      buf += "{\n";

      indent += 1UL;

      for(auto & stmt : t_val.default_case) {
         for(std::uint64_t i = 0; i < indent; ++i) {
            buf += "    ";
         }

         visit(*this, stmt);

         if(!holds_alternative<monostate>(stmt)) {
            buf += ";\n";
         }
      }

      indent -=  1UL;

      for(std::uint64_t i = 0; i < indent; ++i) {
         buf += "    ";
      }

      buf += "}\n";

      for(std::uint64_t i = 0; i < indent; ++i) {
         buf += "    ";
      }

      buf += "break;\n";
   }

   out_indent -= 1UL;

   for(std::uint64_t i = 0; i < out_indent; ++i) {
         buf += "    ";
   }

   buf += "}";
}

struct function_decl {
   std::string ident;
   std::vector<variable_type> args;
   variable_type return_type;

   template<typename T>
   std::string argument_str_template() const {
      static_assert(is_variable_type<T>::type::value, "argument_str_template was passed a non-variable_type type");
      using value_type = typename T::value_type;
      return fmt::format("{}", value_type::value);
   }

   void return_type_str(std::string & buf) const {
     if(holds_alternative<scalar<i8>>(return_type)) {
        buf += argument_str_template<scalar<i8>>();
     }
     else if(holds_alternative<scalar<i16>>(return_type)) {
        buf += argument_str_template<scalar<i16>>();
     }
     else if(holds_alternative<scalar<i32>>(return_type)) {
        buf += argument_str_template<scalar<i32>>();
     }
     else if(holds_alternative<scalar<i64>>(return_type)) {
        buf += argument_str_template<scalar<i64>>();
     }
     else if(holds_alternative<scalar<u8>>(return_type)) {
        buf += argument_str_template<scalar<u8>>();
     }
     else if(holds_alternative<scalar<u16>>(return_type)) {
        buf += argument_str_template<scalar<u16>>();
     }
     else if(holds_alternative<scalar<u32>>(return_type)) {
        buf += argument_str_template<scalar<u32>>();
     }
     else if(holds_alternative<scalar<u64>>(return_type)) {
        buf += argument_str_template<scalar<u64>>();
     }
     else if(holds_alternative<scalar<fp16a>>(return_type)) {
        buf += argument_str_template<scalar<fp16b>>();
     }
     else if(holds_alternative<scalar<fp16b>>(return_type)) {
        buf += argument_str_template<scalar<fp16b>>();
     }
     else if(holds_alternative<scalar<fp32>>(return_type)) {
        buf += argument_str_template<scalar<fp32>>();
     }
     else if(holds_alternative<scalar<fp64>>(return_type)) {
        buf += argument_str_template<scalar<fp64>>();
     }
     else if(holds_alternative<scalar<boolean>>(return_type)) {
        buf += argument_str_template<scalar<boolean>>();
     }
     else if(holds_alternative<array<i8>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<i8>>());
     }
     else if(holds_alternative<array<i16>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<i16>>());
     }
     else if(holds_alternative<array<i32>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<i32>>());
     }
     else if(holds_alternative<array<i64>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<i64>>());
     }
     else if(holds_alternative<array<u8>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<u8>>());
     }
     else if(holds_alternative<array<u16>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<u16>>());
     }
     else if(holds_alternative<array<u32>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<u32>>());
     }
     else if(holds_alternative<array<u64>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<u64>>());
     }
     else if(holds_alternative<array<fp16a>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<fp16b>>());
     }
     else if(holds_alternative<array<fp16b>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<fp16b>>());
     }
     else if(holds_alternative<array<fp32>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<fp32>>());
     }
     else if(holds_alternative<array<fp64>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<fp64>>());
     }
     else if(holds_alternative<array<boolean>>(return_type)) {
        buf += fmt::format("{} []", argument_str_template<matrix<boolean>>());
     }
     else if(holds_alternative<matrix<i8>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<i8>>());
     }
     else if(holds_alternative<matrix<i16>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<i16>>());
     }
     else if(holds_alternative<matrix<i32>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<i32>>());
     }
     else if(holds_alternative<matrix<i64>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<i64>>());
     }
     else if(holds_alternative<matrix<u8>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<u8>>());
     }
     else if(holds_alternative<matrix<u16>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<u16>>());
     }
     else if(holds_alternative<matrix<u32>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<u32>>());
     }
     else if(holds_alternative<matrix<u64>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<u64>>());
     }
     else if(holds_alternative<matrix<fp16a>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<fp16b>>());
     }
     else if(holds_alternative<matrix<fp16b>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<fp16b>>());
     }
     else if(holds_alternative<matrix<fp32>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<fp32>>());
     }
     else if(holds_alternative<matrix<fp64>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<fp64>>());
     }
     else if(holds_alternative<matrix<boolean>>(return_type)) {
        buf += fmt::format("{} [][]", argument_str_template<matrix<boolean>>());
     }

     buf += "void";
   }

   void decl(std::string & buf) const {
      return_type_str(buf);
      buf += fmt::format(" {}", ident);
   }
};

struct function_def {
   function_decl const& fdecl;

   std::vector<placeholder> placeholders;
   std::vector<statement> statements; 

   function_def & operator()(std::initializer_list<placeholder> plhs) {
      placeholders.reserve(plhs.size());

      for(auto & plh : plhs) {
         placeholders.push_back(plh);
      }
  
      return (*this);
   }

   function_def & operator[](std::initializer_list<statement> stmts) {
      statements.reserve(stmts.size());

      for(auto & stmt : stmts) {
         statements.push_back(stmt);
      }

      return (*this);
   }

   void decl(std::string & buf) const {
      fdecl.decl(buf);
   }
};

static inline function_decl const kernel_main_decl{"kernel_main", {}, {}};
static inline function_def kernel_main{kernel_main_decl, {}, {}};

template<>
void StatementVisitor::operator()(recursive_wrapper<function_def> const& t) {
   is_expression_data = true;

   function_def const& t_val = t.get();

   t_val.decl(buf);

   buf += " ( ";
   auto ph_beg_itr = t_val.placeholders.begin();
   auto ph_end_itr = t_val.placeholders.end();

   static std::string const comma[2] = {" , ", ""};
   static std::string const terminal[2] = {";\n", "\n"};

   for(ph_beg_itr = t_val.placeholders.begin(); ph_beg_itr != ph_end_itr; ++ph_beg_itr) {
      visit(*this, *ph_beg_itr);
      buf += comma[ph_beg_itr+1 == ph_end_itr];
   }

   buf += " ) {\n";

   std::vector< statement >::const_iterator beg_itr =
      t_val.statements.begin();

   std::vector< statement >::const_iterator end_itr =
      t_val.statements.end();

   const std::uint64_t indent = this->indent;
   ++this->indent;

   for(auto itr = beg_itr; itr != end_itr; ++itr) {

      for(std::uint64_t i = 0; i < this->indent; ++i) {
         buf += "    ";
      }

      visit(*this, *itr);

      buf += terminal[(
         holds_alternative<monostate>(*itr) ||
         holds_alternative<comment>(*itr) ||
         holds_alternative<recursive_wrapper<for_>>(*itr) ||
         holds_alternative<recursive_wrapper<while_>>(*itr) ||
         holds_alternative<recursive_wrapper<if_>>(*itr) ||
         holds_alternative<recursive_wrapper<switch_>>(*itr) ||
         holds_alternative<recursive_wrapper<function_def>>(*itr)
      )];

   }

   this->indent = indent;

   for(std::uint64_t i = 0; i < indent; ++i) {
      buf += "    ";
   }

   buf += "}";
}

struct function_call {

   function_decl const& fdecl;

   std::vector<statement> arguments; 

   template<typename T>
   void wrap_literal(expression_data & d, T t) {
   }
   template<>
   void wrap_literal(expression_data & d, std::int8_t t) {
      d.node.emplace<variable_type>( variable_type{literal<i8>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::int16_t t) {
      d.node.emplace<variable_type>( variable_type{literal<i16>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::int32_t t) {
      d.node.emplace<variable_type>( variable_type{literal<i32>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::int64_t t) {
      d.node.emplace<variable_type>( variable_type{literal<i64>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::uint8_t t) {
      d.node.emplace<variable_type>( variable_type{literal<u8>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::uint16_t t) {
      d.node.emplace<variable_type>( variable_type{literal<u16>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::uint32_t t) {
      d.node.emplace<variable_type>( variable_type{literal<u32>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, std::uint64_t t) {
      d.node.emplace<variable_type>( variable_type{literal<u64>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, float t) {
      d.node.emplace<variable_type>( variable_type{literal<fp32>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, double t) {
      d.node.emplace<variable_type>( variable_type{literal<fp64>{t}} );
   }
   template<>
   void wrap_literal(expression_data & d, bool t) {
      d.node.emplace<variable_type>( variable_type{literal<boolean>{t}} );
   }

   expression_data operator()() {
      auto _new = function_call{*this};
      return expression_data{
         recursive_wrapper<function_call>{_new}
      };
   }

   template<typename T>
   expression_data operator()(T t) {
      function_call _new = function_call{*this};
      _new.arguments.erase(_new.arguments.begin(), _new.arguments.end());

      expression_data val;
      if constexpr(std::is_integral<T>::value) {
         wrap_literal(val, t);
      }

      _new.arguments.push_back(val);

      //return _new;
      return expression_data{
         recursive_wrapper<function_call>{_new}
      };
   }

   template<typename T>
   void append_args(T t) {

      if constexpr(std::is_integral<T>::value) {
         (*this).arguments.emplace_back(expression_data{});
         wrap_literal((*this).arguments.back(), t);
      }
      else if constexpr(is_variable_type<T>::type::value) {
         (*this).arguments.emplace_back(t);
      }
      else if constexpr(std::is_same<expression_data, T>::value) {
         (*this).arguments.emplace_back(t);
      }
      else {
         std::cerr << "ERROR\t" << typeid(T).name() << std::endl;
      }

   }

   template<typename T, typename... F>
   void append_args(T const& first, F const&... rest) {
      append_args(first);
      append_args(rest...);
   }

   template<typename T, typename... F>
   expression_data operator()(T const& first, F const&... rest) {
      function_call _new = function_call{*this};
      _new.arguments.erase(_new.arguments.begin(), _new.arguments.end());
      _new.append_args(first);
      _new.append_args(rest...);
      //return _new;
      return expression_data{
         recursive_wrapper<function_call>{_new}
      };
   }

};

// struct function_call is forward declared implementation of expression_data::operator= below
//
expression_data expression_data::operator=(function_call t) {
   return expression_data{expression_type{
      assign_op{
         std::pair< recursive_wrapper<expression_data>, recursive_wrapper<expression_data> >{
            *this, expression_data{expression_type{recursive_wrapper<function_call>{t}}}
         }
      }
   }};
}

// struct function_call is forward declared implementation of ExpressionVisitor::operator()(function_call const&) below
//
template<>
void ExpressionVisitor::operator()(function_call const& t) {

   std::size_t argi = 0;
   std::size_t argsz = t.arguments.size()-1U;

   static std::string const delim [2] = { "", ", " };

   buf += t.fdecl.ident + "( ";

   for(auto const& arg : t.arguments) {
      std::uint64_t i = 0;

      visit(StatementVisitor{i, buf}, arg);

      buf += delim[argi < argsz];
      ++argi;
   }

   buf += " )";
}

// struct function_call is forward declared implementation of ExpressionVisitor::operator()(recursive_wrapper<function_call> const&) below
//
template<>
void ExpressionVisitor::operator()(recursive_wrapper<function_call> const& t) {
   (*this)(t.get());
}

struct brisc
   { constexpr static inline char const* value = R"(brisc)"; };
struct ncrisc
   { constexpr static inline char const* value = R"(ncrisc)"; };
struct crisc
   { constexpr static inline char const* value = R"(crisc)"; };

template<typename T>
using is_kernel_type = std::conditional<
      std::is_same<T, brisc>::value ||
      std::is_same<T, ncrisc>::value ||
      std::is_same<T, crisc>::value, 
      std::true_type,
      std::false_type
>;

template<typename T>
struct kernel_context {
   static_assert(is_kernel_type<T>::type::value, "kernel type is not brisc, ncrisc, or crisc");

   std::map<std::string, expression_data> variable_state;
   std::string host_program_location;

   kernel_context(std::string const host_loc) :
      variable_state(), host_program_location(host_loc) {
   }

   template<typename U>
   expression_data & instance(std::string const& ident) {
      static_assert(
         is_scalar_type<U>::type::value,
         "is not a valid scalar type"
      );

      using map_iterator_type =
          std::map<std::string, expression_data>::iterator;

      std::pair<map_iterator_type, bool> vsitr =
          variable_state.insert(
             std::pair<std::string, expression_data>{ident, expression_data{expression_type{U{ident}}}}
          );

      return vsitr.first->second;
   }

   template<typename U>
   expression_data & instance(std::string const ident, const std::size_t nelems) {
      static_assert(
         is_array_type<U>::type::value, 
         "is not an array type"
      );

      using map_iterator_type =
          std::map<std::string, expression_data>::iterator;

      std::pair<map_iterator_type, bool> vsitr =
          variable_state.insert(
             std::pair<std::string, expression_data>{ident, expression_data{expression_type{array<typename U::value_type>{ident, nelems}}}}
          );

      return vsitr.first->second;
   }

   template<typename U>
   expression_data & instance(std::string const ident, std::initializer_list<std::size_t> dims) {
      static_assert(
         is_matrix_type<U>::type::value,
         "is not a matrix type"
      );

      using map_iterator_type =
          std::map<std::string, expression_data>::iterator;

      std::pair<map_iterator_type, bool> vsitr =
          variable_state.insert(
             std::pair<std::string, expression_data>{ident, expression_data{expression_type{matrix<typename U::value_type>{ident, dims}}}}
          );

      return vsitr.first->second;
   }

   template<typename U>
   expression_data & instance(std::string const ident, std::vector<std::size_t> const& dims) {
      static_assert(
         is_matrix_type<U>::type::value,
         "is not a matrix type"
      );

      using map_iterator_type =
          std::map<std::string, expression_data>::iterator;

      std::pair<map_iterator_type, bool> vsitr =
          variable_state.insert(
             std::pair<std::string, expression_data>{ident, expression_data{expression_type{matrix<typename U::value_type>{ident, dims}}}}
          );

      return vsitr.first->second;
   }


/*
   // metal api -> get_arg_val, get_arg_addr
   //
   template<typename U>
   expression_data & runtime_arg(std::string const ident) {
   }

   // metal api -> get_compile_time_arg_val
   //
   template<typename U>
   expression_data & compiletime_arg(std::string const ident) {
   }
*/

};

using kernel_context_type = variant<
   std::monostate,
   kernel_context<brisc>,
   kernel_context<ncrisc>,
   kernel_context<crisc>
>;

template<typename T>
struct kernel {
   static_assert(is_kernel_type<T>::type::value, "kernel type is not brisc, ncrisc, or crisc");

   using kernel_type = T;

   std::string kernel_impl_src;
   std::string host_program_location;

   kernel() : kernel_impl_src(), host_program_location() {};
   kernel(std::string const& src_loc_str) : kernel_impl_src(), host_program_location(src_loc_str) {};

   template<typename U>
   kernel(kernel_context<U> & kctx, std::initializer_list<statement> statements) :
      kernel_impl_src() {

         static_assert(
            is_kernel_type<T>::type::value &&
            is_kernel_type<U>::type::value,
            "kernel<T>::implement and kernel_context<U> are not kernel types"
         );

         static_assert(
            std::is_same<kernel_type, U>::value,
            "kernel type and kernel_context type are not the same"
         );

         std::uint64_t indent = 0;

         for(auto & stmt : statements) {
            visit(StatementVisitor{++indent, kernel_impl_src}, stmt);
         }

         host_program_location = kctx.host_program_location;
   }
};

using kernel_type = variant<
   std::monostate,
   kernel<brisc>,
   kernel<ncrisc>,
   kernel<crisc>
>;

template<typename T>
std::ostream & operator<<(std::ostream & os, kernel<T> const& kern) {
   return os << kern.kernel_impl_src;
}

} /* namespace dsl */ } // namespace tt

#endif

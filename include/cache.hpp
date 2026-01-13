/*
* Copyright(c)	2024 Christopher Taylor

* SPDX-License-Identifier: BSL-1.0
* Distributed under the Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once
#ifndef __TT_EDSL_CACHE_HPP__
#define __TT_EDSL_CACHE_HPP__

#include <cstdio>
#include <filesystem>
#include <sstream>
#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <string>

#include <db_cxx.h>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "dsl.hpp"

namespace fs = std::filesystem;

namespace tt { namespace dsl {

struct kernel_cache {

   // berkeley database backed kernel cache
   //
   // keys are hashes of the kernel source code
   //
   // values are paths to the file stored in $HOME/.tt_edsl
   //

   const static inline fs::path home = "./.tt_edsl";

   using max_path = std::integral_constant<std::size_t, 260UL>;

   Db dbobj;

   kernel_cache() : dbobj(nullptr, 0) {
      if(!fs::exists(home)) {
         setup();
      }
   }

   // hsearch hashing function from musl MIT license
   //
   // libc/musl/src/search/hsearch.c
   //
   // static size_t keyhash(char *k)
   //
   static std::size_t hash(std::string & str) {
      unsigned char *p = reinterpret_cast<unsigned char *>(const_cast<char*>(str.c_str()));
      std::size_t h = 0;
      while (*p) h = 31*h + *p++;
      return h;
   }

   static void setup() {
      if(create_directory(kernel_cache::home)) {
         std::cerr << fmt::format("tt-edsl error: {} failed to setup", kernel_cache::home.string()) << std::endl;
      }

      fs::path cache_path = home / fs::path{"cache.db"};

      const std::uint32_t oflags = DB_CREATE;

      Db db(nullptr, 0);
      try {
         db.open(nullptr, cache_path.string().c_str(), nullptr, DB_BTREE, DB_CREATE, 0);
         db.close(0);
      }
      catch(DbException &e) {
         std::cerr << fmt::format("tt-edsl error: {} failed to create database", cache_path.string()) << std::endl;
      }
      catch(std::exception &e) {
         std::cerr << fmt::format("tt-edsl error: {} failed to create database", cache_path.string()) << std::endl;
      } 
   }

   void open() {
      fs::path cache_path = home / fs::path{"cache.db"};
      dbobj.open(nullptr, cache_path.string().c_str(), nullptr, DB_BTREE, DB_THREAD, 0);
      dbobj.set_error_stream(&std::cerr);
   }

   void close() {
      dbobj.close(0);
   }

   static std::string generateRandomString(const std::size_t length)
   {
      // Define the list of possible characters
      const std::string CHARACTERS =
          "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

       // Create a random number generator
       std::random_device rd;
       std::mt19937 generator(rd());

       // Create a distribution to uniformly select from all
       // characters
       std::uniform_int_distribution<> distribution(
           0, CHARACTERS.size() - 1);

       // Generate the random string
       std::string random_string;
       for (int i = 0; i < length; ++i) {
           random_string
               += CHARACTERS[distribution(generator)];
       }

       return random_string;
   }

   template<typename T>
   void compute_key(kernel<T> const& kern, std::string & db_key) {
      static_assert(is_kernel_type<T>::type::value, "kernel<T> where T is not brisc, ncrisc, or crisc");

      if(kern.host_program_location.size() < 1) {
         std::cerr << fmt::format("Put operation failed, kernel has no host_program_location defined") << std::endl;
         return;
      }

      std::string const kernel_tensix_core{T::value};

      fs::path tmpfnpth = home / fs::path{fmt::format("ttedsl_kernel_{}_{}", kernel_tensix_core, generateRandomString(max_path::value-14UL))};
      db_key = tmpfnpth.string();
   }

   template<typename T>
   void compute_hash(kernel<T> const& kern, std::string & hash_value) {
      hash_value = std::to_string(hash(kern.host_program));
   }

   void compute_hash(std::string & kern, std::string & hash_value) {
      hash_value = std::to_string(hash(kern));
   }

   const static inline std::map<int, std::string> error_msgs = {
      std::make_pair<int, std::string>(DB_KEYEXIST, "Put failed because key already exists"),
      std::make_pair<int, std::string>(DB_NOTFOUND, "Get operation failed, kernel not found")
   };

   bool handle_rc(const int rc) {
      std::map<int, std::string>::const_iterator end_itr = error_msgs.end();
      std::map<int, std::string>::const_iterator value_itr = error_msgs.find(rc);
      if(value_itr != end_itr) {
          dbobj.err(rc, value_itr->second.c_str());
          return true;
      }

      return false;
   }

   template<typename T>
   bool contains(kernel<T> const& kern) {
      std::string db_key;
      compute_key(kern, db_key);

      std::string kern_hash;
      compute_hash(kern, kern_hash);

      Dbt dbkey((void*)kern_hash.c_str(), kern_hash.size());
      const int ret = dbobj.exists(nullptr, &dbkey, 0);
      return handle_rc(ret);
   }

   template<typename T>
   bool put(kernel<T> const& kern) {

      std::string kern_hash;
      compute_hash(kern, kern_hash);

      Dbt dbkey((void*)kern_hash.c_str(), kern_hash.size());

      std::string db_key;
      compute_key(kern, db_key);

      Dbt dbdata(reinterpret_cast<void*>(const_cast<char*>(db_key.c_str())), db_key.size()+1); 

      const int ret = dbobj.put(nullptr, &dbkey, &dbdata, DB_NOOVERWRITE);
      { 
         std::ofstream ofs(db_key);
         ofs << kern << std::endl << std::flush;
         ofs.close();
      }

      return handle_rc(ret);
   }

   template<typename T>
   bool get(kernel<T> const& kern, fs::path & kern_path) {
      if(kern.host_program_location.size() < 1) {
         std::cerr << fmt::format("Put operation failed, kernel has no host_program_location defined; use the 'host_location()' macro where the kernel_context is defined") << std::endl;
         return -1;
      }

      std::string kern_hash;
      compute_hash(kern, kern_hash);

      Dbt dbkey((void*)kern_hash.c_str(), kern_hash.size());

      char tmpfn_buf[max_path::value];
      std::memset(tmpfn_buf, 0, max_path::value);

      Dbt dbdata(tmpfn_buf, max_path::value); 

      const int ret = dbobj.get(nullptr, &dbkey, &dbdata, 0);

      kern_path = std::string{tmpfn_buf};
      return handle_rc(ret);
   }

   bool purge() {

      Dbc * dbcur;
      dbobj.cursor(nullptr, &dbcur, DB_CURSOR_BULK);

      char tmp_buf[max_path::value];
      std::memset(tmp_buf, 0, max_path::value);

      Dbt dbkey(tmp_buf, max_path::value);

      char tmpfn_buf[max_path::value];
      std::memset(tmpfn_buf, 0, max_path::value);

      Dbt dbdata(tmpfn_buf, max_path::value);

      memset(&dbkey, 0, sizeof(dbkey));
      memset(&dbdata, 0, sizeof(dbdata));

      for(int ret = dbcur->get(&dbkey, &dbdata, DB_NEXT); ret == 0; ret = dbcur->get(&dbkey, &dbdata, DB_NEXT)) {

         if(handle_rc(ret)) { break; }

         fs::path pth{std::string{tmpfn_buf}};

         if(!fs::exists(pth)) { continue; }

         std::string kernelstr;

         {
            std::ifstream ifs(pth.string());
            ifs >> kernelstr;
            ifs.close();
         }

         std::string kern_hash;
         compute_hash(kernelstr, kern_hash);

         if(kern_hash.compare(std::string{tmp_buf}) != 0) {
            dbcur->del(0);
         }
      }

      return handle_rc(dbcur->close());
   }

};

} /* namespace dsl */ } // namespace tt

#endif


.. _program_listing_file_debug.hpp:

Program Listing for File debug.hpp
==================================

|exhale_lsh| :ref:`Return to documentation for file <file_debug.hpp>` (``debug.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "operations.hpp"
   #include "range.hpp"
   // Enabling LOCAL enables debug features
   #ifdef LOCAL
   #define dbg(x) (++debug_tools::depth, debug(x, #x##s))
   #else
   #define NDEBUG
   #define dbg(x) (x)
   #endif
   
   namespace debug_tools {
   tm() auto type_name([[maybe_unused]] T const &v) {
       string s = __PRETTY_FUNCTION__, tar = "T = ";
       auto st = s.find(tar) + tar.size();
       return s.substr(st, s.find("]", st) - st);
   }
   auto replace(string s, const string &a, const string &b) {
       // TODO This is multipass. Should this be singlepass?
       ll loc;
       while ((loc = s.find(a)) != string::npos) {
           s = s.substr(0, loc) + b + s.substr(loc + a.size());
       }
       return s;
   }
   template <typename T> auto simple_tp([[maybe_unused]] const T &v) {
       auto s = type_name(v);
       for (const auto &p : lets) {
           s = replace(s, p.first, p.second);
       }
       return s;
   }
   ll depth = -1;
   template <typename T>
   auto debug(const T &x, const string &name,
          source_location const &loc = source_location::current()) {
       if (debug_mode) {
           fo(i, depth) { cerr << "\t"; }
           cerr << loc.function_name() << ":" << loc.line() << " " << name
                << " = " << x << endl;
       }
       --depth;
       return x;
   }
   } // namespace debug_tools
   using namespace debug_tools;

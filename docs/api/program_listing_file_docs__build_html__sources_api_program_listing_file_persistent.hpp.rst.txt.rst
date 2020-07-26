
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_persistent.hpp.rst.txt:

Program Listing for File program_listing_file_persistent.hpp.rst.txt
====================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_persistent.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_persistent.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_persistent.hpp:
   
   Program Listing for File persistent.hpp
   =======================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_persistent.hpp>` (``persistent.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      #include "core.hpp"
      namespace persistent {
      struct first_cmp {
          template <typename T> bool operator()(T a, T b) const {
              return a.first < b.first;
          }
      };
      tm() struct pers {
          static inline auto tim = 0LL; 
          using event = pair<ll, T>;
          set<event, first_cmp> s;
          auto operator=(const T &v) {
              event e{tim, v};
              s.erase(e);
              s.insert(e);
          }
          operator auto() const { return (*--s.upper_bound({tim, T{}})).second; }
      };
      template <typename Stream, typename T>
      auto &operator<<(Stream &os, pers<T> const &p) {
          return os << static_cast<T>(p);
      }
      } // namespace persistent
      using namespace persistent;

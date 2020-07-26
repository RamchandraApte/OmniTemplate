
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_combinatorics.hpp.rst.txt:

Program Listing for File program_listing_file_combinatorics.hpp.rst.txt
=======================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_combinatorics.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_combinatorics.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_combinatorics.hpp:
   
   Program Listing for File combinatorics.hpp
   ==========================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_combinatorics.hpp>` (``combinatorics.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      #include "core.hpp"
      namespace combinatorics {
      template <typename T> T perm(const T a, const T b) {
          return accumulate(int_it<T>{a + 1 - b}, int_it<T>{a + 1}, T{1},
                    multiplies<>{});
      }
      void test_perm() {
          assert(perm(4, 2) == 4 * 3);
          assert(perm(4, 4) == 4 * 3 * 2 * 1);
          assert(perm(4, 0) == 1);
          assert(perm(0, 0) == 1);
          assert(perm(1, 0) == 1);
          assert(perm(1, 1) == 1);
      }
      template <typename T> T fact(const T n) {
          return perm(n, n);
      }
      void test_fact() {
          assert(fact(4) == 4 * 3 * 2 * 1);
          assert(fact(0) == 1);
          assert(fact(1) == 1);
          assert(fact(8) == 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1);
      }
      template <typename T> T choose(const T a, const T b) {
          return perm(a, b) / fact(b);
      }
      void test_choose() {
          assert(choose(5, 2) == 10);
          assert(choose(5, 3) == 10);
          assert(choose(5, 0) == 1);
          assert(choose(5, 5) == 1);
          assert(choose(0, 0) == 1);
          assert(choose(1, 0) == 1);
          assert(choose(1, 1) == 1);
          assert(choose(6, 3) == 20);
      }
      void test_combinatorics() {
          test_perm();
          test_fact();
          test_choose();
      }
      } // namespace combinatorics
      using namespace combinatorics;

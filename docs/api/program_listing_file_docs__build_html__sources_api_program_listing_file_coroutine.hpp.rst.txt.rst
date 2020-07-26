
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_coroutine.hpp.rst.txt:

Program Listing for File program_listing_file_coroutine.hpp.rst.txt
===================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_coroutine.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_coroutine.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_coroutine.hpp:
   
   Program Listing for File coroutine.hpp
   ======================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_coroutine.hpp>` (``coroutine.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      #include "core.hpp"
      #define CO_SWITCH
      #ifdef CO_SWITCH
      #define cobegin                                                                \
          static lli pos = 0;                                                    \
          switch (pos) {                                                         \
          case 0:
      #define coend                                                                  \
          default:                                                               \
              throw out_of_range("Coroutine reached end.");                  \
              }
      #define coreturn(x)                                                            \
          pos = __LINE__;                                                        \
          return x;                                                              \
          case __LINE__:;
      #endif
      #ifdef CO_JMP
      #define cobegin                                                                \
          static bool first = true;                                              \
          static jmp_buf env;                                                    \
          if (!first) {                                                          \
              longjmp(env, true);                                            \
          }                                                                      \
          first = false;
      #define coreturn                                                               \
          if (!setjmp(env))                                                      \
          return
      #define coend throw out_of_range("Coroutine reached end.");
      #endif
      ll coro(ll a) {
          cobegin coreturn(404);
          for (static ll i = 0; i < a; i++) {
              coreturn(i * i);
          }
          coreturn(505);
          coend
      }
      void test_coroutine() {
          const ll a = 4;
          vl v;
          try {
              while (true) {
                  v.push_back(coro(a));
              }
          } catch (out_of_range &) {
          }
          assert((v == vl{404, 0 * 0, 1 * 1, 2 * 2, 3 * 3, 505}));
      }

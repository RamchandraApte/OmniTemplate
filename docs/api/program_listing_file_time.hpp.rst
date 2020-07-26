
.. _program_listing_file_time.hpp:

Program Listing for File time.hpp
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_time.hpp>` (``time.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "core.hpp"
   namespace time_tools {
   struct timer {
       decltype(clock_::now()) t1;
       timer() : t1(clock_::now()) {}
       ~timer() {
           cerr << "Time duration: "
                << duration<ld>(clock_::now() - t1).count() << " s"
                << endl;
       }
   };
   template <typename Func> void bench(Func a) {
       timer _t;
       decltype(a) ans = 0;
       for (decltype(a) i = 0; i < a; ++i) {
           for (decltype(a) j = 1; j < a; ++j) {
               ans += ((-i) % (j));
           }
       }
       // To avoid the benchmark from being optimized out. I don't know if this actually works.
       const auto volatile _unused = ans;
   }
   } // namespace time_tools
   using namespace time_tools;

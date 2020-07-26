
.. _program_listing_file_main.hpp:

Program Listing for File main.hpp
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_main.hpp>` (``main.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #pragma once
   #include "core.hpp"
   #include "time.hpp"
   void main2();
   #if 0
   string s = __FILE__;
   ifstream input{s.substr(0,s.size()-string{"cpp"}.size())+"in"};
   auto& in = input?input:cin;
   #else
   auto &in = cin;
   #endif
   int main(int argc, char *argv[]) {
   #ifdef LOCAL
       debug_mode = true;
   #endif
       fo(i, argc) {
           if (argv[i] == "-q"s) {
               debug_mode = false;
           }
       }
       ios::sync_with_stdio(false);
       if (!debug_mode) {
           cerr.rdbuf(nullptr);
       }
       for (ios &os :
            initializer_list<reference_wrapper<ios>>{in, cout, cerr, clog}) {
           fixed(os);
           if (os.rdbuf()) {
               os.exceptions(ios::failbit | ios::badbit | ios::eofbit);
           }
           os.precision(false ? numeric_limits<ld>::max_digits10 : 5);
       }
       cout.precision(numeric_limits<ld>::max_digits10);
       timer _t;
       ll t = 1;
       if (multitest) {
           cin >> t;
       }
       fo(i, t) { main2(); }
   }

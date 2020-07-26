
.. _program_listing_file_test.cpp:

Program Listing for File test.cpp
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_test.cpp>` (``test.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "template.hpp"
   bool multitest{};
   void test_all() {
       test_utility();
       test_graph_theory();
       test_dsu();
       test_sat2();
       test_modulo();
       test_number_theory();
       test_queue();
       test_splay_tree();
       test_geometry();
       test_combinatorics();
       test_string();
       test_coroutine();
       test_linear_algebra();
       test_permutation();
       test_bit();
       test_segment_tree();
       test_polynomial();
       test_sparse_table();
       test_hld();
       test_link_cut_tree();
       cout << "\e[0;32mAccepted\e[0m" << endl;
   }
   void main2() { test_all(); }

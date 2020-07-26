
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_misc_test_rand.cpp.rst.txt:

Program Listing for File program_listing_file_misc_test_rand.cpp.rst.txt
========================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_misc_test_rand.cpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_misc_test_rand.cpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_misc_test_rand.cpp:
   
   Program Listing for File test_rand.cpp
   ======================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_misc_test_rand.cpp>` (``misc/test_rand.cpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #include "main.hpp"
      bool multitest = false;
      void main2(){
           cout<<clock_::now()
            .time_since_epoch()
            .count()<<endl;
          cout<<reng()<<endl;
          random_device_patch dev{};
          const auto x = dev();
          const auto y = dev();
          cout<<x<<" "<<y<<endl;
      }

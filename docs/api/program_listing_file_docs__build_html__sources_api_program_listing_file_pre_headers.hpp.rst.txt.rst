
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_pre_headers.hpp.rst.txt:

Program Listing for File program_listing_file_pre_headers.hpp.rst.txt
=====================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_pre_headers.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_pre_headers.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_pre_headers.hpp:
   
   Program Listing for File pre_headers.hpp
   ========================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_pre_headers.hpp>` (``pre_headers.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      
      #ifndef PRE
      //#if defined(__GNUC__) && !defined(__clang__)
      #if 0
      #define REALGCC
      #endif
      #ifdef REALGCC
      #include <bits/extc++.h>
      #else
      #include <bits/stdc++.h>
      #endif
      #include <experimental/iterator>
      #include <experimental/source_location>
      #endif

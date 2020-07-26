
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_d.cpp.rst.txt:

Program Listing for File program_listing_file_d.cpp.rst.txt
===========================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_d.cpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_d.cpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_d.cpp:
   
   Program Listing for File d.cpp
   ==============================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_d.cpp>` (``d.cpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #include "graph_theory.hpp"
      #include "main.hpp"
      bool multitest{};
      void main2() {
          I(n);I(m);
          vc<vl> g(n);
          vl u(m), v(m), col(m, 1);
          fo(i,m){
              cin>>u[i]>>v[i];
              --u[i];--v[i];
              g[u[i]].pb(v[i]);
          }
          dfs d{g};
          d();
          vl pos(n);
          fo(i,n){
              pos[d.q[i]] = i;
          }
          fo(i,m){
              col[i] = 1+(pos[u[i]] > pos[v[i]]);
          }
          cout<<*max_element(al(col))<<endl;;
          for(auto x:col){cout<<x<<" ";}
          cout<<endl;
      }

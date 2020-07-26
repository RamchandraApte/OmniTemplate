
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_2sat.hpp.rst.txt:

Program Listing for File program_listing_file_2sat.hpp.rst.txt
==============================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_2sat.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_2sat.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_2sat.hpp:
   
   Program Listing for File 2sat.hpp
   =================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_2sat.hpp>` (``2sat.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      #include "core.hpp"
      #include "graph_theory.hpp"
      namespace sat2 {
      optional<vector<char>> sat2(const vector<array<ll, 2>> &cnf, const ll n) {
          vector<vl> graph(2 * n + 1);
          for (const auto &clause : cnf) {
              // Construct two implications that represent the clause
              graph[n - clause[0]].push_back(n + clause[1]);
              graph[n - clause[1]].push_back(n + clause[0]);
          }
          dfs topo{graph};
          topo();
          vl idx(size(graph));
          fo(i, size(topo.q)) { idx[topo.q[i]] = i; }
          vector<char> vals(n + 1, -1);
          auto comp = scc(graph);
          fo(i, 1, n + 1) {
              auto x = idx[comp[n + i]], nx = idx[comp[n - i]];
              if (nx == x) {
                  return nullopt;
              }
              vals[i] = nx < x;
          }
          return vals;
      }
      void test_sat2() {
          const auto ret1 = sat2({{2, 1}, {-2, 3}}, 3).value();
          assert(ret1[1] || ret1[2]);
          assert(!ret1[2] || ret1[3]);
          const auto ret2 = sat2({{2, 1}, {3, 2}, {-2, -1}}, 3).value();
          assert(ret2[1] || ret2[2]);
          assert(ret2[2] || ret2[3]);
          assert(!ret2[2] || !ret2[1]);
          const auto ret3 = sat2({{1, 1}, {-1, -1}}, 1);
          assert(!ret3);
          const auto ret4 = sat2({{1, 2}, {3, 2}, {-1, -1}, {-2, -2}}, 3);
          assert(!ret4);
      }
      } // namespace sat2
      using namespace sat2;

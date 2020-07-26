
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_hld.hpp.rst.txt:

Program Listing for File program_listing_file_hld.hpp.rst.txt
=============================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_hld.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_hld.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_hld.hpp:
   
   Program Listing for File hld.hpp
   ================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_hld.hpp>` (``hld.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      #include "core.hpp"
      #include "graph_theory.hpp"
      #include "sparse_table.hpp"
      template<typename T, typename Monoid, typename QueryDS>
      class HLD {
      public:
          explicit HLD(const vector<vector<ll>>& graph, const vector<T>& data): heavy(graph.size(), -1), head(graph.size(), -1), pos(graph.size(), -1), d{graph} {
              d.distance[0] = 0;
              d(0);
              const auto sz = get_size(d);
              // Construct the heavy array
              for(auto idx: rev(d.q)){
                  if(d.parent[idx] != -1 && 2*sz[d.parent[idx]] >= sz[d.parent[idx]]){
                      heavy[d.parent[idx]] = idx;
                  }
              }
              // Walk down each heavy path and set head and pos
              ll glob_pos = 0;
              for(const auto idx: d.q){
                  if(head[idx] != -1){continue;}          
                  auto x = idx;
                  while(x != -1){
                      head[x] = idx;
                      pos[x] = glob_pos;
                      ++glob_pos;
                      x = heavy[x];
                  }
              }
              assert(glob_pos == graph.size());
              vector<T> perm_data(graph.size()); 
              fo(idx, graph.size()){
                  perm_data[pos[idx]] = data[idx];
              }
              ds = QueryDS{perm_data};
          }
          template<typename Func>
          void func_path(ll u, ll v, const Func& func){
              // We're assuming the operation is commutative
              // FIXME find the LCA and use that to do it for non-commutative operators
              while(true){
                  // Don't swap u and v if there's a tie
                  swap2(u, v, [&](const auto x){return d.distance[head[x]];});
                  if(head[u] == head[v]){break;}
                  func(pos[head[v]], pos[v]+1);
                  v = d.parent[head[v]];
              }
              // Deal with the last heavy path
              func(pos[v], pos[u]+1);
          }
          T query(ll u, ll v){
              T ret{identity(Monoid{}, T{})};
              func_path(u, v, [&](ll u, ll v){ret = Monoid{}(ret, ds.query(u, v));});
              return ret;
          }
          void update(ll u, ll v, const T& val){
              func_path(u, v, [&](ll u, ll v){ds.update(u, v, val);});
          }
          
      private:
          vector<ll> heavy; 
          vector<ll> head; 
          vector<ll> pos; 
          dfs d; // DFS of tree
          // TODO why doesn't vector<T>{1} work?
          QueryDS ds{vector<T>{-100, -100}}; // DS used for querying
      };
      void test_hld(){
          vector<vector<ll>> tree(6);
          add_edge(tree, 0, 1);
          add_edge(tree, 1, 5);
          add_edge(tree, 0, 2);
          add_edge(tree, 2, 3);
          add_edge(tree, 2, 4);
          vector<ll> data{5,3,6,1,2,7};
          HLD<ll, plus<>, DisjointSparseTable<ll, plus<>>> hld{tree, data};
          // 5 -> 1 -> 0 -> 2 -> 4
          const auto sum_of_idxs = [&](const vector<ll>& idxs){
              ll sum = 0;
              for(const auto u: idxs){
                  sum += data[u];
              }
              return sum;
          };
          assert(( hld.query(5,4) == sum_of_idxs({5, 1, 0, 2, 4}) ));
          assert(( hld.query(1,0) == sum_of_idxs({1, 0}) ));
          assert(( hld.query(0,1) == sum_of_idxs({0, 1}) ));
          assert(( hld.query(2, 1) == sum_of_idxs({2, 0, 1}) ));
          assert(( hld.query(4, 3) == sum_of_idxs({4, 2, 3}) ));
          assert(( hld.query(4,4) == sum_of_idxs({4}) ));
      }

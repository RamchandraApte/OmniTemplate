
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_sparse_table.hpp.rst.txt:

Program Listing for File program_listing_file_sparse_table.hpp.rst.txt
======================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_sparse_table.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_sparse_table.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_sparse_table.hpp:
   
   Program Listing for File sparse_table.hpp
   =========================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_sparse_table.hpp>` (``sparse_table.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      #include "core.hpp"
      // TODO return identity when l = r
      template <typename T, typename Semilattice> class SparseTable {
            public:
          explicit SparseTable(const vector<T> &arr) : meet(log_ceil(arr.size(), 2), vector<ll>(arr.size())) {
              meet[0] = arr;
              fo(pw, 1, meet.size()) {
                  fo(i, arr.size()) {
                      const auto half = 1LL << (pw - 1);
                      meet[pw][i] = Semilattice{}(meet[pw - 1][i], meet[pw - 1][min(i + half, ssize(arr) - 1)]);
                  }
              }
          }
          T query(ll l, ll r) const {
              const auto len = r - l;
              // TODO put this in a function
              const auto floor_log2 = (sizeof(ll) * CHAR_BIT) - 1 - __builtin_clzll(len);
              return Semilattice{}(meet[floor_log2][l], meet[floor_log2][r - (1LL << floor_log2)]);
          }
      
            private:
          vc<vl> meet; 
      };
      template <typename T, typename Monoid> class DisjointSparseTable {
            public:
          explicit DisjointSparseTable(vector<T> arr) : sum(log_ceil(arr.size(), 2), vector<T>(power_ceil(arr.size(), 2))) {
              arr.resize(sum[0].size(), identity(Monoid{}, T{}));
              fo(level, sum.size()) {
                  fo(block, 1LL << level) {
                      // The first half of the block contains suffix sums, the second half contains prefix sums
                      const auto start = block << (sum.size() - level);
                      const auto end = (block + 1) << (sum.size() - level);
                      const auto middle = (end + start) / 2;
                      auto val = arr[middle];
                      sum[level][middle] = val;
                      fo(x, middle + 1, end) {
                          val = Monoid{}(val, arr[x]);
                          sum[level][x] = val;
                      }
                      val = arr[middle - 1];
                      sum[level][middle - 1] = val;
                      fr(x, start, middle - 1) {
                          val = Monoid{}(val, arr[x]);
                          sum[level][x] = val;
                      }
                  }
              }
          }
          T query(ll l, ll r) const {
              assert(l < r);
              // Convert half open interval to closed interval
              --r;
              if(l == r){
                  return sum.back()[l];
              }
              // Position of the leftmost different bit from the right
              const auto pos_diff = (sizeof(ll) * CHAR_BIT) - 1 - __builtin_clzll(l ^ r);
              const auto level = sum.size() - 1 - pos_diff;
              return Monoid{}(sum[level][l], sum[level][r]);
          }
      
            private:
          vector<vector<T>> sum;
      };
      template <template <typename...> typename Table, typename T, typename Monoid> void test_sparse_table_impl() {
          vector<T> data{6, 2, 4, 1, 7, 3, 4, 2, 7, 2, 4, 1, 6};
          Table<T, Monoid> sp{data};
          fo(start, data.size()) {
              fo(end, start + 1, data.size()) { assert(sp.query(start, end) == accumulate(begin(data) + start, begin(data) + end, identity(Monoid{}, T{}), Monoid{})); }
          }
      }
      void test_sparse_table() {
          with _m{ll(1e9 + 7), modulo::modulus};
          test_sparse_table_impl<SparseTable, ll, Min>();
          test_sparse_table_impl<DisjointSparseTable, ll, Min>();
          test_sparse_table_impl<DisjointSparseTable, ll, plus<>>();
          test_sparse_table_impl<DisjointSparseTable, modulo, multiplies<>>();
      }

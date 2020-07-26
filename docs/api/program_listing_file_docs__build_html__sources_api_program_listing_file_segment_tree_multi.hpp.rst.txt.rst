
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_segment_tree_multi.hpp.rst.txt:

Program Listing for File program_listing_file_segment_tree_multi.hpp.rst.txt
============================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_segment_tree_multi.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_segment_tree_multi.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_segment_tree_multi.hpp:
   
   Program Listing for File segment_tree_multi.hpp
   ===============================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_segment_tree_multi.hpp>` (``segment_tree_multi.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      #include "core.hpp"
      // TODO non commutative monoids, specify the ordering
      ll base_ceil(const ll x, const ll base) {
          ll pw = 1;
          for (; pw < x; pw *= base)
              ;
          return pw;
      }
      // TODO multidimensional
      using Bound = array<ll, 2>;
      template <typename T, typename Query, typename Update, bool has_lazy = true, bool has_ptr = false, bool has_pers = false, ll base = 2> class SegmentTree {
            public:
          SegmentTree(const ll size_arg) : size_{size_arg}, ceil_size{base_ceil(size_arg, base)}, nodes(!has_ptr ? base * ceil_size : 0) {
              if constexpr (!has_ptr) {
                  root.idx = 1;
              } else {
                  root = new NodeExp{};
              }
          }
          static_assert(!has_pers || has_ptr, "Pointers required for persistency");
          static_assert(base > 1, "Base must be at least 1");
          struct LazyPart {
              T lazy{identity(Update{}, T{})};
          };
          struct NodeCore : public conditional_t<has_lazy, LazyPart, Empty> {
              T qsum{identity(Query{}, T{})};
          };
          struct NodeExp : public NodeCore {
              array<NodeExp *, base> child{};
          };
          struct NodeImp {
              // workaround attempt
              ll idx;
          };
          using Node = conditional_t<has_ptr, NodeExp *, NodeImp>;
          auto &get_core(NodeExp *const &obj) { return *obj; }
          auto &get_core(const NodeImp idx) { return nodes[idx.idx]; }
          auto &get_child(NodeExp *const &obj, const ll i) { return obj->child[i]; }
          NodeImp get_child(const NodeImp idx, const ll i) { return {base * idx.idx + i}; }
          void down(const Node idx, const ll node_l, const ll node_r) {
              const bool leaf = node_r - node_l == 1;
              if constexpr (has_ptr) {
                  if (!leaf) {
                      for (auto &ptr : idx->child) {
                          if (!ptr) {
                              ptr = new NodeExp{};
                          }
                      }
                  }
              }
              if constexpr (has_lazy) {
                  get_core(idx).qsum = Update{}(get_core(idx).qsum, get_core(idx).lazy);
                  if (!leaf) {
                      fo(i, base) { get_core(get_child(idx, i)).lazy += get_core(idx).lazy; }
                  }
                  get_core(idx).lazy = identity(Update{}, get_core(idx).lazy);
              }
          }
          template <typename... Bounds> T query_impl(const Node idx, const ll node_l, const ll node_r, const Bound bound, const Bounds... bounds) {
              const auto [l, r] = bound;
              if (node_r <= l || r <= node_l) {
                  return identity(Query{}, T{});
              }
              down(idx, node_l, node_r);
              if (l <= node_l && node_r <= r) {
                  return get_core(idx).qsum;
              }
              auto ret = identity(Query{}, T{});
              const auto mid = [&](ll i) {
                  return (node_l * (base - i) + node_r * i) / base;
              };
              fo(inc, base) { ret = Query{}(ret, query_impl(get_child(idx, inc), mid(inc), mid(inc + 1), Bound{l, r}, bounds...)); }
              return ret;
          }
          template <typename... Bounds> T query_pers(const Node custom_root, const Bounds... bounds) {
              /*if (!(0 <= l && l <= r && r <= size_)) {
                  throw out_of_range{"Segment tree query out of bounds"};
              }*/
              return query_impl(custom_root, 0, ceil_size, bounds...);
          }
          template <typename... Bounds> T query(const Bounds... bounds) { return query_pers(root, bounds...); }
          template <typename... Bounds> Node update_impl(Node idx, const ll node_l, const ll node_r, const T val, const Bound bound, const Bounds... bounds) {
              const auto [l, r] = bound;
              if (node_r <= l || r <= node_l) {
                  return idx;
              }
              down(idx, node_l, node_r);
              if constexpr (has_pers) {
                  idx = new NodeExp{*idx};
              }
              if (l <= node_l && node_r <= r) {
                  if constexpr (has_lazy) {
                      get_core(idx).lazy = Update{}(get_core(idx).lazy, val);
                      down(idx, node_l, node_r);
                  } else {
                      get_core(idx).qsum = Update{}(get_core(idx).qsum, val);
                  }
                  return idx;
              }
              const auto mid = [&](ll i) {
                  const auto df = (node_r-node_l)/base;
                  return node_l + df*i;
              };
              if constexpr (has_lazy){get_core(idx).qsum = identity(Query{}, T{});}
              fo(inc, base) {
                  auto get_update = [&, l = l, r = r]() { return update_impl(get_child(idx, inc), mid(inc), mid(inc + 1), val, Bound{l, r}, bounds...); };
                  if constexpr (has_pers) {
                      get_child(idx, inc) = get_update();
                  } else {
                      get_update();
                  }
                  // This shouldn't work, but it does? 😕
                  //get_core(idx).qsum = Query{}(get_core(idx).qsum, query_impl(get_child(idx, inc), mid(inc), mid(inc + 1), Bound{l, r}, bounds...));
                  
                  if constexpr (has_lazy){get_core(idx).qsum = Query{}(get_core(idx).qsum, get_core(get_child(idx, inc)).qsum);}
              }
              return idx;
          }
          template <typename... Bounds> Node update(const T val, const Bounds... bounds) {
              /*if constexpr (!has_lazy) {
                  assert(l + 1 == r);
              }*/
              return root = update_impl(root, 0, ceil_size, val, bounds...);
          }
      
            private:
          ll size_;
          ll ceil_size;
          Node root;
          vector<NodeCore> nodes;
      };
      void test_segment_tree() {
          constexpr bool has_lazy = true;
          SegmentTree<ll, Max, plus<>, has_lazy> seg{1000};
          assert(seg.query(Bound{1U, 3U}) == -inf);
          assert(seg.query(Bound{7U, 9U}) == -inf);
          fo(i, 0, 10) { seg.update(inf, Bound{ll(i), ll(i + 1)}); }
          /*auto old =seg.update(0, Bound{0, 1});*/
          assert(seg.query(Bound{0U, 10U}) == 0);
          assert(seg.query(Bound{3U, 4U}) == 0);
          seg.update(2, Bound{2U, 3U});
          /*auto old2 =*/seg.update(3, Bound{4U, 5U});
          // assert(seg.query(0, 10, old) == 0);
          assert(seg.query(Bound{0U, 10U}) == 3);
          assert(seg.query(Bound{3U, 4U}) == 0);
          assert(seg.query(Bound{2U, 4U}) == 2);
          // assert(seg.query(2, 4, old2) == 2);
          seg.update(-2, Bound{2U, 3U});
          seg.update(-3, Bound{4U, 5U});
          assert(seg.query(Bound{2U, 4U}) == 0);
          assert(seg.query(Bound{0U, 10U}) == 0);
          // assert(seg.query(0, 10, old) == 0);
          // assert(seg.query(2, 4, old2) == 2);
          fo(i, 0, 10) { seg.update(-inf, Bound{ll(i), ll(i + 1)}); }
          if constexpr (has_lazy) {
              seg.update(inf, Bound{0U, 10U});
              /*auto old_lazy =*/ seg.update(10, Bound{3U, 4U});
              assert(seg.query(Bound{0, 10}) == 10);
              //assert(seg.query(0, 10, old_lazy) == 10);
              seg.update(20, Bound{2U, 4U});
              assert(seg.query(Bound{3U, 4U}) == 30);
              assert(seg.query(Bound{2U, 4U}) == 30);
              assert(seg.query(Bound{2U, 3U}) == 20);
              assert(seg.query(Bound{1U, 10U}) == 30);
              seg.update(10, Bound{0U, 2U});
              assert(seg.query(Bound{1U, 10U}) == 30);
              /*assert(seg.query(0, 10, old) == 0);
              assert(seg.query(2, 4, old2) == 2);
              assert(seg.query(0, 10, old_lazy) == 10);*/
          }
      }

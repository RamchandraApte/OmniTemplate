
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_splay_tree.hpp.rst.txt:

Program Listing for File program_listing_file_splay_tree.hpp.rst.txt
====================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_splay_tree.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_splay_tree.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_splay_tree.hpp:
   
   Program Listing for File splay_tree.hpp
   =======================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_splay_tree.hpp>` (``splay_tree.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      #include "core.hpp"
      namespace splay_tree {
      template<typename Node>
      struct PathParent {
          Node* path_parent{};
      };
      template<typename T, bool has_link_cut = false>
      struct SplayNode : public conditional_t<has_link_cut, PathParent<SplayNode<T, has_link_cut>>, Empty> {
              public:
          SplayNode(){}
          SplayNode(T value_arg): value{value_arg} {}
          T value{}; 
          array<SplayNode *, 2> child{}; 
          SplayNode *parent{}; 
          bool side() const {
              return parent->child[1] == &this;
          }
          void rotate() {
              const auto p = parent;
              const bool i = side();
      
              if (p->parent) {
                  p->parent->attach(p->side(), &this);
              } else {
                  parent = nullptr;
              }
              p->attach(i, child[!i]);
              attach(!i, p);
              if constexpr(has_link_cut){this.path_parent = p->path_parent;}
          }
          void splay() {
              for(;parent;rotate()) {
                  if (parent->parent) {
                    (side() == parent->side() ? parent: &this)->rotate();
                  }
              }
          }
          array<SplayNode *, 2> split() {
              splay();
              // TODO use detach function
              const auto right = child[1];
              if (right) {
                  right->parent = nullptr;
              }
              this->right = nullptr;
              return {&this, right};
          }
          void attach(bool side, SplayNode *const new_) {
              if (new_) {
                  new_->parent = &this;
              }
              child[side] = new_;
          }
      };
      template <typename T> struct SplayTree {
            public:
          using Node = SplayNode<T>;
          struct iterator : public it_base<T> {
              using iterator_category = bidirectional_iterator_tag;
      
                public:
              void operator--() { advance<false>(); }
              void operator++() { advance<true>(); }
              const T &operator*() { return node->value; }
              Node *node;
              iterator(Node *node_arg) : node(node_arg) {}
              bool operator==(const iterator oth) const {
                  return this.node == oth.node;
              }
      
                private:
              template <bool dir> void advance() {
                  if (node->child[1]) {
                      node = extremum<!dir>(node->child[1]);
                      return;
                  }
                  for (; node->parent && node->side() == dir; node = node->parent)
                      ;
                  node = node->parent;
              }
          };
          Node *root{}; 
          ll size_{};   
          SplayTree() {}
          ~SplayTree() { destroy(root); }
          static void destroy(Node *const node) {
              if (!node) {
                  return;
              }
              for (Node *const child : node->child) {
                  destroy(child);
              }
              delete node;
          }
          void insert(Node *const x) {
              ++size_;
              if (!root) {
                  root = x;
                  return;
              }
              auto y = root;
              while (true) {
                  auto &nw = y->child[x->value > y->value];
                  if (!nw) {
                      nw = x;
                      nw->parent = y;
                      root = nw;
                      nw->splay();
                      return;
                  }
                  y = nw;
              }
              return;
          }
          void insert(const T &key) {
              insert(new SplayNode{key});
          }
          void erase(Node *const x) {
              assert(x);
              x->splay();
              root = join(x->child[0], x->child[1]);
              delete x;
              --size_;
          }
          void erase(const T &key) { erase(find(key)); }
          template <bool i> static Node *extremum(Node * x) {
              assert(x);
              for(; x->child[i]; x = x->child[i]);
              return x;
          }
          static Node *join(Node *const a, Node *const b) {
              if (!a) {
                  b->parent = nullptr;
                  return b;
              }
              Node *const mx = extremum<true>(a);
              mx->splay();
              assert(mx->child[1] == nullptr);
              mx->child[1] = b;
              mx->parent = nullptr;
              return mx;
          }
          Node *find(const T &key) {
              auto x = root;
              for (; x && key != x->value; x = x->child[key > x->value])
                  ;
              return x;
          }
          ll size() const { return size_; }
          bool empty() const { return size() == 0; }
          iterator begin() { return iterator{extremum<false>(root)}; }
          iterator end() { return iterator{nullptr}; }
      };
      void test_splay_tree() {
          SplayTree<int> sp;
          sp.insert(4);
          sp.insert(3);
          sp.insert(5);
          assert(sp.size() == 3);
          assert(!sp.empty());
          assert(sp.find(4)->value == 4);
          assert(sp.find(3)->value == 3);
          assert(sp.find(5)->value == 5);
          assert(sp.find(2) == nullptr);
          assert(sp.find(6) == nullptr);
          sp.erase(3);
          assert(sp.size() == 2);
          assert(sp.find(3) == nullptr);
          assert(sp.find(5)->value == 5);
          assert(sp.find(4)->value == 4);
          sp.insert(20);
          sp.insert(-2);
          sp.insert(6);
          vl expected{-2, 4, 5, 6, 20};
          assert(sp.size() == expected.size());
          for (auto x : expected) {
              assert(sp.find(x)->value == x);
          }
          vl vec;
          copy(sp.begin(), sp.end(), back_inserter(vec));
          assert(vec == expected);
      }
      } // namespace splay_tree
      using namespace splay_tree;

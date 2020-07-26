
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_link_cut.hpp.rst.txt:

Program Listing for File program_listing_file_link_cut.hpp.rst.txt
==================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_link_cut.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_link_cut.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_link_cut.hpp:
   
   Program Listing for File link_cut.hpp
   =====================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_link_cut.hpp>` (``link_cut.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      #include "core.hpp"
      #include "splay_tree.hpp"
      using Node = SplayNode<ll, true>;
      Node *make_tree() {
          return new Node{};
      }
      void detach_child(Node* node){
          if(node->child[1]){
              node->child[1]->path_parent = node;
              node->child[1]->parent = nullptr;
          }
      }
      Node *access(Node *node) {
          node->splay();
          detach_child(node);
          node->child[1] = nullptr;
          Node *par = node;
          while (node->path_parent) {
              par = node->path_parent;
              par->splay();
              detach_child(par);
              par->attach(1, node);
              node->path_parent = nullptr;
              node->splay();
          }
          return par;
      }
      Node *find_root(Node *node) {
          access(node);
          for (; node->child[0]; node = node->child[0])
              ;
          access(node);
          return node;
      }
      void cut(Node *node) {
          access(node);
          node->child[0]->parent = nullptr;
          node->child[0] = nullptr;
      }
      void link(Node *par, Node *child) {
          access(child);
          access(par);
          child->attach(0, par);
      }
      Node *lca(Node *u, Node *v) {
          if (find_root(u) != find_root(v)) {
              return nullptr;
          }
          access(u);
          return access(v);
      }
      void test_link_cut_tree() {
          vector<Node *> nodes(10);
          generate(al(nodes), make_tree);
          link(nodes[1], nodes[2]);
          assert(find_root(nodes[2]) == nodes[1]);
          assert(find_root(nodes[1]) == nodes[1]);
          assert(lca(nodes[1], nodes[2]) == nodes[1]);
          link(nodes[0], nodes[1]);
          assert(lca(nodes[2], nodes[1]) == nodes[1]);
          assert(lca(nodes[0], nodes[2]) == nodes[0]);
          assert(lca(nodes[0], nodes[1]) == nodes[0]);
          assert(lca(nodes[1], nodes[1]) == nodes[1]);
          assert(lca(nodes[1], nodes[8]) == nullptr);
          assert(find_root(nodes[2]) == nodes[0]);
          assert(find_root(nodes[1]) == nodes[0]);
          assert(find_root(nodes[0]) == nodes[0]);
          link(nodes[3], nodes[4]);
          link(nodes[4], nodes[5]);
          assert(find_root(nodes[5]) == nodes[3]);
          link(nodes[0], nodes[3]);
          assert(lca(nodes[4], nodes[1]) == nodes[0]);
          assert(lca(nodes[4], nodes[4]) == nodes[4]);
          assert(lca(nodes[6], nodes[4]) == nullptr);
          link(nodes[6], nodes[7]);
          link(nodes[6], nodes[8]);
          link(nodes[8], nodes[9]);
          link(nodes[0], nodes[6]);
          assert(lca(nodes[6], nodes[4]) == nodes[0]);
          assert(find_root(nodes[3]) == nodes[0]);
          assert(find_root(nodes[2]) == nodes[0]);
          cut(nodes[1]);
          assert(find_root(nodes[2]) == nodes[1]);
          cut(nodes[3]);
          assert(find_root(nodes[3]) == nodes[3]);
          assert(find_root(nodes[4]) == nodes[3]);
          assert(find_root(nodes[5]) == nodes[3]);
          cut(nodes[4]);
          link(nodes[0], nodes[4]);
          assert(find_root(nodes[5]) == nodes[0]);
          assert(find_root(nodes[9]) == nodes[0]);
          assert(find_root(nodes[6]) == nodes[0]);
          cut(nodes[8]);
          assert(find_root(nodes[9]) == nodes[8]);
          assert(find_root(nodes[8]) == nodes[8]);
          assert(find_root(nodes[0]) == nodes[0]);
      }


.. _program_listing_file_docs__build_html__sources_api_program_listing_file_treap.hpp.rst.txt:

Program Listing for File program_listing_file_treap.hpp.rst.txt
===============================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_treap.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_treap.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_treap.hpp:
   
   Program Listing for File treap.hpp
   ==================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_treap.hpp>` (``treap.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      #include "core.hpp"
      template <typename Key, typename Data> struct treap {
          treap *l{}, *r{}; 
          ll pri{};     
          Key key{};    
          Data data{};      
          bool rev{};   
          treap(Key const &key_) : pri(reng()), key{key_} { update_data(&this); }
      };
      template <typename Key, template <typename> typename Data_Temp>
      using treap_t = treap<Key, Data_Temp<Key>>;
      template <typename Key> struct size_data { ll size{}; };
      template <typename Key>
      size_data<Key> operator+(size_data<Key> const &l, size_data<Key> const &r) {
          return size_data<Key>{l.size + r.size + 1};
      }
      template <typename Stream, typename Key>
      ostream &operator<<(Stream &os, size_data<Key> const &data) {
          return os << "size = " << data.size << endl;
      }
      template <typename Key, typename Data> Data get_data(treap<Key, Data> *trp) {
          return trp ? trp->data : Data{};
      }
      template <typename Trp> void update_data(Trp *trp) {
          if (!trp) {
              return;
          }
          trp->data = get_data(trp->l) + get_data(trp->r);
      }
      template <typename Key, typename Data, typename Trp = treap<Key, Data>>
      void split(treap<Key, Data> *trp, const Key &key, Trp *&l, Trp *&r) {
          if (!trp) {
              l = r = nullptr;
          } else if (key < trp->key) {
              split(trp->l, key, l, trp->l);
              r = trp;
          } else {
              split(trp->r, key, trp->r, r);
              l = trp;
          }
          update_data(trp);
      }
      template <typename Trp>[[nodiscard]] Trp *join(Trp *l, Trp *r) {
          down(l);
          down(r);
          auto ret = [&] {
              if (!l) {
                  return r;
              } else if (!r) {
                  return l;
              } else if (l->pri < r->pri) {
                  r->l = join(l, r->l);
                  return r;
              } else {
                  l->r = join(l->r, r);
                  return l;
              }
          }();
          update_data(ret);
          return ret;
      }
      template <typename Trp> void insert(Trp *&trp, Trp *x) {
          if (!trp) {
              trp = x;
          } else if (trp->pri < x->pri) {
              split(trp, x->key, x->l, x->r), trp = x;
          } else {
              insert(x->key < trp->key ? trp->l : trp->r, x);
          }
          update_data(trp);
      }
      template <typename Key, typename Data, typename Trp = treap<Key, Data>>
      auto insert(treap<Key, Data> *&trp, const Key &key) {
          return insert(trp, new Trp{key});
      }
      template <typename Key, typename Data, typename Trp = treap<Key, Data>>
      void erase(treap<Key, Data> *&trp, const Key &key) {
          if (trp->key == key) {
              trp = join(trp->l, trp->r);
          } else {
              erase(key < trp->key ? trp->l : trp->r, key);
          }
          update_data(trp);
      }
      // Implicit treaps
      template <typename Trp> void down(Trp *trp) {
          if (!(trp && trp->rev)) {
              return;
          }
          swap(trp->l, trp->r);
      #define flip(x)                                                                \
          if (trp->x) {                                                          \
              trp->x->rev ^= 1;                                              \
          }
          flip(l) flip(r)
      #undef flip
              trp->rev = 0;
      }
      template <typename Trp>
      void split_imp(Trp *trp, ll pos, Trp *&l, Trp *&r, ll sum = 0) {
          if (!trp) {
              l = r = nullptr;
              return;
          }
          down(trp);
          ll cur = sum + get_data(trp->l).size;
          if (pos <= cur) {
              split_imp(trp->l, pos, l, trp->l, sum);
              r = trp;
          } else {
              split_imp(trp->r, pos, trp->r, r, cur + 1);
              l = trp;
          }
          update_data(trp);
      }
      template <typename Trp> void insert_imp(Trp *&trp, Trp *x, ll pos) {
          Trp *l, *r;
          split_imp(trp, pos, l, r);
          l = join(l, x);
          trp = join(l, r);
      }
      template <typename Trp> void erase_imp(Trp *&trp, ll pos) {
          Trp *l, *r, *x, *nr;
          split_imp(trp, pos, l, r);
          split_imp(r, 1, x, nr);
          trp = join(l, nr);
      }
      template <typename Trp> auto get_imp(Trp *&trp, ll pos) {
          Trp *l, *r, *x, *nr;
          split_imp(trp, pos, l, r);
          split_imp(r, 1, x, nr);
          trp = join(join(l, x), nr);
          return x->key;
      }
      template <typename Key, typename Data, typename Trp = treap<Key, Data>>
      auto insert_imp(treap<Key, Data> *&trp, Key const &key, ll pos) {
          return insert_imp(trp, new Trp{key}, pos);
      }
      template <typename Stream, typename... Ts>
      auto &operator<<(Stream &os, treap<Ts...> *trp) {
          static ll lvl = -1;
          with _w{lvl + 1, lvl};
          string tab(lvl, ' ');
          if (trp) {
              os << tab << "key = " << trp->key << " "
                 << "priority = " << trp->pri << " " << trp->data << endl;
              os << tab << "Left" << endl
                 << trp->l << tab << "Right" << endl
                 << trp->r;
          } else {
              os << tab << "null" << endl;
          }
          return os;
      }
      template <typename Key, typename Data>
      void to_array(treap<Key, Data> *trp, vector<Key> &out) {
          if (!trp) {
              return;
          }
          to_array(trp->l, out);
          out.push_back(trp->key);
          to_array(trp->r, out);
      }
      template <typename Key, typename Data>
      vector<Key> to_array(treap<Key, Data> *trp) {
          vector<Key> out;
          to_array(trp, out);
          return out;
      }

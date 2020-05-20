template <typename Key, typename Data> struct treap {
  treap *l{}, *r{}; // left and right nodes
  ll pri{};         // random heap priority
  Key key{};        // binary search tree key
  Data data{};
  bool rev{};
  treap(Key const &key_) : pri{reng()}, key{key_} { update_data(&this); }
};
template <typename Key, template <typename> typename Data_Temp>
using treap_t = treap<Key, Data_Temp<Key>>;
template <typename Key> struct size_data { ll size{}; };
template <typename Key>
size_data<Key> operator+(size_data<Key> const &l, size_data<Key> const &r) {
  // Returns the data for a node given the data for the children.
  return size_data<Key>{l.size + r.size + 1};
}
template <typename Key>
ostream &operator<<(ostream &os, size_data<Key> const &data) {
  return os << "size = " << data.size << endl;
}
template <typename Key, typename Data> Data get_data(treap<Key, Data> *trp) {
  return trp ? trp->data : Data{};
}
void update_data(auto *trp) {
  if (!trp) {
    return;
  }
  trp->data = get_data(trp->l) + get_data(trp->r);
}
void split(auto *trp, auto const &key, auto *&l, auto *&r) {
  // Splits the treap by key
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
  // All the keys in l are less than the keys in r
  down(l);
  down(r);
  auto ret = [&]() {
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
template <typename Trp> auto insert(Trp *&trp, auto const &key) {
  return insert(trp, new Trp{key});
}
void erase(auto *&trp, const auto &key) {
  if (trp->key == key) {
    trp = join(trp->l, trp->r);
  } else {
    erase(key < trp->key ? trp->l : trp->r, key);
  }
  update_data(trp);
}
// Implicit treaps
void down(auto *trp) {
  if (!(trp && trp->rev)) {
    return;
  }
  swap(trp->l, trp->r);
#define flip(x)                                                                \
  if (trp->x) {                                                                \
    trp->x->rev ^= 1;                                                          \
  }
  flip(l) flip(r)
#undef flip
      trp->rev = 0;
}
void split_imp(auto *trp, ll pos, auto *&l, auto *&r, ll sum = 0) {
  // Splits the treap by pos
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
template <typename Trp> auto insert_imp(Trp *&trp, auto const &key, ll pos) {
  return insert_imp(trp, new Trp{key}, pos);
}
template <typename T, typename... Ts> T &operator<<(T &os, treap<Ts...> *trp) {
  static ll lvl = -1;
  with _w{lvl + 1, lvl};
  string tab(lvl, ' ');
  if (trp) {
    os << tab << "key = " << trp->key << " "
       << "priority = " << trp->pri << " " << trp->data << endl;
    os << tab << "Left" << endl << trp->l << tab << "Right" << endl << trp->r;
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
  out.pb(trp->key);
  to_array(trp->r, out);
}
template <typename Key, typename Data>
vector<Key> to_array(treap<Key, Data> *trp) {
  // Returns the array of keys for an implicit treap.
  vector<Key> out;
  to_array(trp, out);
  return out;
}
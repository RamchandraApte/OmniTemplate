struct dsu {
  mutable vl p;
  vl s;
  explicit dsu(ll n) : p(n), s(n, 1) { iota(al(p), 0); }
  ll operator[](ll x) const { return x == p[x] ? x : p[x] = this[p[x]]; }
  auto operator()(ll x, ll y) {
    x = this[x];
    y = this[y];
    if (x == y) {
      return false;
    }
    if (s[x] > s[y]) {
      swap(x, y);
    }
    s[y] += s[x];
    p[x] = y;
    return true;
  }
};
template <typename Stream> auto &operator<<(Stream &os, dsu const &d) {
  os << "dsu{";
  fo(i, d.p.size()) {
    if (i) {
      os << delim;
    }
    os << d[i];
  }
  return os << "}";
}

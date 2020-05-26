struct first_cmp {
  template <typename T> bool operator()(T a, T b) const {
    return a.first < b.first;
  }
};
auto tim = 0LL;
tm() struct pers {
  using event = pair<ll, T>;
  set<event, first_cmp> s;
  auto operator=(const T &v) {
    event e{tim, v};
    s.erase(e);
    s.insert(e);
  }
  operator auto() const { return (*--s.upper_bound({tim, T{}})).second; }
};
template <typename Stream, typename T>
auto &operator<<(Stream &os, pers<T> const &p) {
  return os << static_cast<T>(p);
}

namespace std {
auto operator<(pt const &a, pt const &b) {
  return map_args([](auto x) { return tuple{real(x), imag(x)}; })(a, b);
}
} // namespace std
auto dot(pt const &a, pt const &b) { return real(conj(a) * b); }
auto wedge(pt const &a, pt const &b) { return imag(conj(a) * b); }
auto area(pt a, pt b, pt c) { return wedge(b - a, c - a); }
auto ccw(pt a, pt b, pt c) {
  ll w = area(a, b, c);
  if (!(a == b || a == c || b == c || w)) {
    throw invalid_argument{"Points are collinear."};
  }
  return w > 0;
}
template <typename Cont> auto hull(Cont &v, df(do_sort, true)) {
  if (do_sort) {
    const auto p = *min_element(al(v), map_args([](pt a) {
                                  return tuple{imag(a), real(a)};
                                }));
    sort(al(v), bind(ccw, p, _1, _2));
  }
  vc<pt> h;
  for (auto x : v) {
    while (h.size() >= 2 && !ccw(h[h.size() - 2], h.back(), x)) {
      h.pop_back();
    }
    h.push_back(x);
  }
  return h;
}
template <typename Cont, typename Func>
auto convex_min(const Cont &r, const Func &f) {
  return *partition_point(al(r), [&](auto i) { return !(f(i) < f(i + 1)); });
}
struct cht {
  vc<pt> h;
  template <typename Cont> cht(Cont &v) {
    uniq(v, map_args(lambda(imag), equal_to{}), map_args(lambda(conj)));
    h = dbg(hull(v, false));
  }
  auto min(ll x) {
    auto const eval = [&](const auto &i) {
      return real(h[i]) * x + imag(h[i]);
    };
    return eval(convex_min(ra{size(h) - 1}, eval));
  }
};

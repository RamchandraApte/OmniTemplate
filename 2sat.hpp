#pragma once
#include "core.hpp"
#include "graph_theory.hpp"
optional<vc<char>> sat2(const vc<pr> &v) {
  /*
  Takes a 2 SAT instance and returns a solution.
  Numerical negation represents logical negation.
  0 means empty
  */
  ll n = 0;
  for (const auto &p : v) {
    n = max<ll>(n, max(abs(p.first), abs(p.second)));
  }
  vc<vl> g(2 * n + 1);
  for (const auto &p : v) {
    if (p.first) {
      g[n - p.first].pb(n + p.second);
    }
    if (p.second) {
      g[n - p.second].pb(n + p.first);
    }
  }
  dfs topo{g};
  topo();
  vl idx(size(g));
  fo(i, size(topo.q)) { idx[topo.q[i]] = i; }
  vc<char> vals(n + 1, -1);
  auto comp = scc(g);
  fo(i, 1, n + 1) {
    auto x = idx[comp[n + i]], nx = idx[comp[n - i]];
    if (nx == x) {
      return nullopt;
    }
    vals[i] = nx < x;
  }
  return vals;
}
void test_sat2() {
  const auto ret = *sat2({{1, 2}, {-2, 3}});
  for (char c : ret) {
    dbg((ll)c);
  }
}

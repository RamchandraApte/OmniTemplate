
.. _program_listing_file_docs__build_html__sources_api_program_listing_file_graph_theory.hpp.rst.txt:

Program Listing for File program_listing_file_graph_theory.hpp.rst.txt
======================================================================

|exhale_lsh| :ref:`Return to documentation for file <file_docs__build_html__sources_api_program_listing_file_graph_theory.hpp.rst.txt>` (``docs/_build/html/_sources/api/program_listing_file_graph_theory.hpp.rst.txt``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
   .. _program_listing_file_graph_theory.hpp:
   
   Program Listing for File graph_theory.hpp
   =========================================
   
   |exhale_lsh| :ref:`Return to documentation for file <file_graph_theory.hpp>` (``graph_theory.hpp``)
   
   .. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS
   
   .. code-block:: cpp
   
      #pragma once
      #include "core.hpp"
      #include "dsu.hpp"
      #include "linear_algebra.hpp"
      namespace graph_theory {
      struct edge {
          ll weight, a, b;
          auto to_tuple() const { return tuple{weight, a, b}; }
      };
      bool operator<(edge const &a, edge const &b) {
          return a.to_tuple() < b.to_tuple();
      }
      bool operator==(edge const &a, edge const &b) {
          return a.to_tuple() == b.to_tuple();
      }
      template <typename Stream> auto &operator<<(Stream &os, edge const &e) {
          return os << "edge{" << e.a << "-(" << e.weight << ")>" << e.b << "}";
      }
      auto add_edge(vector<vl> &graph, ll u, ll v) {
          graph[u].push_back(v);
          graph[v].push_back(u);
      }
      auto shortest_dist(vector<vector<pr>> graph, ll source) {
          vl d(graph.size(), inf), pv(graph.size(), -1);
          prio_queue_t<pr, greater<>> q;
          d[source] = 0;
          fo(i, d.size()) { q.push({d[i], i}); }
          while (q.size()) {
              const auto [di, a] = q.top();
              q.pop();
              if (di != d[a]) {
                  continue;
              }
              for (const auto &edge : graph[a]) {
                  const auto &[b, w] = edge;
                  auto &x = d[b];
                  auto nw = di + w;
                  if (nw < x) {
                      pv[b] = a;
                      x = nw;
                      q.push({x, b});
                  }
              }
          }
          return array<vl, 2>{d, pv};
      }
      // TODO do we want to consider zero-length paths?
      auto shortest_dist(matrix<ll> const &graph) {
          assert(graph.rows_n == graph.cols_n);
          auto n = graph.rows_n;
          auto d = graph;
          fo(k, n) {
              fo(i, n) {
                  fo(j, n) {
                      auto &x = d[i][j];
                      x = min(x, d[i][k] + d[k][j]);
                  }
              }
          }
          return d;
      }
      void test_shortest_dist() {
          matrix<ll> g{{7, 2, 5}, {2, 4, 1}, {3, 2, 5}};
          matrix<ll> short_dist{{4, 2, 3}, {2, 3, 1}, {3, 2, 3}};
          assert(shortest_dist(g) == short_dist);
          const auto n = g.rows_n;
          vector<vector<pr>> adj(n);
          fo(i, 0, n) {
              fo(j, 0, n) { adj[i].push_back({j, g[i][j]}); }
          }
          fo(s, 0, n) {
              // TODO test pv
              const auto dijkstra = shortest_dist(adj, s)[0];
              auto floyd = vl(short_dist[s], short_dist[s] + n);
              floyd[s] = 0;
              assert((dijkstra == floyd));
          }
      }
      auto mst(vector<edge> edges, const ll n) {
          sort(al(edges));
          dsu d{n};
          vector<edge> ret;
          for (const auto &e : edges) {
              if (!d.join(e.a, e.b)) {
                  continue;
              }
              ret.push_back(e);
          }
          return ret;
      }
      void test_mst() {
          vector<edge> edges{{5, 0, 3}, {2, 1, 2}, {3, 1, 3}, {1, 3, 2}};
          auto ret = mst(edges, 6);
          sort(al(ret));
          assert((ret == vector<edge>{edges[3], edges[1], edges[0]}));
      }
      struct gsearch {
          vector<vl> const &graph;
          vc<char> visited; 
          deque<ll> q;      
          vl parent;    
          vl distance;      
          gsearch(const vector<vector<ll>> &g_)
              : graph(g_), visited(graph.size()), parent(graph.size(), -1),
                distance(graph.size(), inf) {}
          virtual void operator()(ll) = 0;
          void operator()() {
              /* Run the searcher on all vertices. Useful for visiting the
               * entire graph, and not just one connected component. */
              fo(i, graph.size()) {
                  if (!visited[i]) {
                      this(i);
                  }
              }
          }
          void add(const ll child, const ll par) {
              distance[child] = distance[par] + 1;
              parent[child] = par;
          }
      };
      template <typename Searcher> vector<ll> get_size(const Searcher &search) {
          vector<ll> sz(search.parent.size(), 1);
          for (auto idx : rev(search.q)) {
              if (search.parent[idx] != -1) {
                  sz[search.parent[idx]] += sz[idx];
              }
          }
          return sz;
      }
      struct dfs : public gsearch {
          using gsearch::operator(), gsearch::gsearch;
          void operator()(const ll source) {
              visited[source] = true;
              for (const auto &j : graph[source]) {
                  if (visited[j]) {
                      continue;
                  }
                  add(j, source);
                  this(j);
              }
              q.push_front(source);
          }
      };
      struct bfs : public gsearch {
          using gsearch::operator(), gsearch::gsearch;
          void operator()(ll source) {
              ll old_size = q.size();
              q.push_back(source);
              visited[source] = true;
              distance[source] = 0;
              for (ll idx = old_size; idx < q.size(); ++idx) {
                  auto i = q[idx];
                  for (const auto &j : graph[i]) {
                      if (visited[j]) {
                          continue;
                      }
                      q.push_back(j);
                      visited[j] = true;
                      add(j, i);
                  }
              }
          }
      };
      void test_bfs() {
          vector<vl> g(4);
          add_edge(g, 0, 1);
          add_edge(g, 1, 2);
          add_edge(g, 1, 3);
          add_edge(g, 2, 3);
          bfs b{g};
          b(0);
          assert((b.parent == vl{-1, 0, 1, 1}));
          assert((b.distance == vl{0, 1, 2, 2}));
      }
      auto trans(const vector<vl> &graph) {
          ll n = size(graph);
          vector<vl> h(n);
          fo(i, n) {
              for (ll j : graph[i]) {
                  h[j].push_back(i);
              }
          }
          return h;
      }
      void test_trans() {
          assert((trans(vector<vl>{{2, 3}, {2, 1}, {2}, {2, 3, 1}}) ==
              vector<vl>{{}, {1, 3}, {0, 1, 2, 3}, {0, 3}}));
          assert((trans(vector<vl>{}) == vector<vl>{}));
      }
      auto scc(const vector<vl> &graph) {
          auto h = trans(graph);
          vl cm(size(graph), -1);
          auto assign = fix{[&](const auto &assign, ll u, ll c) -> void {
              if (cm[u] != -1) {
                  return;
              }
              cm[u] = c;
              for (ll v : h[u]) {
                  assign(v, c);
              }
          }};
          dfs s{graph};
          s();
          for (ll i : s.q) {
              assign(i, i);
          }
          return cm;
      }
      void test_scc() {
          vector<vl> g(5);
          g[0].push_back(3);
          g[3].push_back(1);
          g[1].push_back(2);
          g[2].push_back(0);
          g[0].push_back(4);
          g[2].push_back(4);
          const auto cm = scc(g);
          vl v{cm[0], cm[1], cm[2], cm[3]};
          // TODO refactor this into a function
          assert((all_of(al(v), [&](auto x) { return x == v[0]; })));
          assert(cm[4] != cm[0]);
      }
      auto bipartite(const vector<vl> &graph) {
          bfs b{graph};
          b();
          auto n = size(graph);
          vl s(n);
          for (auto i : b.q) {
              if (const auto par = b.parent[i]; par != -1) {
                  s[i] = !s[par];
              }
          }
          bool bi = true;
          fo(i, n) {
              for (const auto j : graph[i]) {
                  bi &= s[i] != s[j];
              }
          }
          return bi ? optional{s} : nullopt;
      }
      void test_bipartite() {
          vector<vl> g(6);
          // (2,1,4) is one side, and (5,3,0) is another side
          // connected component 1
          add_edge(g, 2, 5);
          add_edge(g, 4, 5);
          add_edge(g, 4, 3);
          // connected component 2
          add_edge(g, 1, 0);
          add_edge(g, 4, 0);
          const auto col = bipartite(g).value();
          fo(i, 0, g.size()) {
              for (auto j : g[i]) {
                  assert(col[i] ^ col[j]);
              }
          }
      }
      auto max_match(const vector<vl> &graph) {
          auto side = bipartite(graph).value();
          ll n = graph.size();
          vl match(n, -1);
          while (true) {
              /* Construct a directed graph to find aug_pathmenting paths*/
              // TODO refactor this to use lazy graphs
              vector<vl> aug_path(n + 2);
              const auto dummy_a = n;
              const auto dummy_b = n + 1;
              fo(i, n) {
                  for (ll j : graph[i]) {
                      if ((j == match[i]) == side[i]) {
                          aug_path[i].push_back(j);
                      }
                  }
              }
              fo(i, n) {
                  if (match[i] != -1) {
                      continue;
                  }
                  if (side[i]) {
                      aug_path[i].push_back(dummy_b);
                  } else {
                      aug_path[dummy_a].push_back(i);
                  }
              }
              bfs b{aug_path};
              b(dummy_a);
              if (b.distance[dummy_b] == inf) {
                  break;
              }
              vl vis(aug_path.size());
              auto path = fix{[&](const auto &path, ll i) -> bool {
                  if (vis[i]) {
                      return false;
                  }
                  vis[i] = true;
                  if (i == dummy_b) {
                      return true;
                  }
                  for (ll j : aug_path[i]) {
                      if (b.distance[j] == b.distance[i] + 1) {
                          if (path(j)) {
                              if (i < n && j < n) {
                                  match[i] = j;
                                  match[j] = i;
                              }
                              return true;
                          }
                      }
                  }
                  return false;
              }};
              path(dummy_a);
          }
          return match;
      }
      ll matching_size(const vl &matching) {
          return count_if(al(matching), [&](const auto x) { return x != -1; });
      }
      void test_max_match() {
          {
              vector<vl> g(3);
              // 0, 2 on one side, 1 on the other side
              add_edge(g, 0, 1);
              add_edge(g, 2, 1);
              assert((matching_size(max_match(g)) == 2 * 1));
          }
          {
              vector<vl> g(4);
              // 0, 2 on one side, 1, 3 on the other side
              add_edge(g, 0, 1);
              add_edge(g, 2, 1);
              add_edge(g, 2, 3);
              assert((matching_size(max_match(g)) == 2 * 2));
          }
          {
              vector<vl> g(6);
              // 0, 2, 4 on one side, 1, 3, 5 on the other side
              add_edge(g, 0, 1);
              add_edge(g, 0, 3);
              add_edge(g, 2, 3);
              add_edge(g, 2, 5);
              add_edge(g, 4, 1);
              add_edge(g, 4, 5);
              const auto matching = max_match(g);
              assert((matching_size(max_match(g)) == 2 * 3));
          }
          {
              vector<vl> g(6);
              // 0, 2, 4 on one side, 1, 3, 5 on the other side
              add_edge(g, 0, 1);
              add_edge(g, 0, 3);
              add_edge(g, 2, 1);
              add_edge(g, 2, 5);
              add_edge(g, 4, 1);
              add_edge(g, 4, 5);
              assert((matching_size(max_match(g)) == 2 * 3));
          }
          {
              vector<vl> g(6);
              // 0, 2, 4 on one side, 1, 3, 5 on the other side
              add_edge(g, 0, 1);
              add_edge(g, 2, 1);
              add_edge(g, 2, 5);
              add_edge(g, 4, 1);
              add_edge(g, 4, 5);
              assert((matching_size(max_match(g)) == 2 * 2));
          }
          {
              vector<vl> g(10);
              // 0, 2, 4 on one side, 1, 3, 5 on the other side
              fo(i, 0, g.size() / 2) {
                  if (2 * i - 1 >= 0) {
                      add_edge(g, 2 * i, 2 * i - 1);
                  }
                  if (2 * i + 1 < g.size()) {
                      add_edge(g, 2 * i, 2 * i + 1);
                  }
              }
              assert((matching_size(max_match(g)) == 2 * g.size() / 2));
          }
      }
      void test_add_edge() {
          vector<vl> g(10);
          add_edge(g, 3, 4);
          add_edge(g, 6, 4);
          add_edge(g, 9, 2);
          // Order doesn't matter
          for (auto &x : g) {
              sort(al(x));
          }
          assert(
              (g == vector<vl>{{}, {}, {9}, {4}, {3, 6}, {}, {4}, {}, {}, {2}}));
      }
      auto graph_in(vector<vl> &g, ll m) {
          fo(i, 0, m) {
              I(u);
              I(v);
              add_edge(g, --u, --v);
          }
      }
      /*vector<vector<ll>> chain_decomposition(const vector<vector<ll>>& graph){
          dfs d{graph};
          d();
      }*/
      pair<array<ll, 2>, ll> tree_diameter(const vector<vector<ll>> &g) {
          bfs b{g};
          b();
          const auto u = b.q.back();
          bfs b2{g};
          b2(u);
          const auto v = b2.q.back();
          auto c = v;
          fo(i, b2.distance[v] / 2) { c = b2.parent[c]; }
          return {{u, v}, c};
      }
      void test_tree_diameter() {
          {
              vector<vector<ll>> graph(5);
              add_edge(graph, 1, 3);
              add_edge(graph, 3, 2);
              add_edge(graph, 2, 0);
              add_edge(graph, 0, 4);
              auto ret = tree_diameter(graph);
              sort(al(ret.first));
              assert((ret.first == array<ll, 2>{1, 4}));
              assert(ret.second == 2);
          }
          {
              vector<vector<ll>> graph(5);
              add_edge(graph, 1, 3);
              add_edge(graph, 3, 2);
              add_edge(graph, 2, 0);
              add_edge(graph, 3, 4);
              auto ret = tree_diameter(graph).first;
              sort(al(ret));
              assert(ret[0] == 0);
          }
      }
      void test_graph_theory() {
          test_add_edge();
          test_trans();
          test_shortest_dist();
          test_mst();
          test_bfs();
          test_bipartite();
          test_scc();
          test_max_match();
          test_tree_diameter();
      }
      } // namespace graph_theory
      using namespace graph_theory;

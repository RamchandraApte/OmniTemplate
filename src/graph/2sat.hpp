#pragma once
#include "core/all.hpp"
#include "graph/all.hpp"
namespace sat2 {
optional<vector<char>> sat2(const vector<array<ll, 2>> &cnf, const ll n) {
	/*! @brief Takes a 2 SAT instance and returns a solution.
	Numerical negation represents logical negation.
	0 means empty
	*/
	vector<vector<ll>> graph(2 * n + 1);
	for (const auto &clause : cnf) {
		// Construct two implications that represent the clause
		graph[n - clause[0]].push_back(n + clause[1]);
		graph[n - clause[1]].push_back(n + clause[0]);
	}
	DFS topo{graph};
	topo();
	vector<ll> idx(size(graph));
	fo(i, size(topo.queue)) { idx[topo.queue[i]] = i; }
	vector<char> vals(n + 1, -1);
	auto comp = scc(graph);
	fo(i, 1, n + 1) {
		auto x = idx[comp[n + i]], nx = idx[comp[n - i]];
		if (nx == x) {
			return nullopt;
		}
		vals[i] = nx < x;
	}
	return vals;
}
} // namespace sat2
using namespace sat2;

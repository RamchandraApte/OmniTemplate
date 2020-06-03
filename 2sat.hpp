#pragma once
#include "core.hpp"
#include "graph_theory.hpp"
namespace sat2 {
optional<vector<char>> sat2(const vector<pr> &cnf) {
	/*!
	Takes a 2 SAT instance and returns a solution.
	Numerical negation represents logical negation.
	0 means empty
	*/
	ll n = 0;
	for (const auto &clause : cnf) {
		max_eq(n, static_cast<ll>(
			      max(abs(clause.first), abs(clause.second))));
	}
	vector<vl> graph(2 * n + 1);
	for (const auto &clause : cnf) {
		// TODO why if statement?
		if (clause.first) {
			graph[n - clause.first].push_back(n + clause.second);
		}
		if (clause.second) {
			graph[n - clause.second].push_back(n + clause.first);
		}
	}
	dfs topo{graph};
	topo();
	vl idx(size(graph));
	fo(i, size(topo.q)) { idx[topo.q[i]] = i; }
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
void test_sat2() {
	const auto ret1 = sat2({{2, 1}, {-2, 3}}).value();
	assert(ret1[1] || ret1[2]);
	assert(!ret1[2] || ret1[3]);
	const auto ret2 = sat2({{2, 1}, {3, 2}, {-2, -1}}).value();
	assert(ret2[1] || ret2[2]);
	assert(ret2[2] || ret2[3]);
	assert(!ret2[2] || !ret2[1]);
	const auto ret3 = sat2({{1, 1}, {-1, -1}});
	assert(!ret3);
	const auto ret4 = sat2({{1, 2}, {3, 2}, {-1, -1}, {-2, -2}});
	assert(!ret4);
}
} // namespace sat2
using namespace sat2;

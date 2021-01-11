#pragma once
#include "hld.hpp"
namespace hld::test {
void test_hld() {
	GraphAdj tree(6);
	tree.add_edge(0, 1);
	tree.add_edge(1, 5);
	tree.add_edge(0, 2);
	tree.add_edge(2, 3);
	tree.add_edge(2, 4);
	vector<ll> data{5, 3, 6, 1, 2, 7};
	HLD<ll, plus<>, DisjointSparseTable<ll, plus<>>> hld{tree, data};
	// 5 -> 1 -> 0 -> 2 -> 4
	const auto sum_of_idxs = [&](const vector<ll> &idxs) {
		ll sum = 0;
		for (const auto u : idxs) {
			sum += data[u];
		}
		return sum;
	};
	assert((hld.query(5, 4) == sum_of_idxs({5, 1, 0, 2, 4})));
	assert((hld.query(1, 0) == sum_of_idxs({1, 0})));
	assert((hld.query(0, 1) == sum_of_idxs({0, 1})));
	assert((hld.query(2, 1) == sum_of_idxs({2, 0, 1})));
	assert((hld.query(4, 3) == sum_of_idxs({4, 2, 3})));
	assert((hld.query(4, 4) == sum_of_idxs({4})));
}
} // namespace hld::test
using namespace hld::test;

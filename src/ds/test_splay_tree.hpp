#pragma once
#include "splay_tree.hpp"
namespace splay_tree::test {
void test_splay_tree() {
	/*! Tests the splay tree*/
	SplayTree<int> sp;
	sp.insert(4);
	sp.insert(3);
	sp.insert(5);
	assert(sp.size() == 3);
	assert(!sp.empty());
	assert(sp.find(4)->value == 4);
	assert(sp.find(3)->value == 3);
	assert(sp.find(5)->value == 5);
	assert(sp.find(2) == nullptr);
	assert(sp.find(6) == nullptr);
	sp.erase(3);
	assert(sp.size() == 2);
	assert(sp.find(3) == nullptr);
	assert(sp.find(5)->value == 5);
	assert(sp.find(4)->value == 4);
	sp.insert(20);
	sp.insert(-2);
	sp.insert(6);
	vl expected{-2, 4, 5, 6, 20};
	assert(sp.size() == expected.size());
	for (auto x : expected) {
		assert(sp.find(x)->value == x);
	}
	vl vec;
	copy(sp.begin(), sp.end(), back_inserter(vec));
	assert(vec == expected);
}
} // namespace splay_tree::test
using namespace splay_tree::test;

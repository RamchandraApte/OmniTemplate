#pragma once
#include "dsu.hpp"
namespace dsu_ds::test {
void test_dsu() {
	dsu d{100};
	fo(i, 100) { assert(d.find(i) == i); }
	assert(d.join(3, 4));
	assert(d.join(6, 10));
	assert(!d.join(6, 6));
	assert(d.join(10, 3));
	assert(!d.join(6, 3));
	vl idx{d.find(3), d.find(4), d.find(6), d.find(10)};
	assert(all_of(al(idx), [&](auto x) { return x == idx[0]; }));
	fo(i, 99) { d.join(i, i + 1); }
	fo(i, 100) { assert(d.find(i) == d.find(0)); }
}
} // namespace dsu_ds::test
using namespace dsu_ds::test;

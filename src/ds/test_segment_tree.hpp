#pragma once
#include "segment_tree.hpp"
namespace segment_tree::test {
template <bool has_lazy, bool has_ptr, bool has_pers, ll base> void test_segment_tree_impl() {
	SegmentTree<ll, Max, plus<>, has_lazy, has_ptr, has_pers, base> seg{1000};
	assert(seg.query(1, 3) == -inf);
	assert(seg.query(7, 9) == -inf);
	fo(i, 0, 10) { seg.update(i, i + 1, inf); }
	auto upd_old = [&] { return seg.update(0, 1, 0); };
	using NodePtr = typename decltype(seg)::NodeExp *;
	NodePtr old;
	if constexpr (has_pers) {
		old = upd_old();
	} else {
		upd_old();
	}
	assert(seg.query(0, 10) == 0);
	assert(seg.query(3, 4) == 0);
	seg.update(2, 3, 2);
	auto old2 = seg.update(4, 5, 3);
	if constexpr (has_pers) {
		assert(seg.query(0, 10, old) == 0);
	}
	assert(seg.query(0, 10) == 3);
	assert(seg.query(3, 4) == 0);
	assert(seg.query(2, 4) == 2);
	if constexpr (has_pers) {
		assert(seg.query(2, 4, old2) == 2);
	}
	seg.update(2, 3, -2);
	seg.update(4, 5, -3);
	assert(seg.query(2, 4) == 0);
	assert(seg.query(0, 10) == 0);
	if constexpr (has_pers) {
		assert(seg.query(0, 10, old) == 0);
		assert(seg.query(2, 4, old2) == 2);
	}
	fo(i, 0, 10) { seg.update(i, i + 1, -inf); }
	if constexpr (has_lazy) {
		seg.update(0, 10, inf);
		auto upd1 = [&] { return seg.update(3, 4, 10); };
		NodePtr old_lazy;
		if constexpr (has_pers) {
			old_lazy = upd1();
		} else {
			upd1();
		}
		assert(seg.query(0, 10) == 10);
		if constexpr (has_pers) {
			assert(seg.query(0, 10, old_lazy) == 10);
		}
		seg.update(2, 4, 20);
		assert(seg.query(3, 4) == 30);
		assert(seg.query(2, 4) == 30);
		assert(seg.query(2, 3) == 20);
		assert(seg.query(1, 10) == 30);
		seg.update(0, 2, 10);
		assert(seg.query(1, 10) == 30);
		if constexpr (has_pers) {
			assert(seg.query(0, 10, old) == 0);
			assert(seg.query(2, 4, old2) == 2);
			assert(seg.query(0, 10, old_lazy) == 10);
		}
	}
}
void test_segment_tree() {
	test_segment_tree_impl<false, false, false, 2>();
	// Test base
	test_segment_tree_impl<false, false, false, 3>();
	// Test lazy
	test_segment_tree_impl<true, false, false, 2>();
	// Test ptr
	test_segment_tree_impl<false, true, false, 2>();
	// test lazy and ptr
	test_segment_tree_impl<false, true, false, 2>();
	// test ptr and pers
	test_segment_tree_impl<false, true, true, 2>();
	// test lazy and ptr and pers
	test_segment_tree_impl<true, true, true, 2>();
}
} // namespace segment_tree::test
using namespace segment_tree::test;

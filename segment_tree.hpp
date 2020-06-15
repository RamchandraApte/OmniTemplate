#pragma once
#include "core.hpp"
// TODO non commutative monoids, specify the ordering
// TODO multidimensional
/*! Generic persistent explicit/implicit lazy based segment tree
 * T is the value type of the segment tree
 * Query is the monoid for queries
 * Update is the monoid for queries
 * Query must be an additive monoid of a semiring, and Update must be a
 * multiplicative monoid of a semiring
 * base is the segment tree base. Default is 2.
 */
struct Empty {};
template <typename T, typename Query, typename Update, bool has_lazy = true, bool has_ptr = true, bool has_pers = true, size_t base = 2> class SegmentTree {
      public:
	SegmentTree(const size_t size_arg) : size_{size_arg}, ceil_size{base_ceil(size_arg, base)}, nodes(!has_ptr ? base * ceil_size : 0) {
		if constexpr (has_ptr) {
			root = new NodeExp{};
		} else {
			root = 1;
		}
	}
	static_assert(!has_pers || has_ptr, "Pointers required for persistency");
	static_assert(base > 1, "Base must be at least 1");
	struct LazyPart {
		T lazy{identity(Update{}, T{})};
	};
	struct NodeCore : public conditional_t<has_lazy, LazyPart, Empty> {
		T qsum{identity(Query{}, T{})};
	};
	struct NodeExp : public NodeCore {
		array<NodeExp *, base> child{};
	};
	using Node = conditional_t<has_ptr, NodeExp *, size_t>;

	auto &get_core(NodeExp *const &obj) { return *obj; }
	auto &get_core(const size_t idx) { return nodes[idx]; }
	auto &get_child(NodeExp *const &obj, const size_t i) { return obj->child[i]; }
	auto get_child(const size_t idx, const size_t i) { return base * idx + i; }
	static size_t mid(const size_t node_l, const size_t node_r, const size_t i) {
		const auto df = (node_r - node_l) / base;
		return node_l + df * i;
	};
	void down(const Node idx, const size_t node_l, const size_t node_r) {
		const bool leaf = node_r - node_l == 1;
		if constexpr (has_ptr) {
			if (!leaf) {
				for (auto &ptr : idx->child) {
					if (!ptr) {
						ptr = new NodeExp{};
					}
				}
			}
		}
		if constexpr (has_lazy) {
			/*! Push lazy update down*/
			get_core(idx).qsum = Update{}(get_core(idx).qsum, get_core(idx).lazy);
			if (!leaf) {
				fo(i, base) { get_core(get_child(idx, i)).lazy += get_core(idx).lazy; }
			}
			get_core(idx).lazy = identity(Update{}, get_core(idx).lazy);
		}
	}
	T query(const size_t l, const size_t r, const Node idx, const size_t node_l,
		const size_t node_r) {
		/*! Returns the sum over the intersection of [query_l, query_r) with [node_l,
		 * node_r) */
		if (node_r <= l || r <= node_l) {
			return identity(Query{}, T{});
		}
		down(idx, node_l, node_r);
		if (l <= node_l && node_r <= r) {
			return get_core(idx).qsum;
		}

		auto ret = identity(Query{}, T{});
		fo(inc, base) { ret = Query{}(ret, query(l, r, get_child(idx, inc), mid(node_l, node_r, inc), mid(node_l, node_r, inc + 1))); }
		return ret;
	}
	T query(const size_t l, const size_t r, const Node custom_root) {
		if (!(0 <= l && l <= r && r <= size_)) {
			throw out_of_range{"Segment tree query out of bounds"};
		}
		return query(l, r, custom_root, 0, ceil_size);
	}
	T query(const size_t l, const size_t r) { return query(l, r, root); }
	Node update(const size_t l, const size_t r, const T val, Node idx, const size_t node_l, const size_t node_r) {
		/*! Update the range l to r with the update val
		 * returns the new node
		 */
		if (node_r <= l || r <= node_l) {
			return idx;
		}
		down(idx, node_l, node_r);
		if constexpr (has_pers) {
			idx = new NodeExp{*idx};
		}
		if (l <= node_l && node_r <= r) {
			if constexpr (has_lazy) {
				get_core(idx).lazy = Update{}(get_core(idx).lazy, val);
				down(idx, node_l, node_r);
			} else {
				get_core(idx).qsum = Update{}(get_core(idx).qsum, val);
			}
			return idx;
		}
		fo(inc, base) {
			auto get_update = [&] { return update(l, r, val, get_child(idx, inc), mid(node_l, node_r, inc), mid(node_l, node_r, inc + 1)); };
			if constexpr (has_pers) {
				get_child(idx, inc) = get_update();
			} else {
				get_update();
			}
		}
		get_core(idx).qsum = identity(Query{}, T{});
		fo(inc, base) { get_core(idx).qsum = Query{}(get_core(idx).qsum, get_core(get_child(idx, inc)).qsum); }
		return idx;
	}
	Node update(const size_t l, const size_t r, const T val) {
		if constexpr (!has_lazy) {
			assert(l + 1 == r);
		}
		return root = update(l, r, val, root, 0, ceil_size);
	}
	void destroy(Node node) {
		/*! Deallocate memory associated with the subtree of node*/
		if constexpr (has_ptr && !has_pers) {
			if (!node) {
				return;
			}
			fo(inc, base) { destroy(get_child(node, inc)); }
			delete node;
		}
	}
	~SegmentTree() {
		/*! Free memory allocator by the segment tree. Note: does not work for persistent*/
		if constexpr (has_ptr && !has_pers) {
			destroy(root);
		}
	}

      private:
	size_t size_;
	size_t ceil_size;
	Node root;
	vector<NodeCore> nodes;
};
template <bool has_lazy, bool has_ptr, bool has_pers, size_t base> void test_segment_tree_impl() {
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
	timer time_seg;
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

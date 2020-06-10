#pragma once
#include "core.hpp"
// TODO non commutative monoids, specify the ordering
size_t base_ceil(const size_t x, const size_t base) {
	ll pw = 1;
	for (; pw < x; pw *= base)
		;
	return pw;
}
// TODO persistent multidimensional
/*! Generic explicit/implicit lazy based segment tree
 * T is the value type of the segment tree
 * Query is the monoid for queries
 * Update is the monoid for queries
 * Query must be an additive monoid of a semiring, and Update must be a
 * multiplicative monoid of a semiring
 * base is the segment tree base. Default is 2.
 */
struct Empty {};
template <typename T, typename Query, typename Update, bool has_lazy = true, bool has_ptr = true,
	  size_t base = 2>
class SegmentTree {
      public:
	SegmentTree(const size_t size_arg) : size_{size_arg}, ceil_size{base_ceil(size_arg, base)}, nodes(!has_ptr ? base * ceil_size : 0) {
		if constexpr (!has_ptr) {
			root = 1;
		} else {
			root = new NodeExp{};
		}
	}
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
	auto get_child(NodeExp *const &obj, const size_t i) { return obj->child[i]; }
	auto get_child(const size_t idx, const size_t i) { return base * idx + i; }
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
		const auto mid = [&](size_t i) {
			return (node_l * (base - i) + node_r * i) / base;
		};
		fo(inc, base) { ret = Query{}(ret, query(l, r, get_child(idx, inc), mid(inc), mid(inc + 1))); }
		return ret;
	}
	T query(const size_t l, const size_t r) {
		if (!(0 <= l && l <= r && r <= size_)) {
			throw out_of_range{"Segment tree query out of bounds"};
		}
		return query(l, r, root, 0, ceil_size);
	}
	void update(const size_t l, const size_t r, const T val, const Node idx,
		    const size_t node_l, const size_t node_r) {
		/*! Update the range l to r with the update val*/
		if (node_r <= l || r <= node_l) {
			return;
		}
		down(idx, node_l, node_r);
		if (l <= node_l && node_r <= r) {
			if constexpr (has_lazy) {
				get_core(idx).lazy = Update{}(get_core(idx).lazy, val);
				down(idx, node_l, node_r);
			} else {
				get_core(idx).qsum = Update{}(get_core(idx).qsum, val);
			}
			return;
		}
		const auto mid = [&](size_t i) {
			return (node_l * (base - i) + node_r * i) / base;
		};
		get_core(idx).qsum = identity(Query{}, T{});
		fo(inc, base) {
			update(l, r, val, get_child(idx, inc), mid(inc), mid(inc + 1));
			get_core(idx).qsum = Query{}(get_core(idx).qsum, query(l, r, get_child(idx, inc), mid(inc), mid(inc + 1)));
		}
	}
	void update(const size_t l, const size_t r, const T val) {
		if constexpr (!has_lazy) {
			assert(l + 1 == r);
		}
		update(l, r, val, root, 0, ceil_size);
	}

      private:
	size_t size_;
	size_t ceil_size;
	Node root;
	vector<NodeCore> nodes;
};
void test_segment_tree() {
	constexpr bool has_lazy = true;
	SegmentTree<ll, Max, plus<>, has_lazy> seg{1000};
	assert(seg.query(1, 3) == -inf);
	assert(seg.query(7, 9) == -inf);
	fo(i, 0, 10) { seg.update(i, i + 1, inf); }
	assert(seg.query(0, 10) == 0);
	assert(seg.query(3, 4) == 0);
	seg.update(2, 3, 2);
	seg.update(4, 5, 3);
	assert(seg.query(0, 10) == 3);
	assert(seg.query(3, 4) == 0);
	assert(seg.query(2, 4) == 2);
	seg.update(2, 3, -2);
	seg.update(4, 5, -3);
	assert(seg.query(2, 4) == 0);
	assert(seg.query(0, 10) == 0);
	fo(i, 0, 10) { seg.update(i, i + 1, -inf); }
	if constexpr (has_lazy) {
		seg.update(0, 10, inf);
		seg.update(3, 4, 10);
		seg.update(2, 4, 20);
		assert(seg.query(3, 4) == 30);
		assert(seg.query(2, 4) == 30);
		assert(seg.query(2, 3) == 20);
		assert(seg.query(1, 10) == 30);
		seg.update(0, 2, 10);
		assert(seg.query(1, 10) == 30);
	}
}

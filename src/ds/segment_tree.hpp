#pragma once
#include "core/all.hpp"
#include "core/time.hpp"
inline namespace segment_tree {
// TODO non commutative monoids, specify the ordering
// TODO multidimensional
/*! @brief Generic persistent explicit/implicit lazy based segment tree, technically known as range
 * query tree.
 * @param T is the value type of the segment tree
 * @param Query is the monoid for queries
 * @param Update is the monoid for queries
 * @param Query must be an additive monoid of a semiring
 * @param Update must be a multiplicative monoid of a semiring
 * @param base is the segment tree base. Default is 2.
 */
template <typename T, typename Query, typename Update, bool has_lazy = true, bool has_ptr = true,
	  bool has_pers = true, ll base = 2>
class SegmentTree {
      public:
	SegmentTree(const ll size_arg)
	    : size_{size_arg}, ceil_size{power_ceil(size_arg, base)},
	      nodes(!has_ptr ? base * ceil_size : 0) {
		if constexpr (has_ptr) {
			root = new NodeExp{};
		} else {
			root = 1;
		}
	}
	SegmentTree(const vector<T> &arr) : SegmentTree(arr.size()) { build(arr); }
	static_assert(!has_pers || has_ptr, "Pointers required for persistency");
	static_assert(base > 1, "Base must be at least 1");
	struct LazyPart {
		T lazy{identity_elt(Update{}, T{})};
	};
	struct NodeCore : public conditional_t<has_lazy, LazyPart, Empty> {
		T qsum{identity_elt(Query{}, T{})};
	};
	struct NodeExp : public NodeCore {
		array<NodeExp *, base> child{};
	};
	using Node = conditional_t<has_ptr, NodeExp *, ll>;

	auto &get_core(NodeExp *const &obj) { return *obj; }
	auto &get_core(const ll idx) { return nodes[idx]; }
	auto &get_child(NodeExp *const &obj, const ll i) { return obj->child[i]; }
	auto get_child(const ll idx, const ll i) { return base * idx + i; }
	static ll mid(const ll node_l, const ll node_r, const ll i) {
		const auto df = (node_r - node_l) / base;
		return node_l + df * i;
	};
	void build(const vector<T> &arr) { build(arr, root, 0, ceil_size); }
	void build(const vector<T> &arr, const Node idx, const ll node_l, const ll node_r) {
		if (node_r - node_l == 1) {
			get_core(idx).qsum =
			    node_l < arr.size() ? arr[node_l] : identity_elt(Query{}, T{});
			return;
		}
		auto ret = identity_elt(Query{}, T{});
		fo(inc, base) {
			build(arr, get_child(idx, inc), mid(node_l, node_r, inc),
			      mid(node_l, node_r, inc + 1));
			ret = Query{}(ret, get_core(get_child(idx, inc)).qsum);
		}
		get_core(idx).qsum = ret;
	}
	/*! Push lazy updates down*/
	void down([[maybe_unused]] const Node idx, const ll node_l, const ll node_r) {
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
				fo(i, base) {
					get_core(get_child(idx, i)).lazy += get_core(idx).lazy;
				}
			}
			get_core(idx).lazy = identity_elt(Update{}, get_core(idx).lazy);
		}
	}
	T query(const ll l, const ll r, const Node idx, const ll node_l, const ll node_r) {
		/*! Returns the sum over the intersection of [query_l, query_r) with [node_l,
		 * node_r) */
		if (node_r <= l || r <= node_l) {
			return identity_elt(Query{}, T{});
		}
		down(idx, node_l, node_r);
		if (l <= node_l && node_r <= r) {
			return get_core(idx).qsum;
		}

		auto ret = identity_elt(Query{}, T{});
		fo(inc, base) {
			ret =
			    Query{}(ret, query(l, r, get_child(idx, inc), mid(node_l, node_r, inc),
					       mid(node_l, node_r, inc + 1)));
		}
		return ret;
	}
	T query(const ll l, const ll r, const Node custom_root) {
		if (!(0 <= l && l <= r && r <= size_)) {
			throw out_of_range{"Segment tree query out of bounds"};
		}
		return query(l, r, custom_root, 0, ceil_size);
	}
	T query(const ll l, const ll r) { return query(l, r, root); }
	Node update(const ll l, const ll r, const T val, Node idx, const ll node_l,
		    const ll node_r) {
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
			auto get_update = [&] {
				return update(l, r, val, get_child(idx, inc),
					      mid(node_l, node_r, inc),
					      mid(node_l, node_r, inc + 1));
			};
			if constexpr (has_pers) {
				get_child(idx, inc) = get_update();
			} else {
				get_update();
			}
		}
		get_core(idx).qsum = identity_elt(Query{}, T{});
		fo(inc, base) {
			get_core(idx).qsum =
			    Query{}(get_core(idx).qsum, get_core(get_child(idx, inc)).qsum);
		}
		return idx;
	}
	Node update(const ll l, const ll r, const T val) {
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
	ll size_;
	ll ceil_size;
	Node root;		/*< Root node */
	vector<NodeCore> nodes; /*< 1-indexed implicit array of nodes */
};
} // namespace segment_tree

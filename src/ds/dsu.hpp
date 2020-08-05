#pragma once
#include "core/all.hpp"
inline namespace dsu_ds {
/*! @brief Disjoint-set data structure */
struct dsu {
	mutable vl parent; //!< The parent of each element
	vl size_; /*!< Size of set of representative element idx*/
	/*! Construct a dsu with n elements. Initially each element is in its own set.*/
	explicit dsu(const ll n) : parent(n), size_(n, 1) { iota(al(parent), 0); }
	/*! Returns the representative element of x */
	ll find(ll x) const {
		return x == parent[x] ? x : parent[x] = this.find(parent[x]);
	}
	/**
     *@brief Joins the set containing x with the set containing y
     *Returns true if the set containing x is different from the set containing y. Returns false otherwise, since nothing is done.
     */
	bool join(ll x, ll y) {
		x = this.find(x);
		y = this.find(y);
		if (x == y) {
			return false;
		}
		swap2(x, y, [&](auto idx) { return size_[idx]; });
		size_[y] += size_[x];
		parent[x] = y;
		return true;
	}
};
/*! Prints the set of each DSU node*/
template <typename Stream> auto &operator<<(Stream &os, dsu const &d) {
	os << "dsu{";
	fo(i, d.parent.size()) {
		if (i) {
			os << delim;
		}
		os << d.find(i);
	}
	return os << "}";
}
} // namespace dsu_ds

#pragma once
#include "core/all.hpp"
inline namespace dsu_ds {
/** @brief Disjoint-set data structure */
struct dsu {
	mutable vector<ll> parent; //!< The parent of each element
	vector<ll> size_;	   /*!< Size of set of representative element idx*/
	/** @brief Construct a dsu with n elements. Initially each element is in its own set.*/
	explicit dsu(const ll n) : parent(n), size_(n, 1) { iota(al(parent), 0); }
	/** @brief Returns the representative element of x */
	ll find(ll x) const { return x == parent[x] ? x : parent[x] = find(parent[x]); }
	/** @brief Joins the set containing x with the set containing y.
	 *  @returns true if the set containing x is different from the set containing y. Returns
	 * false otherwise, since nothing is done.
	 */
	bool join(ll x, ll y) {
		x = find(x);
		y = find(y);
		if (x == y) {
			return false;
		}
		swap2(x, y, [&](auto idx) { return size_[idx]; });
		size_[y] += size_[x];
		parent[x] = y;
		return true;
	}
};
/** @brief Prints the set of each DSU node*/
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

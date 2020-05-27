#pragma once
#include "core.hpp"
struct dsu {
	/*! Disjoint-set data structure */
	mutable vl p;
	vl s;
	explicit dsu(ll n) : p(n), s(n, 1) { iota(al(p), 0); }
	ll operator[](ll x) const {
		/*! Returns the representative element of x */
		return x == p[x] ? x : p[x] = this[p[x]];
	}
	auto operator()(ll x, ll y) {
		/*! Joins the set containing x with the set containing y*/
		x = this[x];
		y = this[y];
		if (x == y) {
			return false;
		}
		if (s[x] > s[y]) {
			swap(x, y);
		}
		s[y] += s[x];
		p[x] = y;
		return true;
	}
};
template <typename Stream> auto &operator<<(Stream &os, dsu const &d) {
	/*! Prints the parent of each DSU node*/
	os << "dsu{";
	fo(i, d.p.size()) {
		if (i) {
			os << delim;
		}
		os << d[i];
	}
	return os << "}";
}

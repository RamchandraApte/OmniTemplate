#pragma once
#include "core.hpp"
namespace dsu_ds {
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
void test_dsu() {
	dsu d{100};
	fo(i, 100) { assert(d[i] == i); }
	// TODO check return value of d()
	d(3, 4);
	d(6, 10);
	d(6, 6);
	d(10, 3);
	vl idx{d[3], d[4], d[6], d[10]};
	assert(all_of(al(idx), [&](auto x) { return x == idx[0]; }));
	fo(i, 99) { d(i, i + 1); }
	fo(i, 100) { assert(d[i] == d[0]); }
}
} // namespace dsu_ds
using namespace dsu_ds;

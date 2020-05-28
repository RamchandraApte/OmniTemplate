#pragma once
#include "core.hpp"
namespace std {
auto operator<(pt const &a, pt const &b) {
	return map_args([](auto x) { return tuple{real(x), imag(x)}; })(a, b);
}
} // namespace std
auto dot(pt const &a, pt const &b) { return real(conj(a) * b); }
void test_dot() {
	assert((dot({1, 2}, {2, 5}) == 1 * 2 + 2 * 5));
	assert((dot({0, 2}, {3, 0}) == 0 * 3 + 2 * 0));
}
auto wedge(pt const &a, pt const &b) { return imag(conj(a) * b); }
void test_wedge() {
	assert((wedge({1, 0}, {0, 1}) == 1));
	assert((wedge({1, 1}, {1, 1}) == 0));
	assert((wedge({1, 0}, {0, 0}) == 0));
}
auto area(pt a, pt b, pt c) { return wedge(b - a, c - a); }
auto ccw(pt a, pt b, pt c) {
	/*! Returns whether moving through \f$a \rightarrow b \rightarrow c\f$
	 * is counterclockwise */
	ll w = area(a, b, c);
	if (!(a == b || a == c || b == c || w)) {
		throw invalid_argument{"Points are collinear."};
	}
	return w > 0;
}
template <typename Cont> auto hull(Cont &v, df(do_sort, true)) {
	/*! Returns the convex hull of the points in v*/
	if (do_sort) {
		const auto p =
		    *min_element(al(v), map_args([](pt a) {
					 return tuple{imag(a), real(a)};
				 }));
		sort(al(v), bind(ccw, p, _1, _2));
	}
	vc<pt> h;
	for (auto x : v) {
		while (h.size() >= 2 && !ccw(h[h.size() - 2], h.back(), x)) {
			h.pop_back();
		}
		h.push_back(x);
	}
	return h;
}
template <typename Range, typename Func>
auto convex_min(const Range &r, const Func &f) {
	/*! Returns the minimum of a convex function f over a Range r.*/
	return *partition_point(al(r),
				[&](auto i) { return !(f(i) < f(i + 1)); });
}
struct cht {
	/*! Convex-hull trick. This can be used to find the minimum of a set of
	 * lines at various points. */
	vc<pt> h; //!< The lines
	template <typename Cont> cht(const Cont v) {
		v = uniq(v, map_args(lambda(imag), equal_to{}),
			 map_args(lambda(conj)));
		h = dbg(hull(v, false));
	}
	auto min(ll x) {
		/*! Minimum value of the lines at x*/
		auto const eval = [&](const auto &i) {
			return real(h[i]) * x + imag(h[i]);
		};
		return eval(convex_min(ra{size(h) - 1}, eval));
	}
};
void test_geometry() {
	test_dot();
	test_wedge();
}

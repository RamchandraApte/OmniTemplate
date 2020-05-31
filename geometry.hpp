#pragma once
#include "core.hpp"
namespace std {
bool operator<(pt const &a, pt const &b) {
	/*! Compare points a and b lexicographically*/
	return map_args([](auto x) { return tuple{real(x), imag(x)}; })(a, b);
}
void test_less() {
	assert((pt{1, 2} < pt{3, 5}));

	assert((pt{1, 2} < pt{3, 1}));

	assert((pt{1, 1} < pt{1, 2}));

	assert((!(pt{1, 2} < pt{1, 1})));

	assert((!(pt{1, 2} < pt{1, 2})));
}
} // namespace std
namespace geometry {
// TODO generalize these products for multidimensional vectors
auto dot(pt const &a, pt const &b) {
	/*! returns the dot product of 2D vectors a and b, i.e. \f$a \cdot
	 * b\f$*/
	return real(conj(a) * b);
}
void test_dot() {
	assert((dot({1, 2}, {2, 5}) == 1 * 2 + 2 * 5));
	assert((dot({0, 2}, {3, 0}) == 0 * 3 + 2 * 0));
}
auto wedge(pt const &a, pt const &b) {
	/*! Returns the wedge product of 2D vectors a and b, \f$a \wedge b\f$*/
	return imag(conj(a) * b);
}
void test_wedge() {
	assert((wedge({1, 0}, {0, 1}) == 1));
	assert((wedge({1, 1}, {1, 1}) == 0));
	assert((wedge({1, 0}, {0, 0}) == 0));
}
auto area(pt a, pt b, pt c) { return wedge(b - a, c - a); }
auto ccw(pt a, pt b, pt c) {
	/*! Returns whether moving through \f$a \rightarrow b \rightarrow c\f$
	 * is counterclockwise. Throws std::invalid_argument if a, b, c are
	 * collinear. */
	// TODO what if points are identical?
	ll w = area(a, b, c);
	if (!(a == b || a == c || b == c || w)) {
		throw invalid_argument{"Points are collinear."};
	}
	return w > 0;
}
void test_ccw() {
	assert((ccw({1, 0}, {1, 1}, {0, 1})));
	assert((!ccw({0, 1}, {1, 1}, {1, 0})));
	auto test_collinear = [&](pt a, pt b, pt c) {
		try {
			ccw(a, b, c);
		} catch (invalid_argument) {
			return;
		}
		dbg(a);
		dbg(b);
		dbg(c);
		assert(false);
	};
	test_collinear({0, 1}, {0, 2}, {0, -1});
	test_collinear({2, 0}, {-3, 0}, {4, 0});
	test_collinear({4, 6}, {6, 9}, {-4, -6});
}
auto hull(vector<pt> &v, df(do_sort, true)) {
	/*! Returns the convex hull of the points in v*/
	vector<pt> h;
	if (do_sort) {
		const auto p =
		    *min_element(al(v), map_args([](pt a) {
					 return tuple{imag(a), real(a)};
				 }));
		sort(al(v), bind(ccw, p, _1, _2));
		h.pb(p);
	}
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
	/*! Returns x in Range r that minimizes the value of a convex function
	 * f(x).*/
	return *partition_point(al(r),
				[&](auto i) { return !(f(i) < f(i + 1)); });
}
void test_convex_min() {
	assert(
	    (convex_min(ra{-100, 100}, [](auto x) { return x * x + x; }) == 0));
	assert((convex_min(ra{2, 5}, [](auto x) { return x * x; }) == 2));
	assert(
	    (convex_min(ra{-3, 5}, [](auto x) { return x * x - 4 * x; }) == 2));
}
/*! Convex-hull trick. This can be used to find the minimum of a set of
 * lines at various points. */
struct cht {
	vector<pt> h; //!< The lines, specified as (a,b) for ax+b.
	explicit cht(vector<pt> v) {
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
void test_hull() {
	vector<pt> lines{{1, 2}, {4, -2}, {-1, 3}, {1, 3}, {-4, 2}, {3, 4}};
	vector<pt> exp{lines[1], lines[2], lines[4], lines[5]};
	auto h = hull(lines);
	sort(al(h));
	dbg(h);
	sort(al(exp));
	dbg(exp);
	assert(h == exp);
}
void test_cht() {
	vector<pt> lines{{1, 2}, {4, -2}, {-1, 3}, {1, 3}, {-4, 2}, {3, 4}};
	cht ch{lines};
	fo(x, -1000, 1000) {
		ll mn = inf;
		for (const auto line : lines) {
			mn = min(mn, dot(line, pt{x, 1}));
		}
		assert(ch.min(x) == mn);
	}
}
void test_geometry() {
	test_dot();
	test_wedge();
	test_ccw();
	test_less();
	test_convex_min();
	test_hull();
	test_cht();
}
} // namespace geometry
using namespace geometry;

#pragma once
#include "core.hpp"
namespace std {
bool operator<(point const &a, point const &b) {
	/*! Compare points a and b lexicographically*/
	return key_compare([](auto x) { return tuple{real(x), imag(x)}; })(a, b);
}
} // namespace std
namespace geometry {
void test_less() {
	assert((point{1, 2} < point{3, 5}));

	assert((point{1, 2} < point{3, 1}));

	assert((point{1, 1} < point{1, 2}));

	assert((!(point{1, 2} < point{1, 1})));

	assert((!(point{1, 2} < point{1, 2})));
}
// TODO generalize these products for multidimensional vectors
auto dot(point const &a, point const &b) {
	/*! returns the dot product of 2D vectors a and b, i.e. \f$a \cdot
	 * b\f$*/
	return real(conj(a) * b);
}
void test_dot() {
	assert((dot({1, 2}, {2, 5}) == 1 * 2 + 2 * 5));
	assert((dot({0, 2}, {3, 0}) == 0 * 3 + 2 * 0));
}
auto wedge(point const &a, point const &b) {
	/*! Returns the wedge product of 2D vectors a and b, \f$a \wedge b\f$.
	 * This is the signed area of the parallelogram spanned by vectors
	 * \f$\vec{f}\f$ and \f$\vec{b}\f$.*/
	return imag(conj(a) * b);
}
void test_wedge() {
	assert((wedge({1, 0}, {0, 1}) == 1));
	assert((wedge({1, 1}, {1, 1}) == 0));
	assert((wedge({1, 0}, {0, 0}) == 0));
}
auto area(const point &a, const point &b, const point &c) {
	return wedge(b - a, c - a);
}
/**
 * @brief Returns whether moving through \f$a \rightarrow b \rightarrow c\f$
	 * is counterclockwise. @throw std::invalid_argument if a, b, c are
	 * collinear and distinct.
 * 
 * @param a 
 * @param b 
 * @param c 
 * @return bool true if counterclockwise, false otherwise.
 */
bool ccw(const point &a, const point &b, const point &c) {
	ll area_pts = area(a, b, c);
	if (!(a == b || a == c || b == c || w)) {
		throw invalid_argument{"Points are collinear."};
	}
	return area_pts > 0;
}
void test_ccw() {
	assert((ccw({1, 0}, {1, 1}, {0, 1})));
	assert((!ccw({0, 1}, {1, 1}, {1, 0})));
	auto test_collinear = [&](point a, point b, point c) {
		try {
			ccw(a, b, c);
		} catch (invalid_argument &) {
			return;
		}
		assert(false);
	};
	test_collinear({0, 1}, {0, 2}, {0, -1});
	test_collinear({2, 0}, {-3, 0}, {4, 0});
	test_collinear({4, 6}, {6, 9}, {-4, -6});
}
auto hull(vector<point> v, df(do_sort, true)) {
	// TODO why do_sort?
	/*! Returns the convex hull of the points in v*/
	vector<point> h;
	if (do_sort) {
		const auto p = *min_element(al(v), key_compare([](point a) { return tuple{imag(a), real(a)}; }));
		sort(al(v), bind(ccw, p, _1, _2));
		h.push_back(p);
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
	vector<point> lines; //!< The lines, specified as (a,b) for ax+b.
	explicit cht(vector<point> v) {
		v = uniq(v, key_compare(lambda(imag), equal_to{}), key_compare(lambda(conj)));
		lines = hull(v, false);
	}
	auto min(ll x) {
		/*! Minimum value of the lines at x*/
		auto const eval = [&](const auto &i) {
			return real(lines[i]) * x + imag(lines[i]);
		};
		return eval(convex_min(ra{size(lines) - 1}, eval));
	}
};
void test_hull() {
	vector<point> lines{{1, 2}, {4, -2}, {-1, 3}, {1, 3}, {-4, 2}, {3, 4}};
	vector<point> exp{lines[1], lines[2], lines[4], lines[5]};
	auto h = hull(lines);
	sort(al(h));
	sort(al(exp));
	assert(h == exp);
}
void test_cht() {
	vector<point> lines{{1, 2}, {4, -2}, {-1, 3}, {1, 3}, {-4, 2}, {3, 4}};
	cht ch{lines};
	fo(x, -1000, 1000) {
		ll mn = inf;
		for (const auto line : lines) {
			mn = min(mn, dot(line, point{x, 1}));
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

#pragma once
#include "core/all.hpp"
namespace std {
bool operator<(point const &a, point const &b) {
	/*! Compare points a and b lexicographically*/
	return key_compare([](auto x) { return tuple{real(x), imag(x)}; })(a, b);
}
} // namespace std
inline namespace convex_hull_trick {
// TODO generalize these products for multidimensional vectors
auto dot(point const &a, point const &b) {
	/*! returns the dot product of 2D vectors a and b, i.e. \f$a \cdot
	 * b\f$*/
	return real(conj(a) * b);
}
auto wedge(point const &a, point const &b) {
	/*! Returns the wedge product of 2D vectors a and b, \f$a \wedge b\f$.
	 * This is the signed area of the parallelogram spanned by vectors
	 * \f$\vec{f}\f$ and \f$\vec{b}\f$.*/
	return imag(conj(a) * b);
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
	if (!(a == b || a == c || b == c || area_pts)) {
		throw invalid_argument{"Points are collinear."};
	}
	return area_pts > 0;
}
auto hull(vector<point> v, bool do_sort = true) {
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
/*! Convex-hull trick. This can be used to find the minimum of a set of
 * lines at various points. */
struct CHT {
	vector<point> lines; //!< The lines, specified as (a,b) for ax+b.
	explicit CHT(vector<point> v) {
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
} // namespace convex_hull_trick

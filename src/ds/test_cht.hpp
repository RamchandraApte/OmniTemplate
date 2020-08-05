#pragma once
#include "cht.hpp"
namespace convex_hull_trick::test {
void test_less() {
	assert((point{1, 2} < point{3, 5}));
	assert((point{1, 2} < point{3, 1}));
	assert((point{1, 1} < point{1, 2}));
	assert((!(point{1, 2} < point{1, 1})));
	assert((!(point{1, 2} < point{1, 2})));
}
void test_dot() {
	assert((dot({1, 2}, {2, 5}) == 1 * 2 + 2 * 5));
	assert((dot({0, 2}, {3, 0}) == 0 * 3 + 2 * 0));
}
void test_wedge() {
	assert((wedge({1, 0}, {0, 1}) == 1));
	assert((wedge({1, 1}, {1, 1}) == 0));
	assert((wedge({1, 0}, {0, 0}) == 0));
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
void test_convex_min() {
	assert((convex_min(ra{-100, 100}, [](auto x) { return x * x + x; }) == 0));
	assert((convex_min(ra{2, 5}, [](auto x) { return x * x; }) == 2));
	assert((convex_min(ra{-3, 5}, [](auto x) { return x * x - 4 * x; }) == 2));
}
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
	CHT ch{lines};
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
} // namespace convex_hull_trick::test
using namespace convex_hull_trick::test;

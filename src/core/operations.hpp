#pragma once
#include "range.hpp"
// namespace operations {
#define aug(op)                                                                                    \
	template <typename T1, typename T2> auto operator op##=(T1 &a, const T2 &b) {              \
		return a = a op b;                                                                 \
	}
aug(+);
aug(-);
aug(*);
aug(/);
template <typename T> enable_if_t<is_floating_point_v<T>, T> invert(multiplies<>, const T &x) {
	return 1 / x;
}
template <typename Group> Group operator/(Group const &a, Group const &b) {
	return a * invert(multiplies{}, b);
}
template <typename T1, typename T2> auto constexpr operator-(const T1 &a, const T2 &b) {
	return a + -b;
}
template <typename T1, typename T2> auto constexpr operator!=(const T1 &a, const T2 &b) {
	return !(a == b);
}
template <typename T1, typename T2> auto operator<=(const T1 &a, const T2 &b) { return !(b < a); }
template <typename T1, typename T2> auto operator>=(const T1 &a, const T2 &b) { return b <= a; }
template <typename T1, typename T2> auto operator>(const T1 &a, const T2 &b) { return b < a; }
unordered_map<ll, ll> operator+(unordered_map<ll, ll> a, unordered_map<ll, ll> const &b) {
	for (const auto &p : b) {
		a[p.first] += p.second;
	}
	return a;
}
/**
 * @brief Returns union of sets a and b.
 *
 * @param a p_a:...
 * @param b p_b:...
 * @return the union of sets a and b
 */
template <typename T> auto operator|(unordered_set<T> const &a, unordered_set<T> const &b) {
	const auto &[sm, bg] = minmax(a, b);
	auto ret = bg;
	ret.insert(al(sm));
	return ret;
};
template <typename T> auto operator&(unordered_set<T> const &a, unordered_set<T> const &b) {
	const auto &[sm, bg] = minmax(a, b);
	unordered_set<T> ret;
	for (const auto &x : sm) {
		if (bg.count(x)) {
			ret.insert(x);
		}
	}
	return ret;
}
template <typename T>
auto sub_set(unordered_set<T> const &a, unordered_set<T> const &b, unordered_set<T> &ret) {
	for (const auto &x : a) {
		if (!b.count(x)) {
			ret.insert(x);
		}
	}
	return ret;
}
template <typename T> auto operator-(unordered_set<T> const &a, unordered_set<T> const &b) {
	unordered_set<T> ret;
	return sub_set(a, b, ret);
}
template <typename T> auto operator^(unordered_set<T> const &a, unordered_set<T> const &b) {
	unordered_set<T> ret = a - b;
	sub_set(b, a, ret);
	return ret;
}
template <typename T> auto operator*(vector<T> a, vector<T> b) {
	assert(a.size() == b.size());
	vector<T> c(a.size());
	fo(i, a.size()) { c[i] = a[i] * b[i]; }
	return c;
}
template <typename Iterator>
auto operator+(Iterator it,
	       enable_if_t<!is_same<typename iterator_traits<decltype(it)>::iterator_category,
				    random_access_iterator_tag>::value,
			   ll>
		   n) {
	advance(it, n);
	return it;
}
/** @brief Expands to a functor type that calls func */
#define FUNCTOR(func)                                                                              \
	struct {                                                                                   \
		template <typename... Ts> decltype(auto) operator()(Ts &&... args) const {         \
			return (func)(forward<decltype(args)>(args)...);                           \
		}                                                                                  \
	}
using Max = FUNCTOR(max);
using Min = FUNCTOR(min);
ll identity(plus<>, ll) { return 0; }
ll identity(multiplies<>, ll) { return 1; }
ll identity(Max, ll) { return -inf; }
ll identity(Min, ll) { return inf; }
// TODO convert all macros to UPPER_CASE
//} // namespace operations
// using namespace operations;

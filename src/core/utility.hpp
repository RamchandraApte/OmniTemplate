#pragma once
#include "range.hpp"
namespace utility {
/*! Sets v to new_ temporary while with object is alive */
template <typename T> struct [[nodiscard]] with {
	T old; //!< Original value of the variable
	T &v;  //!< Reference to variable
	template <typename Tp> with(const Tp new_, T &v_) : old(v_), v(v_) { v = new_; }
	~with() { v = old; }
};
/*! Helper for lambda recursive functions. The recursive function is
* passed to Func as the first argument.*/
template <typename Func> struct fix {
	Func func;
	fix(const Func &func_) : func(func_) {}
	template <typename... Args> decltype(auto) operator()(Args &&... args) const { return func(this, forward<Args>(args)...); }
};
#define lambda(f) [](auto &&... args) { return f(forward<decltype(args)>(args)...); }
template <typename T> auto max_eq(T &x, const T &y) { x = max(x, y); }
template <typename T> auto min_eq(T &x, const T &y) { x = min(x, y); }
template <typename T> auto cache(const T &f) {
	/*! Cache calls to f using a map of type T*/
	T ch;
	return [=](const auto &arg) mutable {
		if (ch.find(arg) == end(ch)) {
			return ch[arg] = f(arg);
		}
		return ch[arg];
	};
}
/*! Remove all duplicates element from v so that all elements in v are
	 * distinct and sorted */
template <typename Eq = equal_to<>, typename T = less<>, typename Cont>
[[nodiscard]] auto uniq(Cont v, Eq const &up = Eq{}, T const &sp = T{}) {
	sort(al(v), sp);
	v.resize(unique(al(v), up) - begin(v));
	return v;
}
template <typename T = less<>, typename Func> auto key_compare(const Func &f, T g = T{}) {
	return [=](auto &&... args) -> decltype(auto) { return g(f(forward<decltype(args)>(args))...); };
}
template <typename T> auto prev_less(const T &v) {
	ll n = v.size();
	vl l(n, -1);
	stack<ll> s;
	fo(i, n) {
		while (s.size() && !(s.top() < v[i])) {
			s.pop();
		}
		if (s.size()) {
			l[i] = s.top();
		}
		s.push(v[i]);
	}
	return l;
}
ll bit_ceil(ll x) {
	/*! Return the smallest power of two that is at least x*/
	if (x <= 1) {
		return 1;
	}
	return 1LL << (sizeof(ll) * CHAR_BIT - __builtin_clzll(x - 1));
}
ll power_ceil(const ll x, const ll base) {
	ll pw = 1;
	for (; pw < x; pw *= base)
		;
	return pw;
}
ll log_ceil(const ll x, const ll base) {
	ll pw = 1, cnt = 0;
	for (; pw < x; pw *= base, ++cnt) {
	}
	return cnt;
}
[[nodiscard]] ll next_comb(ll x) {
	/*! Formally, returns the smallest integer y > x such that popcount(y) =
	 * popcount(x). Note, such y must exist. */
	ll tz = __builtin_ctzll(x);
	ll y = x + (ll{1} << tz);
	const auto ret = y | (y ^ x) >> (2 + tz);
	assert(ret > x);
	assert(__builtin_popcountll(ret) == __builtin_popcountll(x));
	return ret;
}
template <typename T, typename Func> void swap2(T &a, T &b, const Func &func) {
	/*! Stable sorts a and b by func.*/
	if (func(a) > func(b)) {
		swap(a, b);
	}
}
template <typename Cont> ll ssize(const Cont &cont) { return size(cont); }
// TODO split up utility.hpp maybe?
/*! @brief Array convenience template. Converts C style array type to std::array type. */
template <typename T> struct ar { using type = T; };
template <typename T> using ar_t = typename ar<T>::type;
template <typename T, ll n> struct ar<T[n]> { using type = array<ar_t<T>, n>; };
struct random_device_patch {
	/*! Random device patch to fix libstdc++'s broken implementation on
	 * Windows*/
	unsigned int operator()() { return clock_::now().time_since_epoch().count(); }
	double entropy() { return 0.0; }
};
struct Empty {};
#define USE_RANDOM_DEVICE_PATCH
#ifdef USE_RANDOM_DEVICE_PATCH
using random_device = random_device_patch;
#endif
default_random_engine reng{random_device{}()};
} // namespace utility
using namespace utility;

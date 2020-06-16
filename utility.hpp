#pragma once
#include "range.hpp"
namespace utility {
template <typename T> struct [[nodiscard]] with {
	/*! Sets v to new_ temporary while with object is alive */
	T old; //!< Original value of the variable
	T &v;  //!< Reference to variable
	template <typename Tp> with(const Tp new_, T &v_) : old(v_), v(v_) { v = new_; }
	~with() { v = old; }
};
void test_with() {
	ll var = 12;
	auto inner_func = [&] {
		with _w(23, var);
		assert(var == 23);
		var = 45;
	};
	inner_func();
	assert(var == 12);
}
template <typename Func> struct fix {
	/*! Helper for lambda recursive functions. The recursive function is
	 * passed to Func as the first argument.*/
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
template <typename Eq = equal_to<>, typename T = less<>, typename Cont>
[[nodiscard]] auto uniq(Cont v, Eq const &up = Eq{}, T const &sp = T{}) {
	/*! Remove all duplicates element from v so that all elements in v are
	 * distinct and sorted */
	sort(al(v), sp);
	v.resize(unique(al(v), up) - begin(v));
	return v;
}
void test_uniq() {
	assert((uniq(vl{2, -1, 3, -1, 2, 3}) == vl{-1, 2, 3}));
	assert((uniq<equal_to<>, greater<>>(vl{1, -3, 5}) == vl{5, 1, -3}));
}
template <typename T = less<>, typename Func> auto key_compare(const Func &f, T g = T{}) {
	return [=](auto &&... args) -> decltype(auto) { return g(f(forward<decltype(args)>(args))...); };
}
void test_key_compare() {
	vl a{24, 25};
	assert(key_compare<greater<>>([&](ll i) { return a[i]; })(1, 0));
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
size_t bit_ceil(size_t x) {
	/*! Return the smallest power of two that is at least x*/
	if (x <= 1) {
		return 1;
	}
	return 1ULL << (sizeof(size_t) * CHAR_BIT - __builtin_clzll(x - 1));
}
void test_bit_ceil() {
	assert(bit_ceil(0) == 1);
	assert(bit_ceil(1) == 1);
	assert(bit_ceil(2) == 2);
	assert(bit_ceil(3) == 4);
	assert(bit_ceil(4) == 4);
	assert(bit_ceil(5) == 8);
	assert(bit_ceil((1LL << 45) - 100) == 1LL << 45);
	assert(bit_ceil((1LL << 45)) == 1LL << 45);
}
size_t base_ceil(const size_t x, const size_t base) {
	ll pw = 1;
	for (; pw < x; pw *= base)
		;
	return pw;
}
size_t ceil_log(const size_t x, const size_t base) {
	ll pw = 1, cnt = 0;
	for (; pw < x; pw *= base, ++cnt) {
	}
	return cnt;
}
[[nodiscard]] ll next_comb(ll x) {
	/*! Formally, returns the smallest integer y > x such that popcount(y) =
	 * popcount(x). Note, such y must exist. */
	// Uses algorithm from some blog online, I think
	// TODO credit author
	ll tz = __builtin_ctzll(x);
	ll y = x + (ll{1} << tz);
	const auto ret = y | (y ^ x) >> (2 + tz);
	assert(ret > x);
	assert(__builtin_popcountll(ret) == __builtin_popcountll(x));
	return ret;
}
void test_next_comb() {
	ll x = 0b111;
	x = next_comb(x);
	assert(x == 0b1011);
	x = next_comb(x);
	assert(x == 0b1101);
	x = next_comb(x);
	assert(x == 0b1110);
	x = 0b1;
	x = next_comb(x);
	assert(x == 0b10);
	x = next_comb(x);
	assert(x == 0b100);
}
template <typename T, typename Func> void swap2(T &a, T &b, const Func &func) {
	/*! Stable sorts a and b by func.*/
	if (func(a) > func(b)) {
		swap(a, b);
	}
}
tm() struct ar { using type = T; };
tm() using ar_t = typename ar<T>::type;
template <typename T, size_t n> struct ar<T[n]> {
	using type = array<ar_t<T>, n>;
};
void test_ar() {
	using std::is_same_v; // FIXME
	static_assert(is_same_v<ar_t<ll[2][3]>, array<array<ll, 3>, 2>>);
	static_assert(is_same_v<ar_t<array<ll, 200>[2][3]>,
				array<array<array<ll, 200>, 3>, 2>>);
}
struct random_device_patch {
	/*! Random device patch to fix libstdc++'s broken implementation on
	 * Windows*/
	unsigned int operator()() {
		return clock_::now()
		    .time_since_epoch()
		    .count(); // TODO Probably random enough, but could be
			      // improved?
	}
	double entropy() { return 0.0; }
};
// TODO test this macro on codeforces
#ifdef __MINGW32__
using random_device = random_device_patch;
#endif
default_random_engine reng{std::random_device{}()};
void test_utility() {
	test_with();
	test_uniq();
	test_next_comb();
	test_ar();
	test_bit_ceil();
	test_key_compare();
}
} // namespace utility
using namespace utility;

#pragma once
#include "core.hpp"
struct with {
	/*! Sets v to new_ temporary while with object is alive */
	ll old; //!< Original value of the variable
	ll &v;	//!< Reference to variable
	with(ll new_, ll &v_) : old(v_), v(v_) { v = new_; }
	~with() { v = old; }
};
template <typename Func> struct fix {
	/*! Helper for lambda recursive functions. The recursive function is
	 * passed to Func as the first argument.*/
	Func func;
	fix(const Func &func_) : func(func_) {}
	template <typename... Ts> auto operator()(Ts &&... args) const {
		return func(this, forward<decltype(args)>(args)...);
	}
};
#define lambda(f) [&](auto... args) { return f(args...); }
template <typename T> auto maxeq(T &&x, const T &y) { x = max(x, y); }
template <typename T> auto mineq(T &&x, const T &y) { x = min(x, y); }
template <typename T> auto cache(const T &f) {
	/*! Cache calls to f using a map of type T*/
	T ch;
	return [=](const auto &arg) mutable {
		if (ch.find(arg) == end(ch)) {
			ch[arg] = f(arg);
		}
		return ch[arg];
	};
}
// TODO why doesn't [[nodiscard]] generated a compiler warning?
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
template <typename T = less<>, typename Func>
auto map_args(const Func &f, T g = T{}) {
	return [&](const auto &... args) { return g(f(args)...); };
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
auto nx2(ll x) { return ll(1LL) << ll(ceil(log2(lli(x)))); }
[[nodiscard]] ll next_comb(ll x) {
	/*! Formally, returns the smallest integer y > x such that popcount(y) =
	 * popcount(x). Note, such y must exist. */
	// Uses algorithm from some blog online, I think
	ll tz = __builtin_ctzll(x);
	ll y = x + (ll{1} << tz);
	const auto ret = y | (y ^ x) >> (2 + tz);
	assert(ret > x);
	assert(__builtin_popcountll(ret) == __builtin_popcountll(x));
	return ret;
}
void test_comb() {
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
tm() struct ar { using type = T; };
tm() using ar_t = typename ar<T>::type;
template <typename T, size_t n> struct ar<T[n]> {
	using type = array<ar_t<T>, n>;
};

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
using default_random_device = random_device_patch;
default_random_engine reng{default_random_device{}()};
void test_utility() {
	test_uniq();
	test_comb();
}

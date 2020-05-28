#pragma once
#include "core.hpp"
struct with {
	/*! Sets v to new_ temporary while with object is alive */
	ll old;
	ll &v;
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
template <typename Eq = equal_to<>, typename T = less<>, typename Cont>
auto uniq(Cont &v, Eq const &up = Eq{}, T const &sp = T{}) {
	/*! Remove all duplicates element from v so that all elements in v are
	 * distinct and sorted */
	sort(al(v), sp);
	v.resize(unique(al(v), up) - begin(v));
	return v;
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
ll next_comb(ll x) {
	ll tz = __builtin_ctz(x);
	ll y = x + (ll{1} << tz);
	return y | (y ^ x) >> (2 + tz);
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
		    .count(); // Probably random enough
	}
	double entropy() { return 0.0; }
};
using default_random_device = random_device_patch;
default_random_engine reng{default_random_device{}()};

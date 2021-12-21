#pragma once
#include "range.hpp"
namespace utility {
/*! @brief Sets v to new_ temporary while with object is alive */
template <typename T> struct [[nodiscard]] with {
	T old; //!< Original value of the variable
	T &v;  //!< Reference to variable
	template <typename Tp> with(const Tp new_, T &v_) : old(v_), v(v_) { v = new_; }
	~with() { v = old; }
};
/*! @brief Helper for lambda recursive functions. The recursive function is
 * passed to Func as the first argument.*/
template <typename Func> struct fix {
	Func func;
	fix(const Func &func_) : func(func_) {}
	template <typename... Args> decltype(auto) operator()(Args &&... args) const {
		return func(*this, forward<Args>(args)...);
	}
};
#define LAMBDA_IMPL(f)                                                                             \
	(auto &&...args)->decltype(auto) { return f(forward<decltype(args)>(args)...); }
#define LAMBDA(f) [&] LAMBDA_IMPL(f)
#define LAMBDA_THIS(f) [&, this ] LAMBDA_IMPL(f)
#define DEFINE_FUNC_EQ(func)                                                                       \
	template <typename T> void func##_eq(T &x, const T &y) { x = func(x, y); }                 \
/*! @brief Set x to the minimum of x and y*/
DEFINE_FUNC_EQ(min);
/*! @brief Set x to the maximum of x and y */
DEFINE_FUNC_EQ(max);
/*! @brief Cache calls to f using a map of type T*/
template <typename T> auto cache(const T &f) {
	T ch;
	return [=](const auto &arg) mutable {
		if (ch.find(arg) == end(ch)) {
			return ch[arg] = f(arg);
		}
		return ch[arg];
	};
}
/** @brief Remove all duplicates element from \param v so that all elements in \param v are
 * distinct and sorted */
template <typename Eq = equal_to<>, typename T = less<>, typename Cont>
[[nodiscard]] auto uniq(Cont v, Eq const &up = Eq{}, T const &sp = T{}) {
	sort(al(v), sp);
	v.resize(unique(al(v), up) - begin(v));
	return v;
}
/** @brief Compare using key.
 * @param func The key function
 * @param compare the comparison function.
 * @returns A comparison functor that compares two arguments by the key.
 */
template <typename Compare = less<>, typename Func>
auto key_compare(const Func &func, const Compare &compare = {}) {
	return [=](auto &&... args) -> decltype(auto) {
		return compare(func(forward<decltype(args)>(args))...);
	};
}
template <typename T> auto prev_less(const T &v) {
	ll n = v.size();
	vector<ll> l(n, -1);
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
/** @brief Return the smallest power of two that is at least x*/
ll bit_ceil(ll x) {
	if (x <= 1) {
		return 1;
	}
	return 1LL << (sizeof(ll) * CHAR_BIT - __builtin_clzll(x - 1));
}
// TODO: power_ceil for base 2
/*! @brief Returns the smallest power of base that is at least x*/
ll power_ceil(const ll x, const ll base) {
	ll pw = 1;
	for (; pw < x; pw *= base)
		;
	return pw;
}
/*! @brief Returns the smallest exponent such that base raised to exponent is at least x*/
ll log_ceil(const ll x, const ll base) {
	ll pw = 1, cnt = 0;
	for (; pw < x; pw *= base, ++cnt)
		;
	return cnt;
}
/** @brief next combination of bits
 * Formally, returns the smallest integer y > x such that popcount(y) = popcount(x).
 * @pre The desired y must exist. */
[[nodiscard]] ll next_comb(ll x) {
	ll tz = __builtin_ctzll(x);
	ll y = x + (ll{1} << tz);
	const auto ret = y | (y ^ x) >> (2 + tz);
	assert(ret > x);
	assert(__builtin_popcountll(ret) == __builtin_popcountll(x));
	return ret;
}
/** @brief Identity functor. */
class IdentityFunctor {
      public:
	template <typename T> decltype(auto) operator()(T &&x) const { return std::forward<T>(x); }
};

/** @brief Stable sorts a and b by func.*/
template <typename T, typename Func = IdentityFunctor>
void sort2(T &a, T &b, const Func &func = {}) {
	if (func(a) > func(b)) {
		swap(a, b);
	}
}
/** @brief performs a counting sort, comparing elements x,y using proj(x) < proj(y)*/
template <typename Iter, typename Proj>
void counting_sort(Iter a, Iter b, const Proj &proj, const ll proj_size) {
	range rang{a, b};
	vector<ll> count(proj_size);
	for (const auto &x : rang) {
		++count[proj(x)];
	}
	ll sum = 0;
	for (auto &cnt : count) {
		const auto old_cnt = cnt;
		cnt = sum;
		sum += old_cnt;
	}
	vector<typename Iter::value_type> output(b - a);
	for (const auto &x : rang) {
		output[count[proj(x)]] = x;
		++count[proj(x)];
	}
	move(al(output), a);
}
// TODO split up utility.hpp maybe?
/*! @brief Array convenience template. Converts C style array type to std::array type. */
template <typename T> struct ar { using type = T; };
template <typename T> using ar_t = typename ar<T>::type;
template <typename T, ll n> struct ar<T[n]> { using type = array<ar_t<T>, n>; };
/** @brief  Random device patch to fix libstdc++'s broken implementation on Windows*/
struct random_device_patch {
	unsigned int operator()() { return clock_::now().time_since_epoch().count(); }
	double entropy() { return 0.0; }
};
struct Empty {};
#define USE_RANDOM_DEVICE_PATCH
#ifdef USE_RANDOM_DEVICE_PATCH
using random_device = random_device_patch;
#endif
default_random_engine reng{random_device{}()};
template <typename Compare = less<>> class chained_compare {
      public:
	chained_compare(const Compare &comp_ = {}) : comp{comp_} {}
	template <typename T1, typename T2, typename... Ts>
	bool operator()(const T1 &arg1, const T2 &arg2, const Ts &...args) {
		return comp(arg1, arg2) && (*this)(arg2, args...);
	}
	template <typename T1> bool operator()(const T1 &arg1) { return true; }

      private:
	Compare comp;
};
/*! @brief Return whether idx is a valid index for vec. Note that if idx is negative this returns
 * false.*/
template <typename T> bool valid_idx(const vector<T> &vec, const size_t idx) {
	return idx < vec.size();
}
template <typename InputIt> auto iterator_identity() {
	return identity_elt(plus<>{}, typename InputIt::value_type{});
};
template <typename InputIt> decltype(auto) accumulate(InputIt a, InputIt b) {
	return accumulate(a, b, iterator_identity<InputIt>());
}
template <typename InputIt> decltype(auto) inner_product(InputIt a, InputIt b, InputIt c) {
	return inner_product(a, b, c, iterator_identity<InputIt>());
}
template <typename InputIt, typename Op = plus<>>
auto get_partial_sum(InputIt a, InputIt b, const Op &op = {}) {
	vector sums(distance(a, b) + 1, identity_elt(op, typename InputIt::value_type{}));
	partial_sum(a, b, begin(sums) + 1, op);
	return sums;
}
template <typename... Ts> decltype(auto) read(Ts &...args) { return (std::cin >> ... >> args); }
} // namespace utility
using namespace utility;

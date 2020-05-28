#pragma once
#ifndef PRE
//#if defined(__GNUC__) && !defined(__clang__)
#if 0
#define REALGCC
#endif
#ifdef REALGCC
#include <bits/extc++.h>
#else
#include <bits/stdc++.h>
#endif
#include <experimental/iterator>
#include <experimental/source_location>
#endif
#ifdef LOCAL
#define dbg(x) (++depth, debug(x, #x##s))
#else
#define NDEBUG
#define dbg(x) (x)
#endif
#if 0
#define BEGIN_NS namespace {
#define END_NS }
#else
#define BEGIN_NS
#define END_NS
#endif
#define fo(i, ...) for ([[maybe_unused]] auto i : ra{__VA_ARGS__})
#define fr(i, ...) for ([[maybe_unused]] auto i : rev(ra{__VA_ARGS__}))
#define tp decltype
#define tm(...) template <typename __VA_ARGS__ T>
#define this (*this)
#define al(v) begin(v), end(v)
#define I(x)                                                                   \
	ll x;                                                                  \
	cin >> x;
#define pb push_back
#define vc vector
bool debug_mode = false;
//#define rel_assert(msg) if constexpr(debug_mode){static_assert(false, msg);}
#define rel_assert(...)
#define WARN(msg)                                                              \
	[[deprecated(msg)]] auto warn = []() { rel_assert(msg); };             \
	warn();
//#define TODO(msg) WARN("TODO: " msg)
#define TODO(msg)
#define paste2(x, y) x##y
#define paste(x, y) paste2(x, y)
#define lets_count lets_add paste(_l, __COUNTER__)
#define let(a, ...)                                                            \
	using a = __VA_ARGS__;                                                 \
	lets_count{#__VA_ARGS__, #a};
#define import(a)                                                              \
	using namespace a;                                                     \
	lets_count{#a "::", ""};
#define df(x, v) remove_const_t<tp(v)> x = v
using namespace std;
BEGIN_NS
#define ostream auto
vector<pair<string, string>> lets{{"__debug::", ""},
				  {"const ", ""},
				  {"__cxx11::basic_string<char>", "string"}};
struct lets_add {
	lets_add(const string &a, const string &b) { lets.pb({a, b}); }
};
#ifdef REALGCC
import(__gnu_pbds);
using __gnu_cxx::power;
#endif
using std::priority_queue;
import(std);
import(experimental);
import(chrono);
import(literals);
import(placeholders) let(lli, long long);
let(ull, unsigned long long);
#include "my_int.hpp"
let(vl, vector<ll>);
let(ld, long double) let(pr, pair<ll, ll>);
let(com, complex<double>);
let(pt, complex<ll>);
let(ull, unsigned long long);
using bt = bitset<numeric_limits<ll>::digits>;
tm() using pq = std::priority_queue<T, vector<T>, greater<>>;
let(clock_, high_resolution_clock);
import(this_thread);
let(um, unordered_map<ll, ll>);
BEGIN_NS
#ifdef REALGCC
template <typename T, typename V = null_type>
using omap = tree<T, V, less<>, rb_tree_tag, tree_order_statistics_node_update>;
#endif
END_NS

auto constexpr inf = ll(numeric_limits<ll>::max()) / 8; /*!< Infinity */
auto const delim = ", "s; /*!< Delimiter for debug output */
auto constexpr tau = 2 * 3.1415926535897932384626433L; /*!< Pi */
bool multitest = false;

#include "io.hpp"
BEGIN_NS
#include "operations.hpp"
#include "range.hpp"
#include "debug.hpp"
#include "utility.hpp"

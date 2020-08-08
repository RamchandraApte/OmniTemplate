#pragma once
/*! Contains core files for the template*/
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
#define fo(i, ...) for ([[maybe_unused]] const auto i : ra{__VA_ARGS__})
#define fr(i, ...) for ([[maybe_unused]] const auto i : rev(ra{__VA_ARGS__}))
#define this (*this)
#define al(v) begin(v), end(v)
#define I(x)                                                                   \
	ll x;                                                                  \
	cin >> x;
#define pb push_back
#define vc vector
bool debug_mode = false;
//#define rel_assert(msg) if constexpr(debug_mode){static_assert(false, msg);}
#define rel_assert(...) s
#define WARN(msg)                                                              \
	[[deprecated(msg)]] auto warn = []() { rel_assert(msg); };             \
	warn();
#define TODO(msg) WARN("TODO: " msg)
#define paste2(x, y) x##y
#define paste(x, y) paste2(x, y)
#define lets_count lets_add paste(_l, __COUNTER__)
#define let(a, ...)                                                            \
	using a = __VA_ARGS__;                                                 \
	lets_count{#__VA_ARGS__, #a};
#define import(a)                                                              \
	using namespace a;                                                     \
	lets_count{#a "::", ""};
#define df(x, v) remove_const_t<decltype(v)> x = v
using namespace std;
vector<pair<string, string>> lets{{"__debug::", ""},
				  {"const ", ""},
				  {"__cxx11::basic_string<char>", "string"}};
struct lets_add {
	lets_add(const string &a, const string &b) { lets.push_back({a, b}); }
};
#ifdef REALGCC
import(__gnu_pbds);
using __gnu_cxx::power;
#endif
using std::priority_queue;
import(std);
// import(experimental);
using experimental::make_ostream_joiner;
using experimental::ostream_joiner;
using experimental::source_location;
import(chrono);
import(literals);
import(placeholders) let(lli, long long);
let(ull, unsigned long long);
let(ll, long long);
let(vl, vector<ll>);
let(ld, long double) let(pr, pair<ll, ll>);
let(com, complex<double>);
let(point, complex<ll>);
let(ull, unsigned long long);
using bt = bitset<numeric_limits<ll>::digits>;
template <typename T, typename Comp>
using prio_queue_t = std::priority_queue<T, vector<T>, Comp>;
let(clock_, high_resolution_clock);
import(this_thread);
let(um, unordered_map<ll, ll>);

#ifdef REALGCC
template <typename T, typename V = null_type>
using order_stat_map =
    tree<T, V, less<>, rb_tree_tag, tree_order_statistics_node_update>;
#endif

auto constexpr inf = ll(numeric_limits<ll>::max()) / 8; /*!< Infinity */
auto const delim = ", "s; /*!< Delimiter for debug output */
auto constexpr tau = 2 * 3.1415926535897932384626433L; /*!< Pi */
extern bool multitest;

#include "io.hpp"
#include "debug.hpp"
#include "operations.hpp"
#include "range.hpp"
#include "utility.hpp"

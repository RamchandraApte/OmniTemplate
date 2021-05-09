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
#if 0
#include <algorithm>
#include <cassert>
#include <chrono>
#include <climits>
#include <complex>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#endif
//#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <complex>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <thread>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>
#endif
#include <experimental/iterator>
#include <experimental/source_location>
#endif // PRE
#define fo(i, ...) for ([[maybe_unused]] const auto i : ra{__VA_ARGS__})
#define fr(i, ...) for ([[maybe_unused]] const auto i : rev(ra{__VA_ARGS__}))
#define al(v) begin(v), end(v)
bool debug_mode = false;
//#define rel_assert(msg) if constexpr(debug_mode){static_assert(false, msg);}
#define rel_assert(...) s
#define WARN(msg)                                                                                  \
	[[deprecated(msg)]] auto warn = []() { rel_assert(msg); };                                 \
	warn();
#define TODO(msg) WARN("TODO: " msg)
#define paste2(x, y) x##y
#define paste(x, y) paste2(x, y)
#define lets_count lets_add paste(_l, __COUNTER__)
#define let(a, ...)                                                                                \
	using a = __VA_ARGS__;                                                                     \
	lets_count{#__VA_ARGS__, #a};
#define import(a)                                                                                  \
	using namespace a;                                                                         \
	lets_count{#a "::", ""};
#ifndef DEBUG
#define cerr()                                                                                     \
	if (false)                                                                                 \
	cerr
#endif
using namespace std;
vector<pair<string, string>> lets{
    {"__debug::", ""}, {"const ", ""}, {"__cxx11::basic_string<char>", "string"}};
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
import(placeholders) let(ull, unsigned long long);
// TODO move this to abbrev.hpp
let(ll, long long);
let(ld, long double);
let(pr, pair<ll, ll>);
let(com, complex<double>);
let(point, complex<ll>);
let(ull, unsigned long long);
template <typename T, typename Comp> using prio_queue_t = std::priority_queue<T, vector<T>, Comp>;
let(clock_, high_resolution_clock);
import(this_thread);

#ifdef REALGCC
template <typename T, typename V = null_type>
using order_stat_map = tree<T, V, less<>, rb_tree_tag, tree_order_statistics_node_update>;
#endif

constexpr auto inf = ll(numeric_limits<ll>::max()) / 8; /*!< Infinity */
const auto delim = ", "s;				/*!< Delimiter for debug output */
constexpr auto tau = 2 * 3.1415926535897932384626433L;	/*!< Pi */

#include "debug.hpp"
#include "io.hpp"
#include "operations.hpp"
#include "range.hpp"
#include "utility.hpp"

#pragma once
#include "core/all.hpp"
#include "number_theory/modulo.hpp"
inline namespace string_tools {
/*! Fast rolling hash on a specific string's substrings.
 *
 * Time complexity: \f$O(n)\f$ to build, \f$O(1)\f$ to query.
 */
struct hash_str {
	static auto constexpr lcg_mod = (1ULL << 62) - 57;
	const char *st;
	vector<modulo> h, p;
	explicit hash_str(const string_view str)
	    : st(str.data()), h(str.size() + 1), p(str.size()) {
		with _w{lcg_mod, modulo::modulus};
		modulo g = 1;
		fo(i, 0, str.size()) {
			g *= modulo{0x51a3e995948c0deULL};
			h[i + 1] = modulo{str[i]} * g;
		}
		partial_sum(al(h), begin(h));
		auto const inv = modulo{1} / modulo{0x51a3e995948c0deULL};
		modulo x = 1;
		fo(i, 0, p.size()) {
			p[i] = x;
			x *= modulo{inv};
		}
	}
	ll operator()(const string_view v) const {
		with _w{lcg_mod, modulo::modulus};
		ll l = v.data() - st;
		return ll((h[l + v.size()] - h[l]) * p[l]);
	}
};
/*! Hashes the bytes in an object.
 *
 * NOTE: not sure if this is really standards-compliant
 */
struct bytehash {
	template <typename T> constexpr auto operator()(const T &x) const {
		return hash<string_view>{}(
		    string_view{reinterpret_cast<const char *>(&x), sizeof(x)});
	}
};
/*! Returns prefix function of string s*/
vector<ll> prefix(string const &s) {
	ll n = s.size();
	vector<ll> p(n);
	fo(i, 1, n) {
		for (ll j = p[i - 1];; j = p[j - 1]) {
			if (s[j] == s[i]) {
				p[i] = j + 1;
				break;
			}
			if (!j) {
				break;
			}
		}
	}
	return p;
}
/*! Find all substrings of t equal to s. Returns list of start index for each match. s must be a
 * nonempty string*/
auto search_all(string const &t, string const &s) {
	assert(!s.empty());
	auto p = prefix(s + '\0' + t);
	vector<ll> v;
	fo(i, t.size()) {
		if (p[s.size() + 1 + i] == s.size()) {
			v.push_back(i + 1 - s.size());
		}
	}
	return v;
}

/*! @brief Search iterator for looping through all matches of a string s in t using KMP.
 *  Complexity: \f$O(n)\f$, where is the length between subsequent matches.
 */
struct search_it : it_base<ll> {
	using iterator_category = input_iterator_tag;
	const string t, s;
	const ll n{}, ed{};
	vector<ll> p;
	ll i = 0, o = 0;
	explicit search_it(string const &t_, string const &s_)
	    : t(t_), s(s_), n(s.size()), ed(n + 1 + t.size()), p(n) {
		++*this;
	}
	explicit search_it(const ll i_) : i(i_) {}
	auto operator*() {
		assert(n);
		return i - n - s.size();
	}
	void operator++() {
		assert(i < ed);
		for (++i; i < ed; ++i) {
			auto cur = i <= n ? s.c_str()[i] : t[i - (n + 1)];
			for (ll j = o;; j = p[j - 1]) {
				if (s[j] == cur) {
					o = j + 1;
					break;
				}
				if (!j) {
					o = 0;
					break;
				}
			}
			if (i < n) {
				p[i] = o;
			}
			if (o == n) {
				break;
			}
		}
	}
};
bool operator==(search_it const &a, search_it const &b) { return a.i == b.i; }
bool operator<(search_it const &a, search_it const &b) { return a.i < b.i; }
template <typename... Ts> auto search_ra(const string &t, const string &s) {
	auto start = search_it(t, s);
	return range{start, search_it(start.ed)};
}
} // namespace string_tools
using namespace string_tools;

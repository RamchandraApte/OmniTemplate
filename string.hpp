#pragma once
#include "core.hpp"
namespace string_tools {
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
	size_t operator()(const string_view v) const {
		with _w{lcg_mod, modulo::modulus};
		ll l = v.data() - st;
		return ll((h[l + v.size()] - h[l]) * p[l]);
	}
};
void test_hash_str() {
	auto main_str = "OmniTemplate, OmniTemplate"sv;
	hash_str func{main_str};
	func(main_str.substr(0, 3));
	unordered_map<string_view, ll, hash_str> mapping({}, func);
	auto omni1 = main_str.substr(0, 4);
	auto omni2 = main_str.substr(14, 4);
	auto omn = main_str.substr(14, 3);
	assert(omni1 == omni2);
	mapping[omni1] = 42;
	assert(mapping[omni2] == 42);
	assert(mapping[omn] == 0);
}
struct bytehash {
	template <typename T> constexpr auto operator()(const T &x) const {
		return hash<string_view>{}(
		    string_view{reinterpret_cast<const char *>(&x), sizeof(x)});
	}
};
void test_bytehash() {
	bytehash func{};
	fo(i, 100) {
		assert(func(i) != func(i + 1));
		assert((func(tuple{to_string(i), i}) !=
			func(tuple{to_string(i), i + 1})));
	}
}
vl prefix(string const &s) {
	ll n = s.size();
	vl p(n);
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
auto search_all(string const &t, string const &s) {
	auto p = prefix(s + '\0' + t);
	vl v;
	fo(i, t.size()) {
		if (p[s.size() + 1 + i] == s.size()) {
			v.push_back(i);
		}
	}
	return v;
}
string empstr = "";
struct search_it : it_base<ll> {
	using iterator_category = input_iterator_tag;
	string const &t, s;
	const ll n, ed;
	vl p;
	ll i = 0, o = 0;
	search_it(string const &t_, string const &s_)
	    : t(t_), s(s_), n(s.size()), ed(n + 1 + t.size()), p(n) {
		++this;
	}
	explicit search_it() : search_it(empstr, empstr) {}
	auto operator*() {
		assert(n);
		return i - (n + 1);
	}
	void operator++() {
		for (++i; i < ed; ++i) {
			auto cur = i <= n ? s.c_str()[i] : t[*this];
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
auto operator==(search_it const &a, search_it const &b) {
	bool sa = a.n, sb = b.n;
	if (sa ^ sb) {
		return a.i == b.i;
	}
	if (sa) {
		return a.i == a.ed;
	}
	if (sb) {
		return b.ed == b.i;
	}
}
auto operator<(search_it const &a, search_it const &b) {
	bool sa = a.n, sb = b.n;
	if (sa ^ sb) {
		return a.i < b.i;
	}
	if (sa) {
		return a.i < a.ed;
	}
	if (sb) {
		return b.ed < b.i;
	}
}
template <typename... Ts> auto search_ra(const Ts &... args) {
	return range{search_it(args...), search_it()};
}
#if 0
class trie_node {
	vector<trie_node *> adj;
	ll start, end;
	trie_node() : adj(26), start() {}
	trie_node *operator[](char c) { return adj[c - 'a']; }
	static trie_node *build_trie(const string &str) {
		auto *root = new trie_node;
		fo(i, str.size()) {}
	}
};
void test_trie_node() {}
#endif
void test_string() {
	test_hash_str();
	test_bytehash();
}
} // namespace string_tools
using namespace string_tools;

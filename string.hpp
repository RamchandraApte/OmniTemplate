#pragma once
#include "core.hpp"
namespace string_tools {
struct hash_str {
	static auto constexpr lcg_mod = (1ULL << 62) - 57;
	const char *st;
	vector<modulo> h, p;
	explicit hash_str(const string &s)
	    : st(s.data()), h(s.size() + 1), p(s.size()) {
		with _w{lcg_mod, M};
		modulo g = 1;
		fo(i, 0, s.size()) {
			g *= modulo{0x51a3e995948c0deULL};
			// dbg(A);
			// dbg(B);
			// dbg(lli((int128(A.x)*int128(B.x))%int128(M)));
			h[i + 1] = modulo{s[i]} * g;
		}
		// dbg(h);
		partial_sum(al(h), begin(h));
		auto const inv = modulo{1} / modulo{0x51a3e995948c0deULL};
		modulo x = 1;
		fo(i, 0, p.size()) {
			p[i] = x;
			x *= modulo{inv};
		}
	}
	size_t operator()(string_view const &v) {
		with _w{lcg_mod, M};
		ll l = v.data() - st;
		// dbg(l);
		// dbg(v.size());
		// dbg(modulo{10}-modulo{100});
		// dbg(h[l+v.size()]-h[l]);
		// dbg(p[l]);
		return ll((h[l + v.size()] - h[l]) * p[l]);
	}
};
struct bytehash {
	auto operator()(const string &x) const {
		return hash<string_view>{}(
		    string_view{reinterpret_cast<const char *>(&x), sizeof(x)});
	}
};
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
	dbg(p);
	return p;
}
auto search_all(string const &t, string const &s) {
	auto p = prefix(s + '\0' + t);
	vl v;
	fo(i, t.size()) {
		if (p[s.size() + 1 + i] == s.size()) {
			v.pb(i);
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
			dbg(i);
			dbg(o);
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
} // namespace string_tools
using namespace string_tools;

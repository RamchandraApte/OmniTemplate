#pragma once
#include "combinatorics/permutation.hpp"
#include "core/all.hpp"
#include "number_theory/modulo.hpp"
inline namespace string_tools {
Permutation suffix_array(string str) {
	str += '\0';
	Permutation perm(str.size()), order(str.size());
	iota(al(perm), 0LL);
	copy(al(str), begin(order));
	auto sort_step = [&](const ll len) {
		with _w{str.size(), modulo::modulus};
		auto pair_key = [&, order](const ll idx) {
			return array{
			    order[idx],
			    order[static_cast<ll>(modulo{idx, no_mod{}} + modulo{len, no_mod{}})]};
		};
		if (len == 0) {
			counting_sort(
			    al(perm), [&](const ll idx) { return str[idx]; }, 256);
		} else {
			counting_sort(
			    al(perm),
			    [&](const ll idx) {
				    return order[static_cast<ll>(modulo{idx, no_mod{}} -
								 modulo{len, no_mod{}})];
			    },
			    str.size());
		}
		for (auto &x : perm) {
			x = static_cast<ll>(modulo{x, no_mod{}} - modulo{len, no_mod{}});
		}
		ll idx = 0;
		fo(i, perm.size()) {
			idx += (i >= 1 && pair_key(perm[i - 1]) != pair_key(perm[i]));
			order[perm[i]] = idx;
		}
	};
	sort_step(0);
	for (ll len = 1; len < str.size(); len *= 2) {
		sort_step(len);
	}
	return perm;
}
vector<ll> lcp_array(const string &str, const Permutation &suffix_arr) {
	const auto n = str.size();
	const auto pos = invert(multiplies{}, suffix_arr);
	ll match = 0;
	vector<ll> lcp(n);
	for (const auto start : pos) {
		if (start == n) {
			continue;
		}
		while (true) {
			auto i = suffix_arr[start] + match, j = suffix_arr[start + 1] + match;
			if (!(max(i, j) < n && str[i] == str[j])) {
				break;
			}
			++match;
		}
		lcp[start] = match;
		match = max(match - 1, 0LL);
	}
	return lcp;
}
} // namespace string_tools

#pragma once
#include "core/all.hpp"
#include "number_theory/modulo.hpp"
inline namespace string_tools {
vector<ll> suffix_array(string str) {
	str += '\0';
	vector<ll> perm(str.size()), order(str.size());
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
			dbg(str);
			counting_sort(
			    al(perm), [&](const ll idx) { return str[idx]; }, 256);
			dbg(perm);
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
		dbg(order);
		dbg(perm);
		sort_step(len);
	}
	dbg(str);
	dbg(order);
	dbg(perm);
	perm.erase(begin(perm));
	return perm;
}
} // namespace string_tools

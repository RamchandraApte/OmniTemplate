#pragma once
#include "core/all.hpp"
namespace string_tools {
vector<ll> suffix_array(string str) {
	str += '\0';
	vector<ll> perm(str.size()), order(str.size());
	iota(al(perm), 0LL);
	copy(al(str), begin(order));
	auto sort_step = [&](const ll len) {
		auto pair_key = [=](const ll idx) {
			return array{order[idx], order[(idx + len) % str.size()]};
		};
		sort(al(perm), key_compare(pair_key));
		ll idx = 0;
		fo(i, perm.size()) {
			idx += (i >= 1 && pair_key(perm[i - 1]) != pair_key(perm[i]));
			order[perm[i]] = idx;
		}
	};
	sort_step(0);
	for (ll len = 1; len < str.size(); len *= 2) {
		;
		sort_step(len);
	}
	perm.erase(begin(perm));
	return perm;
}
} // namespace string_tools

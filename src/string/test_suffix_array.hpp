#include "suffix_array.hpp"
namespace string_tools::test {
Permutation suffix_array_naive(const string &str) {
	Permutation perm(str.size() + 1);
	iota(al(perm), 0LL);
	sort(al(perm), key_compare([&](const ll idx) { return string_view{str}.substr(idx); }));
	return perm;
}
string random_str(const ll len) {
	string str(len, '\0');
	for (auto &c : str) {
		c = uniform_int_distribution<char>('a', 'e')(reng);
	}
	return str;
}
auto lcp_array_naive(const string &str, const Permutation &suffix_arr) {
	const auto n = str.size();
	vector<ll> lcp(n);
	fo(i, n) {
		const auto a = str.substr(suffix_arr[i]), b = str.substr(suffix_arr[i + 1]);
		lcp[i] = mismatch(al(a), al(b)).first - begin(a);
	}
	return lcp;
}
void test_suffix_array() {
	// const string str = "zomniomnitemplatecodeforceshelloworldwatera";
	fo(len, 0, 10) {
		fo(it, 1000) {
			const auto str = random_str(len);
			const auto suffix_arr = suffix_array(str);
			assert(suffix_arr == suffix_array_naive(str));
			assert(lcp_array(str, suffix_arr) == lcp_array_naive(str, suffix_arr));
		}
	}
}
} // namespace string_tools::test
using namespace string_tools::test;

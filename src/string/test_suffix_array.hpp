#include "suffix_array.hpp"
namespace string_tools::test {
vector<ll> suffix_array_naive(const string &str) {
	vector<ll> perm(str.size());
	iota(al(perm), 0LL);
	sort(al(perm), key_compare([&](const ll idx) { return string_view{str}.substr(idx); }));
	return perm;
}
string random_str(const ll len) {
	string str(len, '\0');
	for (auto &c : str) {
		c = uniform_int_distribution<char>('a', 'c')(reng);
	}
	return str;
}
void test_suffix_array() {
	// const string str = "zomniomnitemplatecodeforceshelloworldwatera";
	fo(len, 0, 10) {
		fo(it, 10000) {
			const auto str = random_str(len);
			assert(suffix_array(str) == suffix_array_naive(str));
			if (it % 1000 == 0) {
				cerr << it << "    \r";
			}
		}
	}
}
} // namespace string_tools::test
using namespace string_tools::test;

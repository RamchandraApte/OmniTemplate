#pragma once
#include "string.hpp"
namespace string_tools::test {
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
void test_bytehash() {
	bytehash func{};
	fo(i, 100) {
		assert(func(i) != func(i + 1));
		assert((func(tuple{to_string(i), i}) != func(tuple{to_string(i), i + 1})));
	}
}
vector<ll> brute_search_all(const string &t, const string &s) {
	vector<ll> expected;
	fo(idx, t.size()) {
		if (t.substr(idx, s.size()) == s) {
			expected.push_back(idx);
		}
	}
	return expected;
}
vector<ll> search_it_all(const string &t, const string &s) {
	const auto cont = search_ra(t, s);
	return {begin(cont), end(cont)};
}

void test_search_it_one(const string &t, const string &s) {
	assert(search_all(t, s) == brute_search_all(t, s));
	assert(search_it_all(t, s) == brute_search_all(t, s));
}
void test_search_it() {
	test_search_it_one("abbaababaaabbaababaa"s, "aba"s);
	test_search_it_one("aba"s, "abbaababaaabbaababaa"s);
	test_search_it_one("abbaababaaabbcababaa"s, "aabc"s);
	test_search_it_one("abbaababaaabbaababaa"s, "a"s);
	test_search_it_one("aaaaaa"s, "a"s);
	test_search_it_one("abbaababaaabbaababaa"s, "b"s);
	test_search_it_one("abbaababaaabbaababaa"s, "ba"s);
	test_search_it_one("abccbabcbaccbaabcabbababc"s, "abc"s);
	test_search_it_one(""s, "abc"s);
	test_search_it_one("abccbabcbaccbaabca!\1+!$bbabab+!\1c"s, "+!\1"s);
}
void test_string() {
	test_hash_str();
	test_bytehash();
	test_search_it();
}
} // namespace string_tools::test
using namespace string_tools::test;

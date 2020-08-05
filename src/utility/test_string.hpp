#pragma once
#include "string.hpp"
namespace string::test {
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
void test_string() {
	test_hash_str();
	test_bytehash();
}
} // namespace string::test
using namespace string::test;

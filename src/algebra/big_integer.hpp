#pragma once
#include "core/all.hpp"
namespace bigint {
struct bigint {
	vector<ull> v;
	explicit bigint(const vector<ull> &v_) : v(v_) {}
	auto operator[](ll i) const { return i < ssize(v) ? v[i] : 0; }
};
template <typename Stream> auto &operator<<(Stream &os, bigint const &a) { return os << a.v; }
#if 0
auto operator+(bigint const& a, bigint const& b){
#define addo __builtin_add_overflow
	initializer_list xs{a,b};
	ull sm = 0;
	for(const auto& x: xs){sm+=x.v.size();}
	bigint c(sm+1);
	fo(i,sm){
		for(const auto& x: xs){
			c.v[i+1] |= addo(c.v[i], x[i], c.v.data()+i);
		}
	}
	return c;
}
#endif
} // namespace bigint
using namespace bigint;

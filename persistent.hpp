#pragma once
#include "core.hpp"
namespace persistent {
struct first_cmp {
	/*! Compare based on the first member of a variable*/
	template <typename T> bool operator()(T a, T b) const {
		return a.first < b.first;
	}
};
tm() struct pers {
	/*! Persistent variable. The old values can be retrieved by changing the
	 * time tim*/

	static inline auto tim = 0LL; //!< Time for the persistent variable
	using event = pair<ll, T>;
	set<event, first_cmp> s;
	auto operator=(const T &v) {
		event e{tim, v};
		s.erase(e);
		s.insert(e);
	}
	operator auto() const { return (*--s.upper_bound({tim, T{}})).second; }
};
template <typename Stream, typename T>
auto &operator<<(Stream &os, pers<T> const &p) {
	/*! Print the current value of the persistent variable p*/
	return os << static_cast<T>(p);
}
} // namespace persistent
using namespace persistent;

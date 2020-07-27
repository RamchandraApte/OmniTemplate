#pragma once
#include "core/all.hpp"
namespace persistent {
/*! Compare based on the first member of a variable*/
struct first_cmp {
	template <typename T> bool operator()(T a, T b) const {
		return a.first < b.first;
	}
};
/*! Persistent variable. The old values can be retrieved by changing the
* time tim
* 
* Time complexity: \f$O(log n)\f for setting and getting the value.
* 
* Space complexity: \f$O(1)\f$ per assignment.
*/
tm() struct pers {
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

#pragma once
#include "debug.hpp"
/*! Reverse input class. This allows reusing output operators for input.
 *
 * @warning This is a hack, but it works.
 */
struct rin {
	istream &in;
	rin(istream &in_) : in(in_) {}
	auto &operator<<(const char *) { return this; }
	auto &operator<<(string const &s) {
		if (s.empty()) {
			in >> const_cast<string &>(s);
		}
		return this;
	}
	template <typename T> rin &operator>>(T &x) {
		this << x;
		return this;
	}
};
template <typename R, typename T>
auto operator<<(R &r, const T &x)
    -> decltype(r.in >> const_cast<T &>(x),
		declval<enable_if_t<is_same<R, rin>::value, rin &>>()) {
	r.in >> const_cast<T &>(x);
	return r;
}
template <typename Stream, typename T>
enable_if_t<is_same<T, istream>::value, rin> operator>>(Stream &is, T &x) {
	rin r{is};
	return r >> x;
}
template <typename Stream, typename... T>
auto &operator<<(Stream &os, tuple<T...> t) {
	apply(
	    [&](auto &f, auto &... x) {
		    os << f;
		    ((os << delim << x), ...);
	    },
	    t);
	return os;
}
template <typename T1, typename... Ts>
auto print(const T1 &arg1, const Ts &... args) {
	/*! Print arguments separated by spaces to stdout*/
	cout << arg1;
	((cout << " " << args), ...);
	cout << endl;
}
namespace std {
template <typename Stream, typename... T>
auto &operator<<(Stream &os, pair<T...> const &p) {
	return os << simple_tp(p) << "{" << p.first << delim << p.second << "}";
}
template <typename Stream, typename Container>
auto operator<<(Stream &os, const Container &v)
    -> decltype(begin(v), declval<decltype(os)>()) {
	auto ed = begin(v);
	auto big = v.size() > 20;
	if (big) {
		advance(ed, 20);
	} else {
		ed = end(v);
	}
	os << simple_tp(v) << "{";
	copy(begin(v), ed, make_ostream_joiner(os, delim));
	if (big) {
		os << delim << "...";
	}
	return os << "}";
}
template <typename T>
auto operator<<(rin &os, const T &v)
    -> decltype(begin(v), declval<decltype(os)>()) {
	for (const auto &elem : v) {
		os << elem;
	}
	return os;
}
#if __cplusplus >= 201703L
template <typename Stream, typename T>
auto &operator<<(Stream &os, optional<T> const &opt) {
	return opt ? (os << *opt) : (os << "nullopt");
}
#endif
} // namespace std

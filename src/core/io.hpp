#pragma once
#include "debug.hpp"
/*! Reverse input class. This allows reusing output operators for input.
 *
 * @warning This is a hack, but it works.
 */
struct rin {
	istream &in;
	rin(istream &in_) : in(in_) {}
	auto &operator<<(const char *) { return *this; }
	auto &operator<<(string const &s) {
		if (s.empty()) {
			in >> const_cast<string &>(s);
		}
		return *this;
	}
	template <typename T> rin &operator>>(T &x) { return *this << x; }
};
template <typename R, typename T>
auto operator<<(R &r, const T &x)
    -> decltype(r.in >> const_cast<T &>(x), declval<enable_if_t<is_same<R, rin>::value, rin &>>()) {
	r.in >> const_cast<T &>(x);
	return r;
}
template <typename Stream, typename T>
enable_if_t<is_same<T, istream>::value, rin> operator>>(Stream &is, T &x) {
	rin r{is};
	return r >> x;
}
template <typename Stream, typename Tuple, auto size = std::tuple_size<Tuple>::value>
auto &operator<<(Stream &os, const Tuple &tuple) {
	os << simple_tp(tuple) << "{";
	apply(
	    [&](auto &f, auto &...x) {
		    os << f;
		    ((os << delim << x), ...);
	    },
	    tuple);
	return os << "}";
}
template <typename T1, typename... Ts> auto print(const T1 &arg1, const Ts &... args) {
	/*! Print arguments separated by spaces to stdout*/
	cout << arg1;
	((cout << " " << args), ...);
	cout << endl;
}
namespace std {
// enable_if is there to avoid problems with ostringstream
// TODO fix this whole IO mess one day.
template <typename Stream, typename Container>
auto operator<<(Stream &os, const Container &v)
    -> enable_if_t<is_same_v<Stream, ostream>, decltype(begin(v), declval<decltype(os)>())> {
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
auto operator<<(rin &os, const T &v) -> decltype(begin(v), declval<decltype(os)>()) {
	for (const auto &elem : v) {
		os << elem;
	}
	return os;
}
template <typename Stream, typename T> auto &operator<<(Stream &os, optional<T> const &opt) {
	return opt ? (os << *opt) : (os << "nullopt");
}
// FIXME This should really not be in the std namespace
rin rin_cin{cin};
auto &orig_cin = cin;
auto &orig_cerr = cerr;
#define cin rin_cin
} // namespace std

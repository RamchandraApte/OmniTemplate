#pragma once
#include "core.hpp"
namespace time_tools {
struct timer {
	/*! Timer class that return the time between construction and
	 * destruction */
	tp(clock_::now()) t1;
	timer() : t1(clock_::now()) {}
	~timer() {
		cerr << "Time duration: "
		     << duration<ld>(clock_::now() - t1).count() << " s"
		     << endl;
	}
};
template <typename Func> void bench(Func a) {
	timer _t;
	dbg(ll(-5) / ll(3));
	dbg(tp(a)(-5) / tp(a)(3));
	dbg(tp(a)(-6) / tp(a)(3));
	tp(a) ans = 0;
	for (tp(a) i = 0; i < a; ++i) {
		for (tp(a) j = 1; j < a; ++j) {
			ans += ((-i) % (j));
		}
	}
	dbg(ans);
}
} // namespace time_tools
using namespace time_tools;

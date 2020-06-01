#pragma once
#include "core.hpp"
namespace time_tools {
struct timer {
	/*! Timer class that return the time between construction and
	 * destruction */
	decltype(clock_::now()) t1;
	timer() : t1(clock_::now()) {}
	~timer() {
		cerr << "Time duration: "
		     << duration<ld>(clock_::now() - t1).count() << " s"
		     << endl;
	}
};
template <typename Func> void bench(Func a) {
	timer _t;
	decltype(a) ans = 0;
	for (decltype(a) i = 0; i < a; ++i) {
		for (decltype(a) j = 1; j < a; ++j) {
			ans += ((-i) % (j));
		}
	}
	// TODO avoid optimization of ans?
}
} // namespace time_tools
using namespace time_tools;

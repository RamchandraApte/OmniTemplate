// Useful code for competitive programming
#pragma once
#include "core/all.hpp"
#include "time.hpp"

string yesno(const bool b) { return b ? "Yes" : "No"; }

struct set_multitest {
	inline static bool multitest{};
	explicit set_multitest(const bool val = true) { multitest = val; }
};
extern void main2();
int main(int argc, char *argv[]) {
#ifdef DEBUG
	debug_mode = true;
#endif
	fo(i, argc) {
		if (argv[i] == "-q"s) {
			debug_mode = false;
		}
	}
	ios::sync_with_stdio(false);
	if (!debug_mode) {
		cerr.rdbuf(nullptr);
	}
	for (ios &os : initializer_list<reference_wrapper<ios>>{orig_cin, cout, orig_cerr, clog}) {
		fixed(os);
		if (os.rdbuf()) {
			os.exceptions(ios::failbit | ios::badbit | ios::eofbit);
		}
		os.precision(false ? numeric_limits<ld>::max_digits10 : 5);
	}
	cout.precision(numeric_limits<ld>::max_digits10);
	timer _t;
	ll t = 1;
	if (set_multitest::multitest) {
		cin >> t;
	}
	fo(i, t) { main2(); }
}

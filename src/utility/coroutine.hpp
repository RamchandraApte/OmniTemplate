#pragma once
#include "core/all.hpp"
/*! Coroutine library
 * CO_SWITCH for using switch-based coroutines
 * CO_JMP for using setjmp-based coroutines */
inline namespace coroutine {
#define CO_SWITCH
#ifdef CO_SWITCH
#define cobegin                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        \
	static ll pos = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             \
	switch (pos) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
	case 0:
#define coend                                                                  \
	default:                                                               \
		throw out_of_range("Coroutine reached end.");                  \
		}
#define coreturn(x)                                                            \
	pos = __LINE__;                                                        \
	return x;                                                              \
	case __LINE__:;
#endif
#ifdef CO_JMP
#define cobegin                                                                \
	static bool first = true;                                              \
	static jmp_buf env;                                                    \
	if (!first) {                                                          \
		longjmp(env, true);                                            \
	}                                                                      \
	first = false;
#define coreturn                                                               \
	if (!setjmp(env))                                                      \
	return
#define coend throw out_of_range("Coroutine reached end.");
#endif
ll coro(ll a) {
	cobegin coreturn(404);
	for (static ll i = 0; i < a; i++) {
		coreturn(i * i);
	}
	coreturn(505);
	coend
}
} // namespace coroutine

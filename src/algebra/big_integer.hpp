#pragma once
#include "core/all.hpp"
namespace bigint {
struct BigInt {
	using DigitType = unsigned int;
	vector<DigitType> digits;
	explicit BigInt(const ll size_) : digits(size_) {}
	explicit BigInt(const vector<DigitType> &digits_) : digits(digits_) {}
	BigInt(const DigitType n) : digits{n} {}
	auto operator[](ll i) const { return i < ssize(digits) ? digits[i] : 0; }
};
template <typename Stream> auto &operator<<(Stream &os, BigInt const &bigint) {
	return os << bigint.digits;
}
auto operator+(BigInt const &a, BigInt const &b) {
	BigInt ret(max(a.digits.size(), b.digits.size()) + 1);
	copy(al(a.digits), begin(ret.digits));
	bool carry{};
	fo(i, b.digits.size() + 1) {
		const ll sum = static_cast<ll>(ret.digits[i]) + b[i] + carry;
		ret.digits[i] = sum;
		carry = (sum > numeric_limits<BigInt::DigitType>::max());
	}
	return ret;
}
bool operator==(const BigInt &a, const BigInt &b) {
	range<int_it<ll>> rng{0, max(ssize(a.digits), ssize(b.digits))};
	return all_of(al(rng), [&](const ll idx) { return a[idx] == b[idx]; });
}
} // namespace bigint
using namespace bigint;

#include "core/main.hpp"
bool multitest = false;
void main2() {
	cout << clock_::now().time_since_epoch().count() << endl;
	cout << reng() << endl;
	random_device_patch dev{};
	const auto x = dev();
	const auto y = dev();
	cout << x << " " << y << endl;
}

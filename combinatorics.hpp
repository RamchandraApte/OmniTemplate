auto perm(auto a, auto b){
	using T = tp(a);
	return accumulate(int_it<T>{a+1-b}, int_it<T>{a+1}, 1LL, multiplies<>{});
}
auto fact(auto n){
	return perm(n, n);
}
auto choose(auto a, auto b){
	// Returns a choose b
	return perm(a, b)/fact(b);
}
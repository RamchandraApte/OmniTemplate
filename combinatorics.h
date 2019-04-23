_ perm(_ a, _ b){
	using T = tp(a);
	return accumulate(int_it<T>{a+1-b}, int_it<T>{a+1}, 1LL, multiplies<>{});
}
_ fact(_ n){
	return perm(n, n);
}
_ choose(_ a, _ b){
	// Returns a choose b
	return perm(a, b)/fact(b);
}
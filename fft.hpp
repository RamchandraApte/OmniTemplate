#if 0
 auto fft(auto& v, df(d, 1LL),  df(s, 0LL)){
	 if(v.size() == d){return;}
	auto n = nx2(v.size());
	v.resize(n);
	fft(v, 2*d, s);
	fft(v, 2*d, s+d);
	auto e = exp(com{-double{tau}*1.0i/(n/d)});
	auto p = com{1};
	auto i = s;
	vc<com> out(n/d);
	fo(j,n/(2*d)){
		auto od = p*v[i+d];
		out[j] = v[i]+od;
		out[j+n/(2*d)] = v[i]-od;
		p*=e;
		i+=2*d;
	}
	i = s;
	for(const auto& x:out){
		v[i] = x;
		i+=d;
	}
}
auto ifft(auto& v){
	reverse(begin(v)+1, end(v));
	fft(v);
	for(auto& x: v){
		x/=com(v.size());
	}
}
#endif
#if 1
auto fft(auto v) {
	auto n = nx2(v.size());
	if (n == 1) {
		return v;
	}
	v.resize(n);
	vc<vc<com>> vs(2, vc<com>(n / 2));
	fo(i, n) { vs[i % 2][i / 2] = v[i]; }
	for (auto &x : vs) {
		x = fft(x);
	}
	vc<com> f(n);
	fo(i2, n) {
		auto i = i2 % (n / 2);
		f[i2] =
			vs[0][i] + exp(-com{0, double{tau} * double{i2 / n}}) * vs[1][i];
		//++cnt;
	}
	return f;
}
auto ifft(auto v) {
	reverse(begin(v) + 1, end(v));
	auto r = fft(v);
	for (auto &x : r) {
		x /= com{v.size()};
	}
	return r;
}
#endif
auto conv(const auto &a, const auto &b) { return ifft(fft(a) * fft(b)); }
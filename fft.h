#if 0
 _ fft(_& v, df(d, 1LL),  df(s, 0LL)){
	 if(v.size() == d){return;}
	_ n = nx2(v.size());
	v.resize(n);
	fft(v, 2*d, s);
	fft(v, 2*d, s+d);
	_ e = exp(com{-double{tau}*1.0i/(n/d)});
	_ p = com{1};
	_ i = s;
	vc<com> out(n/d);
	fo(j,n/(2*d)){
		_ od = p*v[i+d];
		out[j] = v[i]+od;
		out[j+n/(2*d)] = v[i]-od;
		p*=e;
		i+=2*d;
	}
	i = s;
	for($ x:out){
		v[i] = x;
		i+=d;
	}
}
_ ifft(_& v){
	reverse(begin(v)+1, end(v));
	fft(v);
	for(_& x: v){
		x/=com(v.size());
	}
}
#endif
#if 1
_ fft(_ v){
	_ n = nx2(v.size());
	if(n == 1){return v;}
	v.resize(n);
	vc<vc<com>> vs(2, vc<com>(n/2));
	fo(i,n){
		vs[i%2][i/2] = v[i];
	}
	for(_& x: vs){
		x = fft(x);
	}
	vc<com> f(n);
	fo(i2,n){
		_ i = i2%(n/2);
		f[i2] = vs[0][i]+exp(-com{0, double{tau}*double{i2/n}})*vs[1][i];
		//++cnt;
	}
	return f;
}
_ ifft(_ v){
	reverse(begin(v)+1, end(v));
	_ r = fft(v);
	for(_& x: r){
		x/=com{v.size()};
	}
	return r;
}
#endif
_ conv($ a, $ b){
	return ifft(fft(a)*fft(b));
}
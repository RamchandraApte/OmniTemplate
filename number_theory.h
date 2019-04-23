vl divs;
_ prime(_ n){
	assert(n>=2);
	if(n < divs.size()){
		return divs[n] == n;
	}
	with _m{n,M};
	ll tz = __builtin_ctz(n-1);
	_ b = (n-1)>>tz;
	dbg(b);
	_ prime_a = [&](md co& a){
		dbg(a);
		if(a==0){return true;}
		_ p = power(a,b);
		if(p==1){return true;}
		fo(i,tz){
			if(p == -1){return true;}
			p*=p;
		}
		return false;
	};
	vl v{2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	return all_of(al(v), prime_a);
}
vl divisors(ll x){
	vl v;
	fo(d,1,ll{ceil(sqrt(ld{x}))}+1){
		if(!(x%d)){
			v.pb(d);
			if(ll y = x/d; d!=y){
				v.pb(y);
			}
		}
	}
	return v;
}
_ sieve(ll n){
	vl d(n), ps;
	fo(i,2,n){
		if(d[i] == 0){ps.pb(d[i] = i);}
		for(_ p: ps){
			if(!(p<=d[i] && p*i < n)){break;}
			assert(d[p*i] == 0);
			d[p*i] = p;
		}
	}
	return d;
}
um fac(ll n){
	// Returns the factorization of n as a mapping from the prime to the exponent.
	assert(n>=1);
	if(n==1){return {};};
	ll g = n;
	if(n < divs.size()){
		g = divs[n];
	}
	else if(!prime(n)) {
		with _m{n,M};
		for(md c = 0;g == n;++c){
			_ co f = [&]($ x){return x*x+x+c;};
			for(md a = 0, b = a; a = f(a), b = f(f(b)), (g = gcd(ll(a-b),n)) == 1;){}
		}
	}
	if(g == n){
		return {{n,1}};
	}
	assert(1 < g && g < n && !(n%g));
	return fac(g) + fac(n/g);
}
void egcd($ a, $ b, _& x, _& y){a?egcd(b%a, a, y, x),x-=b/a*y:(x=0,y=1);}
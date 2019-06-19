tm() struct mat {
	ll r,c;
	vc<T> a;
	mat(_ r_, _ c_, df(v, 0LL)): r(r_), c(c_), a(r*c, v) {assert(r>=1 && c>=1);}
	mat(_ d):r(1),c(1),a{d}{}
	mat(vc<vc<pr>> co& g):mat(g.size(),g.size(),inf) {
		fo(i,r){
			for($ p:g[i]){
				_ [x,w] = p;
				this[i][x] = w;
			}
		}
		fo(i,r){
			this[i][i]=0;
		}
	}
	mat(const initializer_list<initializer_list<ll>>& vals): mat(size(vals), size(begin(vals)[0])){
		fo(i,r){
			assert(size(begin(vals)[i]) == c);
			fo(j,c){
				this[i][j] = begin(begin(vals)[i])[j];
			}
		}
	}
	_ operator[](_ i){
		return const_cast<T*>(const_cast<mat co&>(this)[i]);
	}
	_ operator[](_ i) co{
		return &a[i*c];
	}
	_ id() co{
		return this.r==1 && this.c==1 && this[0][0]==1;
	}
};
tm(...) _ operator*(mat<T...> co& a, mat<T...> co& b){
	if(a.id()){return b;}
	if(b.id()){return a;}
	assert(a.c == b.r);
	mat<T...> c{a.r, b.c};
	fo(i,c.r){
		fo(j,a.c){
			fo(k,c.c){
				c[i][k]+=a[i][j]*b[j][k];
			}
		}
	}
	return c;
}
template<typename T>
pair<mat<T>&&, T> gauss(mat<T> b, mat<T> a){
	/*
	Returns x such that ax=b and the determinant of a via Gaussian elimination.
	*/
	assert(a.r == a.c);
	assert(a.r == b.r);
	T det = 1;
	fo(i,a.r){
		const auto div = a[i][i];
		det*=div;
		for(auto& ar: {ref(a), ref(b)}){
			fo(k,ar.get().c){
				ar.get()[i][k]/=div;
			}
		}
		fo(j,a.r){
			if(j==i){continue;}
			const auto mul = a[j][i];
			for(auto& ar: {ref(a), ref(b)}){
				fo(k,ar.get().c){
					ar.get()[j][k]-=ar.get()[i][k]*mul;
				}
			}
		}
	}
	return {move(b), det};
}
tm(...) _ operator/(mat<T...> b, mat<T...> a){
	return gauss(b,a).first;
}
template<typename T>
T det(const mat<T>& a){
	return gauss(mat<T>(a.r, 1), a).second;
}
tm(...) _& operator<<(ostream& os, mat<T...> co& m){
	os<<"mat{"<<endl;
	fo(i,m.r){
		copy(m[i], m[i]+m.c, make_ostream_joiner(os, delim));
		os<<endl;
	}
	return os<<"}";
}
template<typename T>
_ lin_recur(vc<T> co& c, ll n){
	mat<T> m{size(c), size(c)};
	copy(al(c), m[0]);
	fo(i,1,size(c)){
		m[i][i-1] = 1;
	}
	return power(m,n)[0][0];
}
void test_matrix(){
        mat<ld> a{{2,3,5}, {3,6,10}, {5,9,16}};
        mat<ld> b{{1,2,3}, {4,5,6}, {9,7,8}};
        auto x = b/a;
        dbg(x);
        dbg(a*x);
        dbg(b);
        dbg(det(a));
}
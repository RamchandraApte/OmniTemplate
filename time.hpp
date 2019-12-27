struct timer {
	tp(clock_::now()) t1;
	timer(): t1(clock_::now()){}
	~timer(){
		cerr<<"Time duration: "<<duration<ld>(clock_::now()-t1).count()<<" s"<<endl;
	}
};
_ bench(_ a){
	timer _t;
	dbg(ll(-5)/ll(3));
	dbg(tp(a)(-5)/tp(a)(3));
	dbg(tp(a)(-6)/tp(a)(3));
	tp(a) ans = 0;
	for(tp(a) i = 0; i < a; ++i){
		for(tp(a) j = 1; j < a; ++j){
			ans+=((-i)%(j));
		}
	}
	dbg(ans);
}
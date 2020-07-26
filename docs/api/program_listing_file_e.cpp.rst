
.. _program_listing_file_e.cpp:

Program Listing for File e.cpp
==============================

|exhale_lsh| :ref:`Return to documentation for file <file_e.cpp>` (``e.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include "segment_tree.hpp"
   #include "main.hpp"
   namespace std{
   pr operator+(pr a, const pr& b){
       a.first = b.first;
       a.second = min(a.second, b.second);
       return a;
   }
   }
   pr identity(const Min&, const pr&){
       return {inf, inf};
   }
   bool multitest{};
   void main2() {
       I(n);I(m);
       vl a(n);
       for(auto& x:a){cin>>x;}
       const ll sz = 9;
       using st = SegmentTree<pr, Min, plus<>, false, false, false>;
       vc<st> s(sz, st(2));
       vc arr(sz, vc<pr>(n));
       fo(i,0,n){
           ll x = a[i];
           fo(j,0,sz){
               arr[j][i] = {x%10?a[i]:inf, i};
               x/=10;
           }
       }
       fo(j,0,sz){
           s[j] = st(arr[j]);
       }
       auto q1 = [&](ll idx, const ll orig){
           --idx;
           ll val = orig;
           fo(i,0,sz){
               auto& tree = s[i];
               tree.update(idx, idx+1, {(val%10?orig:inf), idx});
               val/=10;
           }
       };
       auto q2 = [&](ll l, ll r){
           --l;
           ll ans = inf;
           fo(i,0,sz){
               auto m1 = s[i].query(l, r);
               if(m1.first == inf){continue;}
               auto m2 = min(s[i].query(l, m1.second), s[i].query(m1.second+1, r));
               if(m2.first == inf){continue;}
               ans = min(ans, m1.first+m2.first);
           }
           if(ans == inf){ans = -1;}
           cout<<ans<<endl;
       };
       fo(i,0,m){
           I(tp);I(qa);I(qb);
           if(tp == 1){
               q1(qa, qb);
           }
           if(tp == 2){
               q2(qa, qb);
           }
       }
   }

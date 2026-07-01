// depends on: Point
#define P Point
pair<P, P> closest(Polygon &v) {
  set<P> s;
  sort(all(v),[](P a,P b){return a.y<b.y;});
  pair<ld,pair<P,P>>ans={LDBL_MAX,{P(),P()}};
  ll j = 0;
  for (P p : v) {
    P d{ans.first,0};
    while (j<sz(v) && v[j].y<=p.y-d.x)s.erase(v[j++]);
    auto lo=s.lower_bound(p-d), hi=s.upper_bound(p+d);
    for (;lo!=hi;lo = ++lo) chmin(ans,{(*lo-p).abs(),{*lo,p}});
    s.insert(p);
  }
  return ans.second;
}
#undef P
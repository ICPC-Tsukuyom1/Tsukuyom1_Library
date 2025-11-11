// depends on: Point, ccCircle
Circle mec(Polygon ps) {
  shuffle(all(ps),mt19937(time(0)));
  Circle c = {ps[0], 0};
  ld eps = 1 + 1e-10;
  rep(i,sz(ps)) if((c.c-ps[i]).abs()>c.r*eps){
    c={ps[i],0};
    rep(j,i) if((c.c-ps[j]).abs()>c.r*eps){
      c.c=(ps[i]+ps[j])/2;
      c.r=(c.c-ps[i]).abs();
      rep(k,j) if((c.c-ps[k]).abs()>c.r*eps){
        c=ccCircle(ps[i],ps[j],ps[k]);
      }
    }
  }
  return c;
}
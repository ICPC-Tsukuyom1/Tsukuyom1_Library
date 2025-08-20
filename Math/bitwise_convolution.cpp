// Subset Zeta Transform
// assert : popcount(sz(v)) == 1
#define szt(v, op) \
  for(int i=1; i<sz(v); i<<=1) \
  for(int j=0; j<sz(v); j += i<<1) \
  rep(k, i) v[i+j+k] op v[j+k];

template <class T>
vector<T> or_conv(vector<T> a, vector<T> b)
{
  szt(a, +=); szt(b, +=);
  rep(i, sz(a)) a[i] *= b[i];
  szt(a, -=);
  return a;
}

#undef szt
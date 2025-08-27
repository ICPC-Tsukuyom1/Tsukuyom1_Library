// Subset Zeta Transform (上位集合)
// assert: |v|は二冪
#define szt(v, op) \
  for(int i=1; i<sz(v); i*=2) \
  for(int j=0; j<sz(v); j += i*2) \
  rep(k, i) v[j+k] op v[i+j+k]

template <class T>
vector<T> and_conv(vector<T> a, vector<T> b)
{
  szt(a, +=); szt(b, +=);
  rep(i, sz(a)) a[i] *= b[i];
  szt(a, -=);
  return a;
}

#undef szt
// Subset Zeta Transform (下位集合)
// assert: |v|は二冪
#define szt(v, op)                   \
  for (int i = 1; i < sz(v); i *= 2) \
    for (int j = 0; j < sz(v); j += i * 2) rep(k, i) v[i + j + k] op v[j + k];

template <class T>
vector<T> or_conv(vector<T> a, vector<T> b) {
  szt(a, +=);
  szt(b, +=);
  rep(i, sz(a)) a[i] *= b[i];
  szt(a, -=);
  return a;
}

#undef szt
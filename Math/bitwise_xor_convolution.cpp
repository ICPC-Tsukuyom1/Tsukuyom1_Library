// Walsh Hadamard Transform
// assert: |v|は二冪
#define wht(v)                                         \
  for (int i = 1; i < sz(v); i *= 2)                   \
    for (int j = 0; j < sz(v); j += i * 2) rep(k, i) { \
        auto s = v[j + k], t = v[i + j + k];           \
        v[j + k] = s + t;                              \
        v[i + j + k] = s - t;                          \
      }

template <class T>
vector<T> xor_conv(vector<T> a, vector<T> b) {
  wht(a);
  wht(b);
  rep(i, sz(a)) a[i] *= b[i];
  wht(a);
  T iv = T(1) / sz(a);
  for (auto& x : a) x *= iv;
  return a;
}

#undef wht
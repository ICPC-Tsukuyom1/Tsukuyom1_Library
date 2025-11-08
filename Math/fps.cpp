template <typename T = ll>
struct FPS : vector<T> {
 private:
  ll mod = 998244353;
  ll root = 3;
  void ntt(vec<T>& a) {
    ll n = sz(a), L = 31 - __builtin_clz(n);
    vl rt(2, 1);
    for (ll k = 2, s = 2; k < n; k *= 2, s++) {
      rt.resize(n);
      ll z[] = {1, modpow(root, mod >> s, mod)};
      reps(i, k, 2 * k) rt[i] = modmul(rt[i / 2], z[i & 1], mod);
    }
    vec<T> rev(n);
    rep(i, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (ll k = 1; k < n; k *= 2) {
      for (ll i = 0; i < n; i += 2 * k) {
        rep(j, k) {
          ll z = modmul(rt[j + k], a[i + j + k], mod), &ai = a[i + j];
          a[i + j + k] = ai - z + (z > ai ? mod : 0ll);
          ai += (ai + z >= mod ? z - mod : z);
        }
      }
    }
  }

  vec<T> conv(vec<T> a, vec<T> b) {
    if (!sz(a) || !sz(b)) return {};
    ll s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
    ll inv = modinv(n, mod);
    vec<T> L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    rep(i, n) out[-i & (n - 1)] = modmul(L[i], modmul(R[i], inv, mod), mod);
    ntt(out);
    out.resize(s);
    return out;
  }

 public:
  using vector<T>::vector;
  using P = FPS;

  void set_mod(ll md, ll g) {
    mod = md;
    root = g;
  }

  ll size() {
    return (ll)*this->size();
  }

  P pre(ll def) const {
    return P(begin(*this), begin(*this) + min(size(), def));
  }
  P rev(ll deg = -1) const {
    P ret(*this);
    if (deg != -1) ret.resize(deg, T(0));
    reverse(all(ret));
    return ret;
  }

  void shrink() {
    while (this->size() && !this->back()) this->pop_back();
  }

  T freq(ll p) const { return (p < size()) ? (*this)[p] : T(0); }

  P operator+(const P& r) const { return P(*this) += r; }
  P operator+(const T& v) const { return P(*this) += v; }
  P operator-(const P& r) const { return P(*this) -= r; }
  P operator-(const T& v) const { return P(*this) -= v; }
  P operator*(const P& r) const { return P(*this) *= r; }
  P operator*(const T& v) const { return P(*this) *= v; }
  P operator/(const P& r) const { return P(*this) /= r; }
  P operator%(const P& r) const { return P(*this) %= r; }

  P& operator+=(const P& r) {
    if (r.size() > size()) this->resize(r.size());
    rep(i, r.size())(*this)[i] += r[i];
    return *this;
  }
  P& operator-=(const P& r) {
    if (r.size() > (ll)this->size()) this->resize(r.size());
    rep(i, r.size())(*this)[i] =
        (*this)[i] - r[i] + (r[i] > (*this)[i] ? mod : 0ll);
    return *this;
  }

  P& operator*=(const P& r) {
    if (this->empty() || r.empty()) {
      this->clear();
      return *this;
    }
    auto ret = conv(*this, r);
    return *this = {all(ret)};
  }
  P& operator/=(const P& r) {
    if (this->size() < r.size()) {
      this->clear();
      return *this;
    }
    ll n = this->size() - r.size() + 1;
    return *this = (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);
  }
  P& operator%=(const P& r) {
    *this -= *this / r * r;
    shrink();
    return *this;
  }
  pair<P, P> div_mod(const P& r) {
    P q = *this / r;
    P x = *this - q * r;
    x.shrink();
    return make_pair(q, x);
  }
  P operator-() const {
    P ret(size());
    rep(i, size()) ret[i] = -(*this)[i];
    return ret;
  }
  P& operator+=(const T& v) {
    if (this->empty()) this->resize(1);
    (*this)[0] += v;
    return *this;
  }
  P& operator-=(const T& v) {
    if (this->empty()) this->resize(1);
    (*this)[0] -= v;
    return *this;
  }
  P& operator*=(const T& v) {
    rep(i, (ll)this->size())(*this)[i] = modmul((*this)[i], v, mod);
    return *this;
  }
  P dot(P r) const {
    P ret(min(this->size(), r.size()));
    rep(i, ret.size()) ret[i] = modmul((*this)[i], r[i], mod);
    return ret;
  }
  P operator>>(ll sz) const {
    if ((ll)this->size() <= sz) return {};
    P ret(*this);
    ret.erase(ret.begin(), ret.begin() + sz);
    return ret;
  }
  P operator<<(ll sz) const {
    P ret(*this);
    ret.insert(ret.begin(), sz, T(0));
    return ret;
  }
  T operator()(T x) const {
    T r = 0, w = 1;
    for (auto& v : *this) {
      r += w * v;
      w *= x;
    }
    return r;
  }
  P diff() const {
    const ll n = (ll)this->size();
    P ret(max(0ll, n - 1));
    reps(i, 1, n) ret[i - 1] = modmul((*this)[i], T(i), mod);
    return ret;
  }
  P integral() const {
    const ll n = (ll)this->size();
    P ret(n + 1);
    rep(i, n) ret[i + 1] = modmul(freq(i), modinv(T(i + 1), mod), mod);
    return ret;
  }
  P inv(ll deg = -1) const {
    if (deg == -1) deg = (ll)this->size();
    P res = P({modmul(T(1), modinv(freq(0), mod), mod)});
    for (ll i = 1; i < deg; i *= 2) {
      res = (res * T(2) - res * res * pre(2 * i)).pre(2 * i);
    }
    return res.pre(deg);
  }
  P exp(ll n = -1) const {
    assert(freq(0) == T(0));
    if (n == -1) n = (ll)this->size();
    P g = P({T(1)});
    for (ll i = 1; i < n; i *= 2) {
      g = (g * (pre(i * 2) + P({T(1)}) - g.log(i * 2))).pre(i * 2);
    }
    return g.pre(n);
  }
  P log(ll n = -1) const {
    if (n == -1) n = (ll)this->size();
    assert(freq(0) == T(1));
    auto f = pre(n);
    return (f.diff() * f.inv(n - 1)).pre(n - 1).integral();
  }
  P sqrt(ll deg = -1) const {
    const ll n = (ll)this->size();
    if (deg == -1) deg = n;
    if ((*this)[0] == T(0)) {
      reps(i, 1, n) {
        if ((*this)[i] != T(0)) {
          if (i & 1) return {};
          if (deg - i / 2 <= 0) break;
          auto ret = (*this >> i).sqrt(deg - i / 2);
          if (ret.empty()) return {};
          ret = ret << (i / 2);
          if (ret.size() < deg) ret.resize(deg, T(0));
          return ret;
        }
      }
      return P(deg);
    }
    auto sqr = T(modsqrt((*this)[0], mod));
    if (abs(modmul(sqr, sqr, mod) - (*this)[0]) % mod != 0) return {};
    P ret{sqr};
    T inv2 = modinv(T(2), mod);
    for (ll i = 1; i < deg; i <<= 1) {
      ret = (ret + pre(i << 1) * ret.inv(i << 1)) * inv2;
    }
    return ret.pre(deg);
  }
  P pow(ll k, ll n = -1) {
    if (n == -1) n = (ll)this->size();
    if (k == 0) {
      P res(n);
      res[0] = T(1);
      return res;
    }
    rep(i, (ll)this->size()) {
      if ((*this)[i]) {
        T rev = modmul(T(1), modinv((*this)[i], mod), mod);
        P ret = (((*this * rev) >> i).log(n) * T(k)).exp(n);
        ret *= modpow((*this)[i], k, mod);
        ret = (ret << (i * k)).pre(n);
        if ((ll)ret.size() < n) ret.resize(n);
        return ret;
      }
      if (__int128(i + 1) * k >= n) return P(n);
    }
    return P(n);
  }
  P pow_mod(ll n, const P& m) {
    P x = *this, r = {{1}};
    while (n) {
      if (n & 1) r = r * x % m;
      x = x * x % m;
      n >>= 1;
    }
    return r;
  }
  P shift(T c) const {
    ll n = this->size();
    vec<T> fact(n), rfact(n);
    fact[0] = rfact[0] = T(1);
    reps(i, 1, n) fact[i] = modmul(fact[i - 1], T(i), mod);
    rfact[n - 1] = T(1) * modinv(fact[n - 1], mod);
    rrep(i, 2, n) rfact[i - 1] = modmul(rfact[i], T(i), mod);
    P p(*this);
    rep(i, n) p[i] = modmul(p[i], fact[i], mod);
    p = p.rev();
    P bs(n, T(1));
    reps(i, 1, n) bs[i] = modmul(
        bs[i - 1], modmul(c, modmul(rfact[i], fact[i - 1], mod), mod), mod);
    p = (p * bs).pre(n);
    p = p.rev();
    rep(i, n) p[i] = modmul(p[i], rfact[i], mod);
    return p;
  }
};
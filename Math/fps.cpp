/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Math/fps.cpp */
// 形式的冪級数。poly の多項式演算に級数演算 (log / exp / sqrt / pow) を追加する。
// depends on: modint, modula, ntt, poly
template <class mint = modint<998244353>>
struct fps : poly<mint> {
  using P = fps;

  fps() = default;
  fps(const poly<mint> &p) : poly<mint>(p) {}
  fps(const vec<mint> &v) : poly<mint>(v) {}
  fps(initializer_list<mint> il) : poly<mint>(il) {}
  explicit fps(size_t n) : poly<mint>(n) {}
  fps(size_t n, const mint &v) : poly<mint>(n, v) {}
  template <class It>
  fps(It a, It b) : poly<mint>(a, b) {}

  // exp。定数項は 0 であること。
  P exp(ll n = -1) const {
    assert(this->freq(0) == mint());
    if (n == -1) n = (ll)this->size();
    P g = P{mint(1)};
    for (ll i = 1; i < n; i *= 2)
      g = (g * (this->pre(2 * i) + mint(1) - g.log(2 * i))).pre(2 * i);
    return g.pre(n);
  }
  // log。定数項は 1 であること。
  P log(ll n = -1) const {
    if (n == -1) n = (ll)this->size();
    assert(this->freq(0) == mint(1));
    auto f = this->pre(n);
    return (f.diff() * f.inv(n - 1)).pre(n - 1).integral();
  }
  // sqrt。存在しなければ空を返す。
  P sqrt(ll deg = -1) const {
    const ll n = (ll)this->size();
    if (deg == -1) deg = n;
    if (n == 0) return {};
    if ((*this)[0] == mint()) {
      reps(i, 1, n) {
        if ((*this)[i] != mint()) {
          if (i & 1) return {};
          if (deg - i / 2 <= 0) break;
          P ret = P(*this >> i).sqrt(deg - i / 2);
          if (ret.empty()) return {};
          ret = ret << (i / 2);
          if ((ll)ret.size() < deg) ret.resize(deg, mint());
          return ret;
        }
      }
      return P(deg);
    }
    mint sqr = mint(modsqrt((*this)[0].x, mint::mod()));
    if (sqr * sqr != (*this)[0]) return {};
    P ret = P{sqr};
    const mint inv2 = mint(2).inv();
    for (ll i = 1; i < deg; i <<= 1)
      ret = (ret + this->pre(i << 1) * ret.inv(i << 1)) * inv2;
    return ret.pre(deg);
  }
  // 冪。n 項まで。
  P pow(ll k, ll n = -1) {
    if (n == -1) n = (ll)this->size();
    if (k == 0) {
      P res(n);
      if (n > 0) res[0] = mint(1);
      return res;
    }
    rep(i, (ll)this->size()) {
      if ((*this)[i]) {
        const mint r = (*this)[i].inv();
        P g = P((*this * r) >> i);
        P ret = P(g.log(n) * mint(k)).exp(n);
        ret *= (*this)[i].pow(k);
        ret = (ret << (i * k)).pre(n);
        if ((ll)ret.size() < n) ret.resize(n, mint());
        return ret;
      }
      if (__int128(i + 1) * k >= n) return P(n);
    }
    return P(n);
  }
  // f^n mod m
  P pow_mod(ll n, const P &m) {
    P x = *this, r = P{mint(1)};
    while (n) {
      if (n & 1) r = r * x % m;
      x = x * x % m;
      n >>= 1;
    }
    return r;
  }
};

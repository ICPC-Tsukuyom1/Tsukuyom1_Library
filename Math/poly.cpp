/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Math/poly.cpp */
// 多項式。係数は modint。加減乗算・除算・シフト・評価・微分積分・逆元を提供する。
// depends on: modint, ntt
template <class mint = modint<998244353>>
struct poly : vec<mint> {
  using vec<mint>::vec;
  using P = poly;

  poly() = default;
  poly(const vec<mint> &v) : vec<mint>(v) {}

  // 先頭 def 項を取り出す
  P pre(ll def) const {
    return P(this->begin(), this->begin() + min((ll)this->size(), def));
  }
  // 係数を逆順にする (deg 指定で長さを合わせる)
  P rev(ll deg = -1) const {
    P ret(*this);
    if (deg != -1) ret.resize(deg, mint());
    reverse(all(ret));
    return ret;
  }
  // 末尾の 0 を落とす
  void shrink() {
    while (this->size() && !this->back()) this->pop_back();
  }
  // p 次の係数 (範囲外は 0)
  mint freq(ll p) const { return p < (ll)this->size() ? (*this)[p] : mint(); }

  P operator+(const P &r) const { return P(*this) += r; }
  P operator+(const mint &v) const { return P(*this) += v; }
  P operator-(const P &r) const { return P(*this) -= r; }
  P operator-(const mint &v) const { return P(*this) -= v; }
  P operator*(const P &r) const { return P(*this) *= r; }
  P operator*(const mint &v) const { return P(*this) *= v; }
  P operator/(const P &r) const { return P(*this) /= r; }
  P operator%(const P &r) const { return P(*this) %= r; }
  P operator-() const {
    P ret(this->size());
    rep(i, (ll)this->size()) ret[i] = -(*this)[i];
    return ret;
  }

  P &operator+=(const P &r) {
    if (r.size() > this->size()) this->resize(r.size());
    rep(i, r.size()) (*this)[i] += r[i];
    return *this;
  }
  P &operator-=(const P &r) {
    if (r.size() > this->size()) this->resize(r.size());
    rep(i, r.size()) (*this)[i] -= r[i];
    return *this;
  }
  P &operator*=(const P &r) {
    if (this->empty() || r.empty()) {
      this->clear();
      return *this;
    }
    auto c = convolution<mint>(*this, r);
    return *this = P(all(c));
  }
  P &operator/=(const P &r) {
    if (this->size() < r.size()) {
      this->clear();
      return *this;
    }
    ll n = this->size() - r.size() + 1;
    return *this = (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);
  }
  P &operator%=(const P &r) {
    *this -= *this / r * r;
    shrink();
    return *this;
  }
  P &operator+=(const mint &v) {
    if (this->empty()) this->resize(1);
    (*this)[0] += v;
    return *this;
  }
  P &operator-=(const mint &v) {
    if (this->empty()) this->resize(1);
    (*this)[0] -= v;
    return *this;
  }
  P &operator*=(const mint &v) {
    rep(i, (ll)this->size()) (*this)[i] *= v;
    return *this;
  }

  // 商と余り
  pair<P, P> div_mod(const P &r) const {
    P q = *this / r, x = *this - q * r;
    x.shrink();
    return {q, x};
  }
  // 係数ごとの積
  P dot(const P &r) const {
    P ret(min(this->size(), r.size()));
    rep(i, (ll)ret.size()) ret[i] = (*this)[i] * r[i];
    return ret;
  }
  P operator>>(ll k) const {
    if ((ll)this->size() <= k) return {};
    P ret(*this);
    ret.erase(ret.begin(), ret.begin() + k);
    return ret;
  }
  P operator<<(ll k) const {
    P ret(*this);
    ret.insert(ret.begin(), k, mint());
    return ret;
  }
  // 多項式の値
  mint operator()(const mint &x) const {
    mint r = 0, w = 1;
    for (auto &v : *this) {
      r += w * v;
      w *= x;
    }
    return r;
  }
  P diff() const {
    const ll n = (ll)this->size();
    P ret(max(0ll, n - 1));
    reps(i, 1, n) ret[i - 1] = (*this)[i] * mint(i);
    return ret;
  }
  P integral() const {
    const ll n = (ll)this->size();
    assert(n < mint::mod()); // 1..n の逆元を前計算するため (mod は素数)
    vec<mint> inv(n + 1);
    if (n >= 1) inv[1] = mint(1);
    reps(i, 2, n + 1) inv[i] = mint(-(mint::mod() / i)) * inv[mint::mod() % i];
    P ret(n + 1);
    rep(i, n) ret[i + 1] = freq(i) * inv[i + 1];
    return ret;
  }
  // 形式的逆元 (deg 項まで、既定は自身の長さ)
  P inv(ll deg = -1) const {
    if (deg == -1) deg = (ll)this->size();
    P res = P{freq(0).inv()};
    for (ll i = 1; i < deg; i *= 2)
      res = (res * mint(2) - res * res * pre(2 * i)).pre(2 * i);
    return res.pre(deg);
  }
  // テイラーシフト (x -> x + c)
  P shift(const mint &c) const {
    const ll n = (ll)this->size();
    if (n == 0) return {};
    vec<mint> fact(n), rfact(n);
    fact[0] = rfact[0] = mint(1);
    reps(i, 1, n) fact[i] = fact[i - 1] * mint(i);
    rfact[n - 1] = fact[n - 1].inv();
    rrep(i, 2, n) rfact[i - 1] = rfact[i] * mint(i);
    P p(*this);
    rep(i, n) p[i] *= fact[i];
    p = p.rev();
    P bs(n, mint(1));
    reps(i, 1, n) bs[i] = bs[i - 1] * c * rfact[i] * fact[i - 1];
    p = (p * bs).pre(n);
    p = p.rev();
    rep(i, n) p[i] *= rfact[i];
    return p;
  }
};

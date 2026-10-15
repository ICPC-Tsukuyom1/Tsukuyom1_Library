class BigInt {
  using I = BigInt;
  using lll = __int128_t;
  static constexpr ll B = 1'000'000'000, BASE = B * B;
  vl d;
  ll sign;
  void norm() {
    if (d.empty()) d = {0};
    while (1 < sz(d) && !d.back()) d.pop_back();
    if (zero()) sign = 1;
  }
  ll cmp_abs(const I& b) const {
    if (sz(d) != sz(b.d)) return sz(d) < sz(b.d) ? -1 : 1;
    auto [i, j] = mismatch(d.rbegin(), d.rend(), b.d.rbegin());
    return i == d.rend() ? 0 : (*j < *i) - (*i < *j);
  }
  BigInt(vl x, ll s = 1) : d(move(x)), sign(s) { norm(); }
  auto slice(ll l) const { return I(vl(d.begin() + min(l, sz(d)), d.end())); }
  static auto shift(I x, ll k) {
    if (!x.zero()) x.d.insert(x.d.begin(), k, 0);
    return x;
  }
  template <ll mod>
  static ll modpow(ll a, ll e) {
    ll r = 1;
    for (; e; e >>= 1, a = a * a % mod)
      if (e & 1) r = r * a % mod;
    return r;
  }
  template <ll mod, ll root>
  static void ntt(vl& a) {
    ll n = sz(a);
    for (ll i = 1, j = 0; i < n; i++) {
      ll bit = n >> 1;
      for (; j & bit; bit >>= 1) j ^= bit;
      if ((j ^= bit) > i) swap(a[i], a[j]);
    }
    ll g = modpow<mod>(root, (mod - 1) / n);
    vl w(n / 2, 1);
    reps(i, 1, n / 2) w[i] = w[i - 1] * g % mod;
    for (ll len = 2; len <= n; len <<= 1) {
      ll step = n / len;
      for (ll i = 0; i < n; i += len) rep(j, len / 2) {
          ll u = a[i + j], v = a[i + j + len / 2] * w[j * step] % mod;
          a[i + j] = u + v < mod ? u + v : u + v - mod;
          a[i + j + len / 2] = u < v ? u - v + mod : u - v;
        }
    }
  }
  template <ll mod, ll root>
  static vl conv(const vl& a, const vl& b) {
    ll k = 2 * (sz(a) + sz(b)) - 1, n = bit_ceil((size_t)k);
    vl x(n), y(n);
    for (auto [v, d] : {pair{&x, &a}, pair{&y, &b}}) {
      rep(i, sz(*d)) rep(j, 2)(*v)[2 * i + j] =
          (j ? (*d)[i] / B : (*d)[i] % B) % mod;
      ntt<mod, root>(*v);
    }
    ll ni = modpow<mod>(n, mod - 2);
    rep(i, n) x[i] = x[i] * y[i] % mod * ni % mod;
    reverse(x.begin() + 1, x.end());
    ntt<mod, root>(x);
    x.resize(k);
    return x;
  }
  static I div_small(const I& a, const I& b) {
    vl q(sz(a.d) - sz(b.d) + 1);
    auto r = a.slice(sz(q) - 1);
    rrep(i, 0, sz(q)) {
      auto t = r.slice(sz(b.d) - 1);
      lll x = t.d[0] + (sz(t.d) > 1 ? (lll)t.d[1] * BASE : 0);
      q[i] = min((lll)BASE - 1, x / b.d.back());
      auto v = b * q[i];
      while (r < v) --q[i], v -= b;
      r -= v;
      if (i) r = shift(move(r), 1), r.d[0] = a.d[i - 1];
    }
    return I(move(q));
  }
  // Requires a.d.back() >= BASE / 2 and p >= 2; divmod uses one guard limb.
  static I inv(const I& a, ll p) {
    ll h = p == 2 ? 1 : p / 2 + 1;
    auto t = a.slice(max(0LL, sz(a.d) - p - 1));
    auto z = p == 2 ? I((ll)((lll)BASE * BASE / a.d.back())) : inv(t, h);
    return shift(z + z, p - h) - (z * z * t).slice(sz(t.d) + 2 * h - p);
  }

 public:
  BigInt(ll x = 0) : d{abs(x % BASE)}, sign(x < 0 ? -1 : 1) {
    if (x / BASE) d.push_back(abs(x / BASE));
  }
  bool zero() const { return !d.back(); }
  BigInt(const string& s) : sign(s[0] == '-' ? -1 : 1) {
    ll first = s[0] == '-' || s[0] == '+';
    for (ll r = sz(s); first < r; r -= 18) {
      d.push_back(0);
      from_chars(s.data() + max(first, r - 18), s.data() + r, d.back());
    }
    norm();
  }
  string to_string() const {
    string s = std::to_string(sign * d.back());
    s.reserve(18 * sz(d) + 1);
    rrep(i, 0, sz(d) - 1) {
      auto t = std::to_string(d[i]);
      s.append(18 - sz(t), '0').append(t);
    }
    return s;
  }
  I& operator+=(I b) {
    ll s = sign * b.sign;
    if (s < 0 ? cmp_abs(b) < 0 : sz(d) < sz(b.d)) swap(*this, b);
    ll carry = 0;
    rep(i, sz(d)) {
      auto x = d[i] + s * (i < sz(b.d) ? b.d[i] : 0) + carry;
      carry = (BASE <= x) - (x < 0);
      d[i] = x - carry * BASE;
    }
    if (carry) d.push_back(carry);
    return norm(), *this;
  }
  auto operator-() const { return I(d, -sign); }
  I& operator-=(I b) { return b.sign = -b.sign, *this += move(b); }
  auto& operator++() { return *this += 1; }
  auto operator++(int) { return exchange(*this, *this + 1); }
  auto& operator--() { return *this -= 1; }
  auto operator--(int) { return exchange(*this, *this - 1); }
  friend I operator+(I a, I b) { return a += move(b), move(a); }
  friend I operator-(I a, I b) { return a -= move(b), move(a); }
  friend bool operator==(const I&, const I&) = default;
  friend strong_ordering operator<=>(const I& a, const I& b) {
    return (a.sign == b.sign ? a.sign * a.cmp_abs(b) : a.sign - b.sign) <=> 0;
  }
  friend I operator*(const I& a, const I& b) {
    if (a.zero() || b.zero()) return 0;
    ll n = sz(a.d), m = sz(b.d);
    vl d(n + m);
    lll carry = 0;
    if (min(n, m) <= 128) {
      rep(k, n + m - 1) {
        auto x = carry;
        reps(i, max(0LL, k - m + 1), min(n, k + 1)) x +=
            (lll)a.d[i] * b.d[k - i];
        carry = x / BASE;
        d[k] = x - carry * BASE;
      }
      d.back() = carry;
    } else {
      constexpr ll p0 = 167'772'161, p1 = 469'762'049, p2 = 754'974'721;
      auto r0 = conv<p0, 3>(a.d, b.d), r1 = conv<p1, 3>(a.d, b.d),
           r2 = conv<p2, 11>(a.d, b.d);
      static const ll i01 = modpow<p1>(p0, p1 - 2);
      static const ll i012 = modpow<p2>(p0 * p1 % p2, p2 - 2);
      rep(i, sz(r0)) {
        lll v = r0[i] + (lll)p0 * ((r1[i] - r0[i] + p1) * i01 % p1);
        ll t = (r2[i] - (ll)(v % p2) + p2) * i012 % p2;
        v += (lll)p0 * p1 * t + carry;
        d[i / 2] += (ll)(v % B) * (i & 1 ? B : 1);
        carry = v / B;
      }
      d.back() += carry * B;
    }
    return I(move(d), a.sign * b.sign);
  }
  auto& operator*=(const I& b) { return *this = *this * b; }
  auto divmod(const I& b) const {
    if (cmp_abs(b) < 0) return pair{I(0), *this};
    auto a = *this, y = b;
    a.sign = y.sign = 1;
    if (sz(y.d) == 1) {
      auto q = move(a);
      lll rem = 0;
      for (auto& digit : views::reverse(q.d)) {
        rem = rem * BASE + digit;
        digit = rem / y.d[0];
        rem -= (lll)digit * y.d[0];
      }
      q.norm();
      q.sign = sign * b.sign;
      return pair{move(q), I(sign * rem)};
    }
    ll factor = BASE / (y.d.back() + 1);
    auto u = a * factor, v = y * factor;
    ll m = sz(v.d), n = max(sz(u.d), m + 1);
    lll top = (sz(u.d) > m ? (lll)u.d.back() * BASE : 0) + u.d[m - 1];
    auto q = sz(a.d) == sz(y.d) ? I((ll)min((lll)BASE - 1, top / v.d.back()))
             : n <= 64          ? div_small(u, v)
                                : (u * inv(v, n - m + 1)).slice(n + 1);
    auto r = a - q * y;
    while (r < 0) --q, r += y;
    while (y <= r) ++q, r -= y;
    q.sign = sign * b.sign;
    r.sign = r.zero() ? 1 : sign;
    return pair{move(q), move(r)};
  }
  auto& operator/=(const I& b) { return *this = divmod(b).first; }
  auto& operator%=(const I& b) { return *this = divmod(b).second; }
  friend auto operator/(const I& a, const I& b) { return a.divmod(b).first; }
  friend auto operator%(const I& a, const I& b) { return a.divmod(b).second; }
};

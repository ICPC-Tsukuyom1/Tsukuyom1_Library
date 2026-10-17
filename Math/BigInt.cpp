/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Math/BigInt.cpp */
struct BigInt {
private:
  static constexpr ll BASE = 1'000'000'000'000'000'000LL;
  vl d;
  ll sign;

  void norm() {
    while (1 < sz(d) && !d.back()) d.pop_back();
    if (zero()) sign = 1;
  }

  ll cmp_abs(const BigInt& b) const {
    if (sz(d) != sz(b.d)) return sz(d) < sz(b.d) ? -1 : 1;
    auto [i, j] = mismatch(d.rbegin(), d.rend(), b.d.rbegin());
    return i == d.rend() ? 0 : (*j < *i) - (*i < *j);
  }

public:
  BigInt(ll x = 0) : d{abs(x % BASE)}, sign(x < 0 ? -1 : 1) {
    if (x / BASE) d.push_back(abs(x / BASE));
  }
  bool zero() const { return !d.back(); }

  BigInt(const string& s) : sign(s[0] == '-' ? -1 : 1) {
    ll first = s[0] == '-' || s[0] == '+';
    for (ll r = sz(s); first < r; r -= 18) {
      ll x = 0;
      reps(i, max(first, r - 18), r) {
        x = x * 10 + s[i] - '0';
      }
      d.push_back(x);
    }
    norm();
  }

  string to_string() const {
    string s = std::to_string(sign * d.back());
    s.reserve(18 * sz(d) + 1);
    rrep(i, 0, sz(d) - 1) {
      auto t = std::to_string(d[i]);
      s.append(18 - sz(t), '0');
      s += t;
    }
    return s;
  }

  auto& operator+=(BigInt b) {
    ll s = sign * b.sign;
    if (s < 0 ? cmp_abs(b) < 0 : sz(d) < sz(b.d)) swap(*this, b);
    ll carry = 0;
    rep(i, sz(d)) {
      auto x = d[i] + s * (i < sz(b.d) ? b.d[i] : 0) + carry;
      carry = (BASE <= x) - (x < 0);
      d[i] = x - carry * BASE;
    }
    if (carry) d.push_back(carry);
    norm();
    return *this;
  }
  auto operator-() const {
    auto r = *this;
    if (!r.zero()) r.sign = -r.sign;
    return r;
  }
  auto& operator-=(const BigInt& b) { return *this += -b; }
  auto& operator++() { return *this += 1; }
  auto operator++(int) { auto r = *this; ++*this; return r; }
  auto& operator--() { return *this -= 1; }
  auto operator--(int) { auto r = *this; --*this; return r; }
  friend auto operator+(BigInt a, const BigInt& b) {
    a += b; return a;
  }
  friend auto operator-(BigInt a, const BigInt& b) {
    a -= b; return a;
  }
  friend bool operator==(const BigInt&, const BigInt&) = default;
  friend auto operator<=>(const BigInt& a, const BigInt& b) {
    return (a.sign == b.sign ? a.sign * a.cmp_abs(b) : a.sign - b.sign) <=> 0;
  }

  // ------ mul ------

private:
  using lll = __int128_t;
  BigInt(vl limbs, ll s = 1) : d(move(limbs)), sign(s) {
    if (d.empty()) d = {0};
    norm();
  }

  auto slice(ll l, ll r = LLONG_MAX) const {
    r = min(r, sz(d));
    return BigInt(vl(d.begin() + min(l, r), d.begin() + r));
  }

  static auto shift(BigInt x, ll k) {
    if (!x.zero()) x.d.insert(x.d.begin(), k, 0);
    return x;
  }

public:
  friend BigInt operator*(const BigInt& a, const BigInt& b) {
    if (a.zero() || b.zero()) return 0;
    ll n = sz(a.d), m = sz(b.d);
    if (min(n, m) <= 128) {
      vl c(n + m);
      lll carry = 0;
      rep(k, n + m - 1) {
        auto x = carry;
        reps(i, max(0LL, k - m + 1), min(n, k + 1))
          x += (lll)a.d[i] * b.d[k - i];
        carry = x / BASE;
        c[k] = x - carry * BASE;
      }
      c.back() = carry;
      return BigInt(move(c), a.sign * b.sign);
    }
    ll k = (max(n, m) + 1) / 2;
    auto a0 = a.slice(0, k), a1 = a.slice(k);
    auto b0 = b.slice(0, k), b1 = b.slice(k);
    auto p0 = a0 * b0, p2 = a1 * b1;
    auto p1 = (a0 + a1) * (b0 + b1) - p0 - p2;
    p0 += shift(move(p1), k);
    p0 += shift(move(p2), 2 * k);
    p0.sign = a.sign * b.sign;
    return p0;
  }

  auto& operator*=(const BigInt& b) { return *this = *this * b; }

  // ------ div ------

  auto divmod(const BigInt& b) const {
    if (cmp_abs(b) < 0) return pair{BigInt(0), *this};
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
      return pair{move(q), BigInt(sign * rem)};
    }
    BigInt factor = BASE / (y.d.back() + 1);
    auto u = a * factor, v = y * factor;
    ll m = sz(v.d), n = max(sz(u.d), m + 1), p = m + 1;
    BigInt x = (lll)BASE * BASE / v.d.back();
    while (1) {
      x = (x * (shift(2, p) - v * x)).slice(p) + 1;
      if (p == n) break;
      ll next = min(n, 2 * p - m);
      x = shift(move(x), next - p);
      p = next;
    }
    auto q = (u * x).slice(n), r = a - q * y;
    while (r < 0) { --q; r += y; }
    while (y <= r) { ++q; r -= y; }
    q.sign = sign * b.sign;
    r.sign = r.zero() ? 1 : sign;
    return pair{move(q), move(r)};
  }
  auto& operator/=(const BigInt& b) { return *this = divmod(b).first; }
  auto& operator%=(const BigInt& b) { return *this = divmod(b).second; }
  friend auto operator/(const BigInt& a, const BigInt& b) {
    return a.divmod(b).first;
  }
  friend auto operator%(const BigInt& a, const BigInt& b) {
    return a.divmod(b).second;
  }
};

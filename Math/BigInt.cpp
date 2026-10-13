struct BigInt {
private:
  using uint = uint64_t;
  using ulll = __uint128_t;
  using lll = __int128_t;
  vec<uint> d;
  int sign;

  void norm() {
    while (sz(d) > 1 && d.back() == 0) d.pop_back();
    if (zero()) sign = 1;
  }

  int cmp_abs(const BigInt& b) const {
    if (sz(d) != sz(b.d)) return sz(d) < sz(b.d) ? -1 : 1;
    auto [i, j] = mismatch(d.rbegin(), d.rend(), b.d.rbegin());
    return i == d.rend() ? 0 : (*i > *j) - (*i < *j);
  }

  BigInt(vec<uint> limbs, int s = 1) : d(move(limbs)), sign(s) {
    if (d.empty()) d = {0};
    norm();
  }

public:
  BigInt(ll x = 0)
      : d{x < 0 ? (uint)(-(x + 1)) + 1 : (uint)x}, sign(x < 0 ? -1 : 1) {}
  bool zero() const { return sz(d) == 1 && d[0] == 0; }

  BigInt& operator+=(BigInt b) {
    int s = sign == b.sign ? 1 : -1;
    if (s < 0 && cmp_abs(b) < 0) swap(*this, b);
    int n = max(sz(d), sz(b.d));
    d.resize(n);
    lll carry = 0;
    rep(i, n) {
      auto x = (lll)d[i] + s * (i < sz(b.d) ? (lll)b.d[i] : 0) + carry;
      d[i] = x;
      carry = x >> 64;
    }
    if (carry) d.push_back(carry);
    norm();
    return *this;
  }
  BigInt& operator-=(const BigInt& b) { return *this += -b; }
  BigInt operator+() const { return *this; }
  BigInt operator-() const {
    auto r = *this;
    if (!r.zero()) r.sign = -r.sign;
    return r;
  }
  BigInt& operator++() { return *this += 1; }
  BigInt operator++(int) { auto r = *this; ++*this; return r; }
  BigInt& operator--() { return *this -= 1; }
  BigInt operator--(int) { auto r = *this; --*this; return r; }
  friend BigInt operator+(BigInt a, const BigInt& b) {
    a += b; return a;
  }
  friend BigInt operator-(BigInt a, const BigInt& b) {
    a -= b; return a;
  }
  friend bool operator==(const BigInt&, const BigInt&) = default;
  friend auto operator<=>(const BigInt& a, const BigInt& b) {
    return (a.sign == b.sign ? a.sign * a.cmp_abs(b) : a.sign - b.sign) <=> 0;
  }

  // 加減算・比較はここまで。以下を省く場合は末尾に }; を追加。
private:
  static BigInt slice(const BigInt& a, int l, int r) {
    l = min(l, (int)sz(a.d)); r = min(r, (int)sz(a.d));
    return BigInt(vec<uint>(a.d.begin() + l, a.d.begin() + r));
  }

  static BigInt schoolbook(const BigInt& a, const BigInt& b) {
    vec<uint> c(sz(a.d) + sz(b.d));
    auto start = c.begin();
    for (auto v : a.d) {
      auto out = start++;
      ulll carry = 0;
      // A product plus carry and one limb fits in unsigned 128 bits.
      for (auto u : b.d) {
        auto x = (ulll)v * u + *out + carry;
        *out++ = x;
        carry = x >> 64;
      }
      *out = carry;
    }
    return BigInt(move(c), a.sign * b.sign);
  }

  static BigInt shift(BigInt x, int k) {
    if (!x.zero()) x.d.insert(x.d.begin(), k, 0);
    return x;
  }

  static BigInt multiply(const BigInt& a, const BigInt& b) {
    if (a.zero() || b.zero()) return 0;
    if (min(sz(a.d), sz(b.d)) <= 16) return schoolbook(a, b);
    // Karatsuba: p1 is the coefficient of the middle block.
    int n = max(sz(a.d), sz(b.d)), k = (n + 1) / 2;
    auto a0 = slice(a, 0, k), a1 = slice(a, k, n);
    auto b0 = slice(b, 0, k), b1 = slice(b, k, n);
    auto p0 = multiply(a0, b0), p2 = multiply(a1, b1);
    auto p1 = multiply(a0 + a1, b0 + b1) - p0 - p2;
    p0 += shift(move(p1), k);
    p0 += shift(move(p2), 2 * k);
    p0.sign = a.sign * b.sign;
    return p0;
  }

public:
  BigInt& operator*=(const BigInt& b) { return *this = multiply(*this, b); }
  friend BigInt operator*(const BigInt& a, const BigInt& b) {
    return multiply(a, b);
  }

  // 乗算はここまで。以下を省く場合は末尾に }; を追加。
private:
  pair<BigInt, uint> div_small(uint x) const {
    auto q = *this;
    ulll rem = 0;
    for (auto& limb : views::reverse(q.d)) {
      auto cur = (rem << 64) + limb;
      limb = cur / x;
      rem = cur % x;
    }
    q.norm();
    return {move(q), (uint)rem};
  }

  BigInt drop_abs(int n) const { return slice(*this, n, sz(d)); }

  static pair<BigInt, BigInt> divmod_abs(const BigInt& a, const BigInt& b) {
    if (a.cmp_abs(b) < 0) return {0, a};
    if (sz(b.d) == 1) {
      auto [q, rem] = a.div_small(b.d[0]);
      return {move(q), BigInt(vec<uint>{rem})};
    }
    // Normalize the top limb to >= 2^63.
    BigInt factor;
    factor.d[0] = ((ulll)1 << 64) / ((ulll)b.d.back() + 1);
    auto u = a * factor, v = b * factor;
    int m = sz(v.d), n = max<int>(sz(u.d), m + 1), p = m + 1;
    auto x = shift(1, 2).div_small(v.d.back()).first;
    // Keep |x - 2^(64*p)/v| <= 1 as the precision doubles.
    while (true) {
      auto scale = shift(1, p);
      x = (x * (scale * 2 - v * x)).drop_abs(p) + 1;
      if (p == n) break;
      int next = min(n, 2 * p - m);
      x = shift(move(x), next - p);
      p = next;
    }
    auto q = (u * x).drop_abs(n), r = a - q * b;
    while (r < 0) { --q; r += b; }
    while (r >= b) { ++q; r -= b; }
    return {move(q), move(r)};
  }

public:
  pair<BigInt, BigInt> divmod(const BigInt& b) const {
    assert(!b.zero());
    auto a = *this, y = b;
    a.sign = y.sign = 1;
    auto [q, r] = divmod_abs(a, y);
    q.sign = q.zero() ? 1 : sign * b.sign;
    r.sign = r.zero() ? 1 : sign;
    return {move(q), move(r)};
  }
  BigInt& operator/=(const BigInt& b) { return *this = divmod(b).first; }
  BigInt& operator%=(const BigInt& b) { return *this = divmod(b).second; }
  friend BigInt operator/(const BigInt& a, const BigInt& b) {
    return a.divmod(b).first;
  }
  friend BigInt operator%(const BigInt& a, const BigInt& b) {
    return a.divmod(b).second;
  }

  // 除算・剰余はここまで。以下を省く場合は末尾に }; を追加。
private:
  static constexpr ll DEC = 1000000000000000000LL;

public:
  BigInt(const string& s) : BigInt() {
    assert(!s.empty());
    int first = s[0] == '-' || s[0] == '+';
    assert(first < sz(s));
    while (first + 1 < sz(s) && s[first] == '0') ++first;
    int n = (sz(s) - first + 17) / 18;
    vec<BigInt> p{BigInt(DEC)};
    while ((1ULL << sz(p)) < (uint)n) p.push_back(p.back() * p.back());
    auto parse = [&](auto&& self, int l, int r) -> BigInt {
      if (r - l == 1) {
        int end = sz(s) - 18 * l;
        ll x = 0;
        reps(i, max(first, end - 18), end) {
          assert('0' <= s[i] && s[i] <= '9');
          x = x * 10 + s[i] - '0';
        }
        return BigInt(x);
      }
      auto k = bit_floor((unsigned)(r - l - 1));
      auto a = self(self, l + k, r) * p[countr_zero(k)];
      a += self(self, l, l + k);
      return a;
    };
    *this = parse(parse, 0, n);
    if (s[0] == '-' && !zero()) sign = -1;
  }

  string to_string() const {
    vec<BigInt> p{BigInt(DEC)};
    while (p.back().cmp_abs(*this) <= 0) p.push_back(p.back() * p.back());
    string s;
    s.reserve((size_t(18) << (sz(p) - 1)) + 1);
    auto write = [&](auto&& self, const BigInt& x, int k) -> void {
      if (k == 0) {
        auto t = std::to_string((ll)x.d[0]);
        s.append(18 - sz(t), '0');
        s += t;
        return;
      }
      auto [q, r] = x.divmod(p[k - 1]);
      self(self, q, k - 1); self(self, r, k - 1);
    };
    write(write, *this, sz(p) - 1);
    s.erase(0, s.find_first_not_of('0'));
    if (s.empty()) s = "0";
    if (sign < 0) s.insert(s.begin(), '-');
    return s;
  }
};

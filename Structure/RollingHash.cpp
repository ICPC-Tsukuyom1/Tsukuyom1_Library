struct RollingHash {
  ll base = 150, Hash = (1LL << 61) - 1;
  string S;
  vector<ll> hashed, power;
  ll mul(ll a, ll b) { return __int128_t(a) * b % Hash; };
  RollingHash(const string &S) {
    ll N = S.size();
    hashed.assign(N + 1, 0);
    power.assign(N + 1, 0);
    power[0] = 1;
    rep(i, N) {
      power[i + 1] = mul(power[i], base);
      hashed[i + 1] = mul(hashed[i], base) + S[i];
      if (hashed[i + 1] >= Hash) hashed[i + 1] -= Hash;
    }
  }
  ll get(ll l, ll r) {
    ll ret = hashed[r] + Hash - mul(hashed[l], power[r - l]);
    if (ret >= Hash) ret -= Hash;
    return ret;
  }
};
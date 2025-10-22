vl Zalgo(string& s) {
  ll n = sz(s), l = -1, r = -1;
  vl z(n, n);
  reps(i, 1, n) {
    ll& x = z[i] = i < r ? min<ll>(r - i, z[i - l]) : 0;
    while (i + x < n && s[i + x] == s[x]) x++;
    if (i + x > r) l = i, r = i + x;
  }
  return z;
}
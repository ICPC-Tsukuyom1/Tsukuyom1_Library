ll modmul(ll a, ll b, ll mod) {
  ll ret = a * b - mod * ll(1.L / mod * a * b);
  return ret + mod * (ret < 0) - mod * (ret >= mod);
}
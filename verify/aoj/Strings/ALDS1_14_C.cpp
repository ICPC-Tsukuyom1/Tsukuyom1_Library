//@aoj ALDS1_14_C

#include "../../../template.cpp"
#include "../../../Structure/RollingHash.cpp"

namespace {
const ll MOD = (1LL << 61) - 1;
const ll VB = 1000003;  // vertical base
ll mul(ll a, ll b) { return (ll)((__int128_t)a * b % MOD); }
}  // namespace

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll H, W;
  cin >> H >> W;
  vector<string> g(H);
  rep(i, H) cin >> g[i];
  ll R, C;
  cin >> R >> C;
  vector<string> p(R);
  rep(i, R) cin >> p[i];

  // horizontal hashes (base 150 via RollingHash) of every length-C window
  vv<ll> gh(H, vl(W - C + 1));
  rep(i, H) {
    RollingHash rh(g[i]);
    rep(j, W - C + 1) gh[i][j] = rh.get(j, j + C);
  }
  vl ph(R);
  rep(i, R) {
    RollingHash rh(p[i]);
    ph[i] = rh.get(0, C);
  }

  // vertical polynomial hash using base VB
  vl pw(R + 1, 1);
  rep(i, R) pw[i + 1] = mul(pw[i], VB);
  ll target = 0;
  rep(i, R) target = (mul(target, VB) + ph[i]) % MOD;

  // prefix over the vertical direction for every column window
  vv<ll> pre(W - C + 1, vl(H + 1));
  rep(j, W - C + 1) {
    pre[j][0] = 0;
    rep(i, H) pre[j][i + 1] = (mul(pre[j][i], VB) + gh[i][j]) % MOD;
  }
  // row-major order (i first, then j)
  rep(i, H - R + 1) rep(j, W - C + 1) {
    ll cur = (pre[j][i + R] - mul(pre[j][i], pw[R]) % MOD + MOD) % MOD;
    if (cur == target) cout << i << ' ' << j << '\n';
  }
}

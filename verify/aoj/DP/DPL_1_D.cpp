//@aoj DPL_1_D

#include "../../../template.cpp"
#include "../../../LIS.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  cin >> n;
  vl a(n);
  rep(i, n) cin >> a[i];
  cout << LIS(a, true) << '\n';
}

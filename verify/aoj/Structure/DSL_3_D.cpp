//@aoj DSL_3_D

#include "../../../template.cpp"

#define T ll
#define e 4611686018427387904LL
#define op(a, b) min(a, b)

#include "../../../Structure/swag.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, l;
  cin >> n >> l;
  vl a(n);
  rep(i, n) cin >> a[i];
  SWAG sw;
  rep(i, l) sw.push_back(a[i]);
  rep(i, n - l + 1) {
    if (i) {
      sw.pop_front();
      sw.push_back(a[i + l - 1]);
      cout << ' ';
    }
    cout << sw.query();
  }
  cout << '\n';
}

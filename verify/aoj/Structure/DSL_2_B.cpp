//@aoj DSL_2_B

#include "../../../template.cpp"
#include "../../../Structure/BIT.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, q;
  cin >> n >> q;
  BIT<ll> bit(n);
  while (q--) {
    ll com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      bit.apply(x - 1, y);
    } else {
      cout << bit.prod(x - 1, y) << '\n';
    }
  }
}

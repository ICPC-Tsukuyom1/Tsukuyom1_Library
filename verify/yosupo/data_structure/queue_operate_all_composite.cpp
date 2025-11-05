//@yosupo queue_operate_all_composite

#include "../../../template.cpp"

const ll mod = 998244353;

#include "../../../Math/modint.cpp"

using T = pair<mint, mint>;
const T e = pair{1, 0};
#define op(a, b) \
  pair { a.first *b.first, b.first *a.second + b.second }

#include "../../../Structure/swag.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll q;
  cin >> q;
  SWAG s;
  while (q--) {
    ll t;
    cin >> t;
    if (t == 0) {
      ll a, b;
      cin >> a >> b;
      s.push_back({a, b});
    } else if (t == 1) {
      s.pop_front();
    } else {
      ll x;
      cin >> x;
      auto a = s.query();
      cout << a.first * x + a.second << "\n";
    }
  }
}
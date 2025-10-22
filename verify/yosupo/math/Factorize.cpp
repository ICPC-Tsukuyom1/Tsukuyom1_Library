//@yosupo factorize

#include "../../../Math/FastFactorize.cpp"
#include "../../../template.cpp"

int main() {
  ll Q;
  cin >> Q;
  while (Q--) {
    ll N;
    cin >> N;
    auto f = fac(N);
    cout << f.size();
    sort(all(f));
    for (ll p : f) { cout << ' ' << p; }
    cout << endl;
  }
}

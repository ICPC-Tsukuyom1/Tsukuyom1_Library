//@yosupo primality_test
#include "../../../template.cpp"
#include "../../../Math/MillerRabin.cpp"

int main() {
  ll Q;
  cin >> Q;
  while (Q--) {
    ll N;
    cin >> N;
    if (isprime(N)) {
      cout << "Yes" << endl;
    } else cout << "No" << endl;
  }
}
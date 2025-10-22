//@yosupo primality_test
#include "../../../Math/MillerRabin.cpp"
#include "../../../template.cpp"

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
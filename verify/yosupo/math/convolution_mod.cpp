//@yosupo convolution_mod

#include "../../../template.cpp"
#include "../../fastio.hpp"
#include "../../../Math/modula.cpp"
#include "../../../Math/fps.cpp"

FastIn in;
FastOut out;

int main() {
  ll N, M;
  in >> N >> M;
  FPS<ll> a(N), b(M);
  rep(i, N) in >> a[i];
  rep(i, M) in >> b[i];
  vl c = a * b;
  rep(i, sz(c)) { out << c[i] << " \n"[i == sz(c) - 1]; }
}
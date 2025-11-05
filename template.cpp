#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using vl = vector<ll>;
template <class T>
using vec = vector<T>;
template <class T>
using vv = vec<vec<T>>;
template <class T>
using vvv = vv<vec<T>>;
template <class T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
#define rep(i, r) for (ll i = 0; i < (r); i++)
#define reps(i, l, r) for (ll i = (l); i < (r); i++)
#define rrep(i, l, r) for (ll i = (r)-1; i >= l; i--)
#define all(a) (a).begin(), (a).end()
#define sz(a) (ll)(a).size()
template <typename T>
bool chmax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}
template <typename T>
bool chmin(T& a, const T& b) {
  return a > b ? a = b, true : false;
}
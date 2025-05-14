#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef string::const_iterator State;
class ParseError {};
#define rep(i, n) for(ll i = 0; i < (n); i++)
#define reps(i, l, r) for(ll i = (l); i < (r); i++)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define endl "\n";
const ll INF = LLONG_MAX / 4;
const ld inf = numeric_limits<long double>::max() / (ld)4;
const ll mod1 = 1000000007;
const ll mod2 = 998244353;
ll dx[4] = {1, 0, -1, 0};
ll dy[4] = {0, -1, 0, 1};
void chmin(ll& a, ll b){ if(a > b) a = b; }
void chmax(ll& a, ll b){ if(a < b) a = b; }
ll gcd(ll a, ll b) {return (b == 0 ? a : gcd(b, a % b));}
ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
const ld pi = 3.1415926535897;
bool islower(char c) { return 'a' <= c && c <= 'z'; }
bool isupper(char c) { return 'A' <= c && c <= 'Z'; }
bool isletter(char c) { return islower(c) || isupper(c); }
template <class T>
bool chmax(T &a, const T &b) { return a < b ? a = b, true : false; }
template <class T>
bool chmin(T &a, const T &b) { return a > b ? a = b, true : false; }

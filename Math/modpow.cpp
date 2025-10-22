#include "modmul.cpp"

ll modpow(ll a, ll b, ll mod) {
	ll ans = 1;
	for(; b; a = modmul(a, a, mod), b /= 2)
		if (b & 1) ans = modmul(ans, a, mod);
	return ans;
}
ll rnd(ll l, ll r) { //[l, r)
	static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
	return uniform_int_distribution<ll>(l, r - 1)(gen);
}
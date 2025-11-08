ll rnd(ll l, ll r) {  //[l, r)
  random_device gen_seed;
  static mt19937_64 gen(gen_seed());
  return uniform_int_distribution<ll>(l, r - 1)(gen);
}

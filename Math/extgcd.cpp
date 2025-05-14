ll extgcd(ll A, ll B, ll& X, ll& Y) {
    ll D = A;
    if (B != 0) {
        D = extgcd(B, A % B, Y, X);
        Y -= (A / B) * X;
    }
    else {
        X = 1; Y = 0;
    }
    return D;
}

ll invmod(ll A, ll M) {
    assert(gcd(A, M) == 1);
    ll X, Y;
    extgcd(A,M,X,Y);
    X %= M;
    if (X < 0) {
        while (X < 0) {
            X += M;
        }
    }
    return X;
}

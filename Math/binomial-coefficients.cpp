const ll MOD = 1000000007; //問題に応じて変える
// 1. 1 <= k <= n <= 10^7, mod p(prime number)
const int MAX = 10000010;
long long fac[MAX], finv[MAX], inv[MAX];
void init() { 
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++){
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}
long long com(int n, int k){ 
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

//1B : modint (modint.cpp) を用いる場合
const int MAX = 100010;
modint<mod1> fac[MAX];
void init() { 
    fac[0] = fac[1] = 1;
    for (ll i = 2; i < MAX; i++){
        fac[i] = fac[i - 1] * i;
    }
}
modint<mod1> com(int n, int k){ 
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] / fac[k] / fac[n - k];
}

//2. 1 <= k <= n <= 2000, mod p(positive integer)
const int MAX_C = 2010;
long long C[MAX_C][MAX_C];
void calc() {
    memset(Com, 0, sizeof(Com));
    C[0][0] = 1;
    for (int i = 1; i < MAX_C; ++i) {
        C[i][0] = 1;
        for (int j = 1; j < MAX_C; ++j) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
        }
    }
}


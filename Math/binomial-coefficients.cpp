const int MAX = 1000010;
mint fac[MAX];
void init() { 
    fac[0] = fac[1] = 1;
    for (ll i = 2; i < MAX; i++){
        fac[i] = fac[i - 1] * i;
    }
}
mint com(int n, int k){ 
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] / fac[k] / fac[n - k];    
}
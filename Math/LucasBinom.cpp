/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Math/LucasBinom.cpp */
template <class Mint>
struct LucasBinom {
    Binom<Mint> small;
    
    LucasBinom(int n = Mint::mod() - 1) : small(n) {}
    
    Mint C(long long n, long long r) const {
        if (n < 0 || r < 0 || r > n) return Mint(0);
        
        const int p = Mint::mod();
        Mint res = 1;
        while (n > 0 || r > 0) {
            int ni = n % p, ri = r % p;
            
            if (ri > ni) return Mint(0);
            res *= small.C(ni, ri);
            n /= p; r /= p;
        }
        return res;
    }
};
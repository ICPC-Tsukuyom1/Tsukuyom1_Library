//@yosupo associative_array

#include "../../../template.cpp"
#include "../../../Structure/pbds.cpp"

using ull = unsigned long long;

struct chash {
    ull operator()(ll X) const {
        ull x = X;
        x ^= rotr(x, 23) ^ rotr(x, 47);
        x ^= x >> 13;
        x ^= x << 37;
        x ^= x >> 21;
        return x;
    }
};

int main() {
    ll q;
    cin >> q;
    FastMap<ll, ll, chash> mp;
    rep(Q, q)
    {
        ll t;
        cin >> t;
        if (t == 0)
        {
            ll k, v;
            cin >> k >> v;
            mp[k] = v;
        } else
        {
            ll k;
            cin >> k;
            cout << (mp.find(k) == mp.end() ? 0 : mp[k]) << "\n";
        }
    }
}
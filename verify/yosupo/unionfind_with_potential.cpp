//@yosupo unionfind_with_potential

#include "../../template.cpp"
#include "../../Math/modint.cpp"
#include "../../Structure/weightedunionfind.cpp"

using mint = modint<998244353>;

int main()
{
    ll n, q;
    cin >> n >> q;
    WeightedUnionFind<mint> uf(n);
    while (q--)
    {
        ll t, u, v;
        cin >> t >> u >> v;
        if (t == 0)
        {
            mint x;
            cin >> x;
            if (uf.connected(u, v))
            {
                if (uf.diff(v, u) != x)
                {
                    cout << 0 << endl;
                    continue;
                }
            }
            uf.merge(v, u, x);
            cout << 1 << endl;
        }
        else
        {
            if (uf.connected(u, v))
            {
                cout << uf.diff(v, u) << endl;
            } else
            {
                cout << -1 << endl;
            }
        }
    }
}
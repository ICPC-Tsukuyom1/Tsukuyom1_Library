//@yosupo unionfind_with_potential

#include "../../../template.cpp"

const ll mod = 998244353;

#include "../../../Math/modint.cpp"
#include "../../../Structure/weightedunionfind.cpp"

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
			if (uf.same(u, v))
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
			if (uf.same(u, v))
			{
				cout << uf.diff(v, u) << endl;
			} else
			{
				cout << -1 << endl;
			}
		}
	}
}
//@yosupo rectangle_sum

#include "../../../template.cpp"
#include "../../../Structure/kd-tree.cpp"

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(12);

    ll n, q;
    cin >> n >> q;


    vec<tuple<ll, ll, ll>> src;

    rep(i, n) {
        ll x, y, w;
        cin >> x >> y >> w;
        src.emplace_back(x, y, w);
    }

    kDTree<> kd(all(src), [](ll a, ll b){ return a + b; }, 0);

    rep(i, q) {
        ll l, d, r, u;
        cin >> l >> d >> r >> u;
        cout << kd.prod(l, r, d, u) << endl;
    }
}
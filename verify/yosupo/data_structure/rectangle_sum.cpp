//@yosupo rectangle_sum

#include "../../../template.cpp"
#include "../../fastio.hpp"

FastIn in;
FastOut out;
#include "../../../Structure/kd-tree.cpp"

int main(){

    ll n, q;
    in >> n >> q;


    vec<tuple<ll, ll, ll>> src;

    rep(i, n) {
        ll x, y, w;
        in >> x >> y >> w;
        src.emplace_back(x, y, w);
    }

    kDTree<> kd(all(src), [](ll a, ll b){ return a + b; }, 0);

    rep(i, q) {
        ll l, d, r, u;
        in >> l >> d >> r >> u;
        out << kd.prod(l, r, d, u) << '\n';
    }
}
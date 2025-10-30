template <typename T>
struct BIT2d {
    ll h, w;
    vv<T> bit;
    BIT2d(ll H, ll W) : h(H + 1), w(W + 1) {
        bit.resize(h + 3, vec<T>(w + 3, T(0)));
    }
    void add(ll x, ll y, T c) {
        if (x < 0 || x >= h || y < 0 || y >= w) return;
        for (ll a = (++y, ++x); a <= h; a += a & -a) {
            for (ll b = y; b <= w; b += b & -b) {
                bit[a][b] += c;
            }
        }
    }
    void imos(ll x1, ll y1, ll x2, ll y2, T c) {
        add(x1, y1, c);
        add(x1, y2, -c);
        add(x2, y1, -c);
        add(x2, y2, c);
    }
    T sum(ll x, ll y) {
        if (x <= 0 || y <= 0) return T(0);
        if (x > h) x = h;
        if (y > w) y = w;
        T ret = 0;
        for (ll a = (y, x); a > 0; a -= a & -a) {
            for (ll b = y; b > 0; b -= b & -b) {
                ret += bit[a][b];
            }
        }
		return ret;
    }
    T sum(ll x1, ll y1, ll x2, ll y2) {
        if (x1 > x2 || y1 > y2) return T(0);
        return sum(x2, y2) - sum(x2, y1) - sum(x1, y2) + sum(x1, y1);
    }
};
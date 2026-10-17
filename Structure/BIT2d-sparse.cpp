/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Structure/BIT2d-sparse.cpp */
// 座標が大きい平面向けの sparse 2D BIT(各 x ノードに、届く y を圧縮保持)。
// 入力が全部読めた状態で point / prefix 境界を request し、build() で確定してから
// add / sum を使う。矩形は 0-indexed 半開区間 [x1, x2) × [y1, y2)。
// 計算量: request O(log x) / build O(Q log x) / add, sum O(log x log q)
template <typename T>
struct BIT2dSparse {
    int n;                      // 圧縮後の x 方向の個数
    vector<vector<int>> ys;     // 各ノードが保持しうる y (圧縮後、昇順・重複なし)
    vector<vector<T>> dat;      // 各ノードの内部 BIT

    explicit BIT2dSparse(int n_) : n(n_), ys(n + 1), dat(n + 1) {}

    // 点 (圧縮後 x, 圧縮後 y) が更新されることを登録
    void request(int x, int y) {
        for (int a = x + 1; a <= n; a += a & -a) ys[a].push_back(y);
    }
    // 「x 未満かつ y 未満」の prefix 計算に必要な境界 (圧縮後 x, 圧縮後 y) を登録
    void request_prefix(int x, int y) {
        for (int a = x; a > 0; a -= a & -a) ys[a].push_back(y);
    }
    void build() {
        for (int a = 1; a <= n; a++) {
            sort(ys[a].begin(), ys[a].end());
            ys[a].erase(unique(ys[a].begin(), ys[a].end()), ys[a].end());
            dat[a].assign(ys[a].size() + 1, T(0));
        }
    }

    // 圧縮後座標 (x, y) に c を加算 (c は負も可)
    void add(int x, int y, T c) {
        for (int a = x + 1; a <= n; a += a & -a) {
            int k = lower_bound(ys[a].begin(), ys[a].end(), y) - ys[a].begin();
            for (int b = k + 1; b < (int)dat[a].size(); b += b & -b) dat[a][b] += c;
        }
    }

    // [0, x) × [0, y) の和 (x, y は圧縮後の境界 index)
    T pref(int x, int y) const {
        T ret = 0;
        for (int a = x; a > 0; a -= a & -a) {
            int k = lower_bound(ys[a].begin(), ys[a].end(), y) - ys[a].begin();
            for (int b = k; b > 0; b -= b & -b) ret += dat[a][b];
        }
        return ret;
    }

    // 矩形 [x1, x2) × [y1, y2) の和
    T sum(int x1, int x2, int y1, int y2) const {
        return pref(x2, y2) - pref(x2, y1) - pref(x1, y2) + pref(x1, y1);
    }
};

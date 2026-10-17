/* https://github.com/ICPC-Tsukuyom1/Tsukuyom1_Library/blob/main/Structure/binary-trie.cpp */
// T / op / e(): 可換モノイド
// op, e は省略可。既定では常に T{} を返す意味のないダミーを使う。
// B: ビット数 (デフォルト 63)
template <class T, auto op = [](const T&, const T&) { return T{}; },
          auto e = [] { return T{}; }, ll B = 63>
struct BinaryTrie {
  struct Node {
    array<Node*, 2> ch{};
    T val = e();
    ll cnt = 0;
    ll lazy = 0;
    void push(ll bit) {
      if (!lazy) return;
      if (lazy & bit) swap(ch[0], ch[1]);
      for (auto* v : ch)
        if (v) v->lazy ^= lazy & (bit - 1);
      lazy = 0;
    }
    T query(ll l, ll r, ll lo, ll hi) {
      if (hi < l || r <= lo) return e();
      if (l <= lo && hi < r) return val;
      ll mid = lo + (hi - lo) / 2 + 1;
      push(mid - lo);
      T lv = e(), rv = e();
      if (ch[0]) lv = ch[0]->query(l, r, lo, mid - 1);
      if (ch[1]) rv = ch[1]->query(l, r, mid, hi);
      return op(lv, rv);
    }
  };
  Node* root = new Node{};
  BinaryTrie() = default;
  BinaryTrie(const BinaryTrie&) = delete;
  BinaryTrie& operator=(const BinaryTrie&) = delete;

  ll size() const { return root->cnt; }
  T query_all() const { return root->val; }
  void xor_all(ll x) { root->lazy ^= x; }

 private:
  const Node* find(ll x) const {
    Node* v = root;
    rrep(b, 0, B) {
      v->push(1LL << b);
      v = v->ch[(x >> b) & 1];
      if (!v) return nullptr;
    }
    return v;
  }

 public:
  T get(ll x) const {
    auto v = find(x);
    return v ? v->val : e();
  }
  ll count(ll x) const {
    auto v = find(x);
    return v ? v->cnt : 0;
  }

  void insert(ll x, T val) { update(x, val, false); }
  void erase(ll x) { update(x, e(), true); }
  void update(ll x, T val, bool clear) {
    auto dfs = [&](auto&& self, Node*& v, ll b) -> void {
      if (!v) {
        if (clear) return;
        v = new Node{};
      }
      if (b == 0) {
        if (clear) v->val = e(), v->cnt = 0;
        else v->val = op(v->val, val), ++v->cnt;
      } else {
        v->push(1LL << (b - 1));
        self(self, v->ch[(x >> (b - 1)) & 1], b - 1);
        Node *l = v->ch[0], *r = v->ch[1];
        T lv = e(), rv = e();
        if (l) lv = l->val;
        if (r) rv = r->val;
        v->val = op(lv, rv);
        v->cnt = (l ? l->cnt : 0) + (r ? r->cnt : 0);
      }
    };
    dfs(dfs, root, B);
  }

  // 現在のキーの k 番目 (0-indexed、重複を含む)
  ll at(ll k) const {
    Node* v = root;
    ll res = 0;
    rrep(b, 0, B) {
      v->push(1LL << b);
      ll n = v->ch[0] ? v->ch[0]->cnt : 0, d = k >= n;
      if (d) k -= n;
      res |= d << b;
      v = v->ch[d];
    }
    return res;
  }

  // 現在のキーが [l, r) に入る要素の集約
  T query(ll l, ll r) const {
    l = max(l, 0LL);
    if (l >= r) return e();
    return root->query(l, r, 0, LLONG_MAX >> (63 - B));
  }
};

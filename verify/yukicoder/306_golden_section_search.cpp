//@yukicoder 306

#include "../../template.cpp"
#include "../../Math/golden_section_search.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ld xa, ya, xb, yb;
  cin >> xa >> ya >> xb >> yb;

  auto f = [&](ld y) -> ld {
    ld da = sqrtl(xa * xa + (ya - y) * (ya - y));
    ld db = sqrtl(xb * xb + (yb - y) * (yb - y));
    return da + db;
  };

  ld l = min(ya, yb), r = max(ya, yb);
  ld y = golden_section_search(l, r, f);
  cout << fixed << setprecision(15) << y << '\n';
  return 0;
}

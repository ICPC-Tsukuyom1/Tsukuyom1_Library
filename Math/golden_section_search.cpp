ld golden_section_search(ld l, ld r, auto f) {
  ld g = (sqrtl(5) - 1) / 2, eps = 1e-7;
  ld x1 = r - (r - l) * g, x2 = l + (r - l) * g;
  ld f1 = f(x1), f2 = f(x2);
  while (r - l > eps)
    if (f1 < f2) r = x2, x2 = x1, f2 = f1, x1 = r - (r - l) * g, f1 = f(x1);
    else l = x1, x1 = x2, f1 = f2, x2 = l + (r - l) * g, f2 = f(x2);
  return (l + r) / 2;
}

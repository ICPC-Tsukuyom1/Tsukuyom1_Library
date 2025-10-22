#include "./Point.cpp"
int isinPolygon(Point p, Polygon S) {
  bool check = false;
  rep(i, sz(S)) {
    Point A = S[i] - p, B = S[(i + 1) % sz(S)] - p;
    if (abs(A.cross(B)) < EPS && A.dot(B) < EPS) return 1;
    if (A.y > B.y) swap(A, B);
    if (A.y < EPS && EPS < B.y && A.cross(B) > EPS) check = !check;
  }
  return 2 * check;
}
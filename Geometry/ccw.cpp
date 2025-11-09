#include "./Point.cpp"
const int COUNTER_CLOCKWISE = 1;
const int CLOCKWISE = -1;
const int ONLINE_BACK = 2;
const int ONLINE_FRONT = -2;
const int ON_SEGMENT = 0;
int ccw(Point A, Point B, Point C) {
  Vector S = B - A, T = C - A;
  if (S.cross(T) > EPS) return COUNTER_CLOCKWISE;
  if (S.cross(T) < -EPS) return CLOCKWISE;
  if (S.dot(T) < -EPS) return ONLINE_BACK;
  if (S.norm() < T.norm()) return ONLINE_FRONT;
  return ON_SEGMENT;
}

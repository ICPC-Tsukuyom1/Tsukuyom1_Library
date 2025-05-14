static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;
int ccw(Point A, Point B, Point C) {
    Vector S = B - A, T = C - A;
    if (cross(S, T) > EPS) return COUNTER_CLOCKWISE;
    if (cross(S, T) < -EPS) return CLOCKWISE; 
    if (dot(S, T) < -EPS) return ONLINE_BACK; 
    if (S.norm() < T.norm()) return ONLINE_FRONT;
    return ON_SEGMENT;
}

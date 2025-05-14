bool isconvex(Polygon S) {
    bool check = true;
    for (ll i = 0; i+1 < S.size(); i++) {
        if (ccw(S[i],S[(i+1)%(ll)S.size()],S[(i+2)%(ll)S.size()]) == COUNTER_CLOCKWISE) {
            check = false;
        }
    }
    bool check2 = true;
    for (ll i = 0; i+1 < S.size(); i++) {
        if (ccw(S[i],S[(i+1)%(ll)S.size()],S[(i+2)%(ll)S.size()]) == CLOCKWISE) {
            check2 = false;
        }
    }
    return check | check2;
}

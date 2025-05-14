// ！！！！！！何らかのバグが発生してます！！！！！！
Polygon convex_hull(Polygon S) {
    Polygon u, l;
    if (S.size() < 3) return S;
    sort(S.begin(), S.end());
    u.push_back(S[0]); u.push_back(S[1]);
    l.push_back(S[S.size()-1]); l.push_back(S[S.size() - 2]);
    for (int i = 2; i < S.size(); i++) {
        for (int n = u.size(); n >= 2 && ccw(u[n-2],u[n-1],S[i])!=CLOCKWISE;n--){
            u.pop_back();
        }
        u.push_back(S[i]);
    }
    for (int i = S.size() - 3; i >= 0; i--) {
        for (int n = l.size(); n >= 2 && ccw(l[n-2],l[n-1],S[i])!=CLOCKWISE;n--){
            l.pop_back();
        }
        l.push_back(S[i]);
    }
    reverse(l.begin(),l.end());
    for (int i = u.size()-2;i>=1;i--){
        l.push_back(u[i]);
    }

    return l;
}

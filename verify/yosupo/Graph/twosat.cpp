//@yosupo two_sat

#include "../../../template.cpp"
#include "../../../Graph/Graph.cpp"
#include "../../../Graph/SCC.cpp"
#include "../../../Graph/twosat.cpp"

int main(){
    string _; ll N, M; cin >> _ >> _ >> N >> M;
    Twosat ts(N);
    rep(i, M){
        ll x, y, __; cin >> x >> y >> __;
        bool f = (x > 0), g = (y > 0);
        ts.either(abs(x)-1, f, abs(y)-1, g);
    }
    auto ans = ts.satisfy();
    if(!sz(ans)){
        cout << "s " << "UNSATISFIABLE" << endl;
        return;
    }
    cout << "s " << "SATISFIABLE" << endl;
    cout << "v ";
    rep(i, N){
        cout << (i+1) * ((ans[i]) ? 1 : -1) << " ";
    }
    cout << 0 << endl;
    return;
}
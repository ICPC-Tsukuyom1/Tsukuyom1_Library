
template <typename T = ll>
ll LIS(vector<T> &A, bool strict) {
    vector<T> lis;
    for (auto &p : A) {
        typename vector<T>::iterator it;
        if (strict) it = lower_bound(all(lis), p);
        else it = upper_bound(all(lis), p);
        if (end(lis) == it) lis.emplace_back(p);
        else *it = p;
    }
    return (ll)lis.size();
}
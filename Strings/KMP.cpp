vl pi(const string &s) {
	vl p(sz(s));
	reps(i, 1, sz(s)) {
		ll g = p[i - 1];
		while (g && s[i] != s[g]) g = p[g - 1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}
vl match(const string &s, const string& pat) {
	vl p = pi(pat + '\0' + s), res;
	reps(i, sz(p) - sz(s), sz(p))
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}
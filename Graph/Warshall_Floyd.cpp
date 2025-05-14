void Warshall_Floyd(vector<vector<ll>>&dist, ll N) {
  rep(k, N) {
    rep(i, N) {
      rep(j, N) {
        if (dist[i][k] == INF || dist[k][j] == INF) continue;
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}

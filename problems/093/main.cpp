#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adj[a].push_back({b, c});
    }
    // state 0 = coupon unused, 1 = coupon used
    vector<array<long long, 2>> dist(n + 1, {LLONG_MAX, LLONG_MAX});
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> pq;
    dist[1][0] = 0; pq.push({0, 1, 0});
    while (!pq.empty()) {
        auto [d, u, s] = pq.top(); pq.pop();
        if (d > dist[u][s]) continue;
        for (auto [v, w] : adj[u]) {
            if (d + w < dist[v][s]) { dist[v][s] = d + w; pq.push({dist[v][s], v, s}); }
            if (s == 0 && d + w / 2 < dist[v][1]) { dist[v][1] = d + w / 2; pq.push({dist[v][1], v, 1}); }
        }
    }
    printf("%lld\n", min(dist[n][0], dist[n][1]));
}

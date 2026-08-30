#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adj[a].push_back({b, c});
    }
    const long long INF = 1e18;
    vector<long long> d(n + 1, INF), ways(n + 1, 0);
    vector<int> mn(n + 1, INT_MAX), mx(n + 1, 0), done(n + 1, 0);
    d[1] = 0; ways[1] = 1; mn[1] = 0; mx[1] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [dd, u] = pq.top(); pq.pop();
        if (done[u]) continue;
        done[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w; ways[v] = ways[u]; mn[v] = mn[u] + 1; mx[v] = mx[u] + 1;
                pq.push({d[v], v});
            } else if (d[u] + w == d[v]) {
                ways[v] = (ways[v] + ways[u]) % MOD;
                mn[v] = min(mn[v], mn[u] + 1);
                mx[v] = max(mx[v], mx[u] + 1);
            }
        }
    }
    printf("%lld %lld %d %d\n", d[n], ways[n], mn[n], mx[n]);
}

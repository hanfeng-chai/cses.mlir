#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<array<long long, 3>> e(m);
    vector<vector<int>> adj(n + 1), radj(n + 1);
    for (auto &E : e) {
        long long a, b, x;
        scanf("%lld %lld %lld", &a, &b, &x);
        E = {a, b, x}; adj[a].push_back(b); radj[b].push_back(a);
    }
    vector<char> r1(n + 1, 0), rn(n + 1, 0);
    { queue<int> q; q.push(1); r1[1] = 1; while (!q.empty()) { int u = q.front(); q.pop(); for (int v : adj[u]) if (!r1[v]) { r1[v] = 1; q.push(v); } } }
    { queue<int> q; q.push(n); rn[n] = 1; while (!q.empty()) { int u = q.front(); q.pop(); for (int v : radj[u]) if (!rn[v]) { rn[v] = 1; q.push(v); } } }
    const long long NEG = LLONG_MIN / 4;
    vector<long long> dist(n + 1, NEG); dist[1] = 0;
    for (int it = 0; it < n - 1; it++)
        for (auto &[a, b, x] : e)
            if (dist[a] > NEG && dist[a] + x > dist[b]) dist[b] = dist[a] + x;
    bool inf = false;
    for (auto &[a, b, x] : e)
        if (dist[a] > NEG && dist[a] + x > dist[b] && r1[a] && rn[b]) inf = true;
    if (inf) printf("-1\n");
    else printf("%lld\n", dist[n]);
}

#include <bits/stdc++.h>
using namespace std;
struct Dinic {
    struct E { int to; long long cap; int rev; };
    vector<vector<E>> g;
    vector<int> level, it;
    int n;
    Dinic(int n) : g(n), level(n), it(n), n(n) {}
    void add(int a, int b, long long c) {
        g[a].push_back({b, c, (int)g[b].size()});
        g[b].push_back({a, 0, (int)g[a].size() - 1});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q; level[s] = 0; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u]) if (e.cap > 0 && level[e.to] < 0) { level[e.to] = level[u] + 1; q.push(e.to); }
        }
        return level[t] >= 0;
    }
    long long dfs(int u, int t, long long f) {
        if (u == t) return f;
        for (int &i = it[u]; i < (int)g[u].size(); i++) {
            auto &e = g[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                long long d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) { e.cap -= d; g[e.to][e.rev].cap += d; return d; }
            }
        }
        return 0;
    }
    long long maxflow(int s, int t) {
        long long fl = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            long long f;
            while ((f = dfs(s, t, LLONG_MAX)) > 0) fl += f;
        }
        return fl;
    }
};
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Dinic d(n + 1);
    vector<pair<int, int>> es(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        es[i] = {a, b};
        d.add(a, b, 1); d.add(b, a, 1);  // undirected street, closing costs 1
    }
    long long f = d.maxflow(1, n);
    // min cut: S = nodes reachable from source in the residual graph
    vector<char> vis(n + 1, 0);
    queue<int> q; q.push(1); vis[1] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &e : d.g[u]) if (e.cap > 0 && !vis[e.to]) { vis[e.to] = 1; q.push(e.to); }
    }
    printf("%lld\n", f);
    for (auto [a, b] : es) if (vis[a] != vis[b]) printf("%d %d\n", a, b);
}

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
    vector<int> pos(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        es[i] = {a, b}; pos[i] = d.g[a].size();
        d.add(a, b, 1);
    }
    long long f = d.maxflow(1, n);
    // Dinic flow is acyclic (sum of s-t paths); follow used edges to extract paths
    vector<vector<int>> nxt(n + 1);
    for (int i = 0; i < m; i++)
        if (d.g[es[i].first][pos[i]].cap == 0) nxt[es[i].first].push_back(es[i].second);
    vector<int> ptr(n + 1, 0);
    printf("%lld\n", f);
    for (long long p = 0; p < f; p++) {
        vector<int> path = {1};
        int u = 1;
        while (u != n) { int v = nxt[u][ptr[u]++]; path.push_back(v); u = v; }
        printf("%d\n", (int)path.size());
        for (size_t i = 0; i < path.size(); i++) printf("%d%c", path[i], " \n"[i + 1 == path.size()]);
    }
}
